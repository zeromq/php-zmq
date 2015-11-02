/*
+-----------------------------------------------------------------------------------+
|  ZMQ extension for PHP                                                            |
|  Copyright (c) 2010-2013, Mikko Koppanen <mkoppanen@php.net>                      |
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
#include "zmq_object_access.c"
#include "ext/spl/php_spl.h"

#define PHP_ZMQ_ALLOC_SIZE 5

void php_zmq_pollset_init(php_zmq_pollset *set) 
{
	set->num_items       = 0;
	set->num_php_items   = 0;
	set->alloc_size      = PHP_ZMQ_ALLOC_SIZE;

	set->items     = ecalloc(PHP_ZMQ_ALLOC_SIZE, sizeof(zmq_pollitem_t));
	set->php_items = ecalloc(PHP_ZMQ_ALLOC_SIZE, sizeof(php_zmq_pollitem));
	array_init(&set->errors);
}

void php_zmq_pollset_clear(php_zmq_pollset *set, zend_bool reinit TSRMLS_DC)
{
	if (set->alloc_size > 0) {
		efree(set->php_items);
		efree(set->items);
	}

	set->items      = NULL;
	set->php_items  = NULL;
	set->alloc_size = 0;

	if (reinit) {
		zval_dtor(&set->errors);
		php_zmq_pollset_init(set);
	}
}

static
void php_zmq_pollitem_deinit(php_zmq_pollitem *item) {
	Z_DELREF(item->entry);
	zend_string_release(item->key);
}

void php_zmq_pollset_deinit(php_zmq_pollset *set TSRMLS_DC)
{
	int i;

	for (i = 0; i < set->num_php_items; i++) {
		php_zmq_pollitem_deinit(&set->php_items[i]);
	}
	php_zmq_pollset_clear(set, 0 TSRMLS_CC);
	zval_dtor(&set->errors);
}

void php_zmq_pollset_delete_all(php_zmq_pollset *set TSRMLS_DC)
{
	int i;
	for (i = 0; i < set->num_php_items; i++) {
		php_zmq_pollitem_deinit(&set->php_items[i]);
	}
	php_zmq_pollset_clear(set, 1 TSRMLS_CC);
}

static
zend_string *php_zmq_create_key(zval *entry TSRMLS_DC)
{
	if (Z_TYPE_P(entry) == IS_RESOURCE) {
		return strpprintf(0, "r:%ld", Z_RES_P(entry)->handle);
	}
	else {
		zend_string *hash = php_spl_object_hash(entry);
		zend_string *key = strpprintf(0, "o:%s", hash->val);
		zend_string_release(hash);
		return key;
	}
}

zend_string *php_zmq_pollset_get_key(php_zmq_pollset *set, int pos TSRMLS_DC)
{
	if (pos >= set->num_php_items || pos < 0) {
		return 0;
	}
	return zend_string_dup(set->php_items[pos].key, 1);
}

int php_zmq_pollset_add(php_zmq_pollset *pollset, zval *entry, int events TSRMLS_DC) 
{
	int i;
	zend_string *key;
	zend_bool resize;

	assert(pollset->num_php_items == pollset->num_items);

	if (Z_TYPE_P(entry) != IS_OBJECT && Z_TYPE_P(entry) != IS_RESOURCE) {
		return PHP_ZMQ_POLLSET_ERR_INVALID_TYPE;
	}

	key = php_zmq_create_key(entry TSRMLS_CC);

	if (!key) {
		return PHP_ZMQ_POLLSET_ERR_KEY_FAIL;
	}

	for (i = 0; i < pollset->num_php_items; i++) {
		if (zend_string_equals(pollset->php_items[i].key, key)) {

			pollset->items[i].events     = events;
			pollset->php_items[i].events = events;
			zend_string_release(key);
			return i;
		}
	}

	resize = (pollset->num_items >= pollset->alloc_size);

	if (Z_TYPE_P(entry) == IS_RESOURCE) {
		int fd;
		php_stream *stream;

		php_stream_from_zval_no_verify(stream, entry);

		if (!stream) {
			return PHP_ZMQ_POLLSET_ERR_NO_STREAM;
		}

		if (php_stream_can_cast(stream, (PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL | PHP_STREAM_AS_SOCKETD) & ~REPORT_ERRORS) == FAILURE) {
			return PHP_ZMQ_POLLSET_ERR_CANNOT_CAST;
		}

		if (php_stream_cast(stream, (PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL | PHP_STREAM_AS_SOCKETD) & ~REPORT_ERRORS, (void*)&fd, 0) == FAILURE) {
			return PHP_ZMQ_POLLSET_ERR_CAST_FAILED;
		}

		if (resize) {
			pollset->items = erealloc(pollset->items, (pollset->alloc_size + PHP_ZMQ_ALLOC_SIZE) * sizeof(zmq_pollitem_t));
		}

		memset(&(pollset->items[pollset->num_items]), 0, sizeof(zmq_pollitem_t));

		pollset->items[pollset->num_items].fd     = fd;
		pollset->items[pollset->num_items].events = events;

		ZVAL_COPY(&pollset->php_items[pollset->num_php_items].entry, entry);

	} else {
		php_zmq_socket_object *item = php_zmq_socket_fetch_object(Z_OBJ_P(entry));

		if (resize) {
			pollset->items = erealloc(pollset->items, (pollset->alloc_size + PHP_ZMQ_ALLOC_SIZE) * sizeof(zmq_pollitem_t));
		}

		memset(&(pollset->items[pollset->num_items]), 0, sizeof(zmq_pollitem_t));

		pollset->items[pollset->num_items].socket = item->socket->z_socket;
		pollset->items[pollset->num_items].events = events;

		ZVAL_OBJ(&pollset->php_items[pollset->num_php_items].entry, &item->zo);
		Z_ADDREF(pollset->php_items[pollset->num_php_items].entry);
	}
	if (resize) {
		pollset->php_items   = erealloc(pollset->php_items, (pollset->alloc_size + PHP_ZMQ_ALLOC_SIZE) * sizeof(php_zmq_pollitem));
		pollset->alloc_size += PHP_ZMQ_ALLOC_SIZE;
	}

	pollset->php_items[pollset->num_php_items].events = events;
	pollset->php_items[pollset->num_php_items].key    = key;

	if (Z_TYPE_P(entry) == IS_RESOURCE) {
		pollset->php_items[pollset->num_php_items].fd = pollset->items[pollset->num_items].fd;
	} else {
		pollset->php_items[pollset->num_php_items].socket = pollset->items[pollset->num_items].socket;
	}

	pollset->num_php_items++;
	pollset->num_items++;
	return (pollset->num_php_items - 1);
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
	set->items = ecalloc(set->alloc_size, sizeof(zmq_pollitem_t));

	for (i = 0; i < set->num_php_items; i++) {
		if (Z_TYPE(set->php_items[i].entry) == IS_RESOURCE) {
			set->items[i].fd = set->php_items[i].fd;
		} else {
			set->items[i].socket = set->php_items[i].socket;
		}
		set->items[i].events = set->php_items[i].events;
	}
	set->num_items = set->num_php_items;
}

zend_bool php_zmq_pollset_delete_by_key(php_zmq_pollset *set, zend_string *key TSRMLS_DC)
{
	php_zmq_pollitem *php_items = NULL;
	int i, num_php_items = 0, alloc_size;
	zend_bool match = 0;

	alloc_size = (set->alloc_size - set->num_items > PHP_ZMQ_ALLOC_SIZE) ? (set->alloc_size - PHP_ZMQ_ALLOC_SIZE) : set->alloc_size;
	php_items  = ecalloc(alloc_size, sizeof(php_zmq_pollitem));

	for (i = 0; i < set->num_php_items; i++) {
		if (!match && zend_string_equals(set->php_items[i].key, key)) {
			php_zmq_pollitem_deinit(&set->php_items[i]);
			match = 1;
			continue;
		}
		memcpy(&php_items[num_php_items], &set->php_items[i], sizeof(php_zmq_pollitem));
		num_php_items++;
	}

	php_zmq_pollset_clear(set, 0 TSRMLS_CC);
	set->php_items     = php_items;
	set->num_php_items = num_php_items;
	set->alloc_size    = alloc_size;

	php_zmq_pollset_rebuild(set);
	return match;
}

zend_bool php_zmq_pollset_delete(php_zmq_pollset *set, zval *entry TSRMLS_DC)
{
	zend_bool retval;
	zend_string *key = php_zmq_create_key(entry TSRMLS_CC);

	retval = php_zmq_pollset_delete_by_key(set, key TSRMLS_CC);
	zend_string_release(key);

	return retval;
}

int php_zmq_pollset_poll(php_zmq_pollset *set, int timeout, zval *r_array, zval *w_array, zval *e_array)
{
	int rc, i;
	zend_bool readable = 0, writable = 0;

	zend_hash_clean(Z_ARRVAL_P(e_array));

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

	rc = zmq_poll(set->items, set->num_items, timeout);

	if (rc == -1) {
		return -1;
	}

	if (rc > 0) {
		for (i = 0; i < set->num_items; i++) {
			if (readable && set->items[i].revents & ZMQ_POLLIN) {
				Z_ADDREF(set->php_items[i].entry);
				add_next_index_zval(r_array, &set->php_items[i].entry);
			}

			if (writable && set->items[i].revents & ZMQ_POLLOUT) {
				Z_ADDREF(set->php_items[i].entry);
				add_next_index_zval(w_array, &set->php_items[i].entry);
			}

			if (set->items[i].revents & ZMQ_POLLERR) {
				add_next_index_str(e_array, set->php_items[i].key);
			}
		}
	}
	return rc;
}
