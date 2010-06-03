/*
+-----------------------------------------------------------------------------------+
|  ZMQ extension for PHP                                                            |
|  Copyright (c) 2010, Mikko Koppanen <mkoppanen@php.net>                           |
|  All rights reserved.                                                             |
+-----------------------------------------------------------------------------------+
|  Redistribution and use in source and binary forms, with or without               |
|  modification, are permitted provided that the following conditions are met:      |
|     * Redistributions of source code must retain the above copyright              |
|       notice, this list of conditions and the following disclaimer.               |
|     * Redistributions in binary form must reproduce the above copyright           |
|       notice, this list of conditions and the following disclaimer in the         |
|       documentation and/or other materials provided with the distribution.        |
|     * Neither the name of the copyright holder nor the                            |
|       names of its contributors may be used to endorse or promote products        |
|       derived from this software without specific prior written permission.       |
+-----------------------------------------------------------------------------------+
|  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND  |
|  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED    |
|  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           |
|  DISCLAIMED. IN NO EVENT SHALL MIKKO KOPPANEN BE LIABLE FOR ANY                   |
|  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES       |
|  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;     |
|  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND      |
|  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       |
|  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS    |
|  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                     |
+-----------------------------------------------------------------------------------+
*/

#include "php_zmq.h"
#include "php_zmq_private.h"
#include "php_zmq_pollset.h"

void php_zmq_pollset_init(php_zmq_pollset *set) 
{	
	set->items         = NULL;
	set->php_items     = NULL;
		
	set->num_items     = 0;
	set->num_php_items = 0;
	
	MAKE_STD_ZVAL(set->errors);
	array_init(set->errors);
}

void php_zmq_pollset_clear(php_zmq_pollset *set) 
{
	if (set->php_items)	{
		efree(set->php_items);
		set->php_items = NULL;
	}
	
	if (set->items) {
		efree(set->items);
		set->items = NULL;
	}
	set->num_items     = 0;
	set->num_php_items = 0;
}

void php_zmq_pollset_deinit(php_zmq_pollset *set TSRMLS_DC)
{
	int i;
	
	for (i = 0; i < set->num_php_items; i++) {
		if (Z_TYPE_P(set->php_items[i].entry) == IS_RESOURCE) {
			Z_DELREF_P(set->php_items[i].entry);
		} else {
			zend_objects_store_del_ref(set->php_items[i].entry TSRMLS_CC);
		}
	}
	php_zmq_pollset_clear(set);
	
	zval_dtor(set->errors);
	FREE_ZVAL(set->errors);
}

void php_zmq_pollset_delete_all(php_zmq_pollset *set TSRMLS_DC)
{
	int i;
	
	for (i = 0; i < set->num_php_items; i++) {
		if (Z_TYPE_P(set->php_items[i].entry) == IS_RESOURCE) {
			Z_DELREF_P(set->php_items[i].entry);
		} else {
			zend_objects_store_del_ref(set->php_items[i].entry TSRMLS_CC);
		}
	}
	php_zmq_pollset_clear(set);
}

static void php_zmq_create_key(zval *entry, char key[35], int *key_len)
{
	if (Z_TYPE_P(entry) == IS_RESOURCE) {
		*key_len = snprintf(key, 35, "r:%d", Z_LVAL_P(entry));
	} else {
		char hash[33];
		php_spl_object_hash(entry, hash TSRMLS_CC);
		*key_len = snprintf(key, 35, "o:%s", hash);
	}
}

zend_bool php_zmq_pollset_get_key(php_zmq_pollset *set, int pos, char key[35], int *key_len)
{
	if (pos >= set->num_php_items || pos < 0) {
		return 0;
	}
	
	if (*key_len < set->php_items[pos].key_len + 1) {
		return 0;
	}
	memcpy(key, set->php_items[pos].key, set->php_items[pos].key_len + 1);
	*key_len = set->php_items[pos].key_len;
	return 1;
}

int php_zmq_pollset_add(php_zmq_pollset *set, zval *entry, int events) 
{
	int i;
	char key[35];
	int key_len;
	
	assert(set->num_php_items == set->num_items);
	
	php_zmq_create_key(entry, key, &key_len);
	
	for (i = 0; i < set->num_php_items; i++) {
		if (key_len == set->php_items[i].key_len &&
			!memcmp(set->php_items[i].key, key, key_len)) {
		
			set->items[i].events     = events;
			set->php_items[i].events = events;
			return i;
		}
	}

	if (Z_TYPE_P(entry) == IS_RESOURCE) {
		int fd;
		php_stream *stream;

		php_stream_from_zval_no_verify(stream, &entry);

		if (!stream) {
			return -1;
		}

		if (php_stream_can_cast(stream, PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL) == FAILURE) {
			return -2;
		}

		if (php_stream_cast(stream, PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL, (void*)&fd, 0) == FAILURE) {
			return -3;
		}	

		set->items = erealloc(set->items, (set->num_items + 1) * sizeof(zmq_pollitem_t));
		memset(&(set->items[set->num_items]), 0, sizeof(zmq_pollitem_t));
		
		set->items[set->num_items].fd     = fd;
		set->items[set->num_items].events = events;
		Z_ADDREF_P(entry);
		
	} else {
		
		php_zmq_object *item = (php_zmq_object *)zend_object_store_get_object(entry TSRMLS_CC);

		if (!item->zms) {
			return -4;
		}

		if (!item->ctx_opts.poll) {
			return -5;
		}
		
		set->items = erealloc(set->items, (set->num_items + 1) * sizeof(zmq_pollitem_t));
		memset(&(set->items[set->num_items]), 0, sizeof(zmq_pollitem_t));
		
		set->items[set->num_items].socket = item->zms->socket;
		set->items[set->num_items].events = events;
		zend_objects_store_add_ref(entry TSRMLS_CC);	
	}
	
	set->php_items = erealloc(set->php_items, (set->num_php_items + 1) * sizeof(php_zmq_pollitem));
	
	set->php_items[set->num_php_items].events  = events;
	set->php_items[set->num_php_items].entry   = entry;
	set->php_items[set->num_php_items].key_len = key_len;
	
	if (Z_TYPE_P(entry) == IS_RESOURCE) {
		set->php_items[set->num_php_items].fd = set->items[set->num_items].fd;
	} else {
		set->php_items[set->num_php_items].socket = set->items[set->num_items].socket;
	}
	
	memcpy(set->php_items[set->num_php_items].key, key, key_len + 1);
	
	set->num_php_items++;
	set->num_items++;
	return (set->num_php_items - 1);
}

void php_zmq_pollset_rebuild(php_zmq_pollset *set)
{
	int i;
	
	if (set->num_php_items == 0 && set->items) {
		efree(set->items);	
		set->items = NULL;
		return;
	}

	/* Clear items */
	if (set->items) {
		efree(set->items);	
	}
	set->items = ecalloc(set->num_php_items, sizeof(zmq_pollitem_t));

	for (i = 0; i < set->num_php_items; i++) {
		if (Z_TYPE_P(set->php_items[i].entry) == IS_RESOURCE) {
			set->items[i].fd = set->php_items[i].fd;
		} else {
			set->items[i].socket = set->php_items[i].socket;	
		}
		set->items[i].events = set->php_items[i].events;
	}
	set->num_items = set->num_php_items;
}

static void php_zmq_pollitem_copy(php_zmq_pollitem *target, php_zmq_pollitem *source)
{
	target->events  = source->events;
	target->entry   = source->entry;
	target->key_len = source->key_len;
	memcpy(target->key, source->key, source->key_len + 1);
}

zend_bool php_zmq_pollset_delete_by_key(php_zmq_pollset *set, char key[35], int key_len)
{	
	php_zmq_pollitem *php_items = NULL;
	int i, num_php_items = 0;
	zend_bool match = 0;
	
	for (i = 0; i < set->num_php_items; i++) {
		if (key_len == set->php_items[i].key_len &&
			!memcmp(set->php_items[i].key, key, key_len)) {	
				
			if (Z_TYPE_P(set->php_items[i].entry) == IS_RESOURCE) {
				Z_DELREF_P(set->php_items[i].entry);
			} else {
				zend_objects_store_add_ref(set->php_items[i].entry TSRMLS_CC);
			}
			match = 1;
			continue;
		}
		php_items = erealloc(php_items, (num_php_items + 1) * sizeof(php_zmq_pollitem));
		php_zmq_pollitem_copy(&(php_items[num_php_items]), &(set->php_items[i]));
		num_php_items++;
	}
	php_zmq_pollset_clear(set);
	set->php_items     = php_items;
	set->num_php_items = num_php_items;
	
	php_zmq_pollset_rebuild(set);
	return match;
}

zend_bool php_zmq_pollset_delete(php_zmq_pollset *set, zval *entry)
{
	char key[35];
	int key_len;
	
	php_zmq_create_key(entry, key, &key_len);
	return php_zmq_pollset_delete_by_key(set, key, key_len);
}

int php_zmq_pollset_poll(php_zmq_pollset *set, int timeout, zval *r_array, zval *w_array, zval *e_array)
{
	int rc, i;
	zend_bool readable = 0, writable = 0;

	rc = zmq_poll(set->items, set->num_items, timeout);
	
	if (rc == -1) {
		return -1;
	}
	
	if (r_array && Z_TYPE_P(r_array) == IS_ARRAY) {
		if (zend_hash_num_elements(Z_ARRVAL_P(r_array)) > 0) {
			zend_hash_clean(Z_ARRVAL_P(r_array));
		}
		readable = 1;
	}
	
	if (w_array && Z_TYPE_P(w_array) == IS_ARRAY) {
		if (zend_hash_num_elements(Z_ARRVAL_P(w_array)) > 0) { 
			zend_hash_clean(Z_ARRVAL_P(w_array));
		}
		writable = 1;
	}
	
	assert(set->num_items == set->num_php_items);
	
	if (rc > 0) {
		zend_hash_clean(Z_ARRVAL_P(e_array));
		
		for (i = 0; i < set->num_items; i++) {
			if (readable && set->items[i].revents & ZMQ_POLLIN) {
				Z_ADDREF_P(set->php_items[i].entry);
				add_next_index_zval(r_array, set->php_items[i].entry);
			} 
		
			if (writable && set->items[i].revents & ZMQ_POLLOUT) {
				Z_ADDREF_P(set->php_items[i].entry);
				add_next_index_zval(w_array, set->php_items[i].entry);
			}
		
			if (set->items[i].revents & ZMQ_POLLERR) {
				add_next_index_string(e_array, set->php_items[i].key, set->php_items[i].key_len);
			}
		}
	}
	return rc;
}
