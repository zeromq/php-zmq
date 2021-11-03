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

#define PHP_ZMQ_ALLOC_SIZE 20

/* {{{ typedef struct _php_zmq_pollset 
*/
struct _php_zmq_pollset {

	zmq_pollitem_t *items;
	zend_string **keys;
	zval *zv;

	size_t num_items;
	size_t allocated;
	size_t alloc_size;

	zval errors;
};
/* }}} */

static
void s_pollset_clear(php_zmq_pollset *set, zend_bool reinit)
{
	size_t i;

	if (set->items) {
		efree(set->items);
	}

	if (set->zv) {
		for (i = 0; i < set->num_items; i++) {
			zval_ptr_dtor(&set->zv[i]);
		}
		efree(set->zv);
	}

	if (set->keys) {
		for (i = 0; i < set->num_items; i++) {
			zend_string_release(set->keys[i]);
		}
		efree(set->keys);
	}

	if (reinit) {
		set->items      = ecalloc(set->alloc_size, sizeof(zmq_pollitem_t));
		set->keys       = ecalloc(set->alloc_size, sizeof(zend_string *));
		set->zv         = ecalloc(set->alloc_size, sizeof(zval));
		set->allocated  = set->alloc_size;
		set->num_items  = 0;
	}
}

static
size_t s_pollset_append(php_zmq_pollset *set, zmq_pollitem_t *item, zend_string *key, zval *entry)
{
	size_t index = set->num_items;

	if (set->allocated <= set->num_items + 1) {

		set->items = erealloc (set->items, (set->allocated + set->alloc_size) * sizeof(zmq_pollitem_t));
		set->keys  = erealloc (set->keys,  (set->allocated + set->alloc_size) * sizeof(zend_string *));
		set->zv    = erealloc (set->zv,    (set->allocated + set->alloc_size) * sizeof(zval));

		set->allocated += set->alloc_size;
	}

	memcpy (&(set->items[index]), item, sizeof(zmq_pollitem_t));
	set->keys[index] = key;

	ZVAL_COPY_VALUE(&set->zv[index], entry);
	Z_ADDREF(set->zv[index]);

	set->num_items++;
	return index;
}

static
void s_pollset_delete(php_zmq_pollset *set, size_t index)
{
	zend_string_release(set->keys[index]);
	zval_ptr_dtor(&set->zv[index]);

	memmove(
		set->items + index,
		set->items + index + 1,
		(set->num_items - index - 1) * sizeof(zmq_pollitem_t)
	);
	memmove(
		set->keys + index,
		set->keys + index + 1,
		(set->num_items - index - 1) * sizeof(zend_string *)
	);
	memmove(
		set->zv + index,
		set->zv + index + 1,
		(set->num_items - index - 1) * sizeof(zval)
	);

	set->num_items--;

	if ((set->allocated - set->alloc_size > set->num_items) &&
	    (set->allocated - set->alloc_size > set->alloc_size)) {

		set->items = erealloc (set->items, (set->allocated - set->alloc_size) * sizeof(zmq_pollitem_t));
		set->keys  = erealloc (set->keys,  (set->allocated - set->alloc_size) * sizeof(zend_string *));
		set->zv    = erealloc (set->zv,    (set->allocated - set->alloc_size) * sizeof(zval));

		set->allocated -= set->alloc_size;
	}
}

static
zend_bool s_index_for_key(php_zmq_pollset *set, zend_string *key, size_t *index)
{
	zend_bool retval = 0;
	size_t i;

	for (i = 0; i < set->num_items; i++) {
		if (zend_string_equals (set->keys[i], key)) {
			*index = i;
			retval = 1;
			break;
		}
	}
	return retval;
}

static
zval *s_zval_for_index(php_zmq_pollset *set, size_t index)
{
	return &set->zv[index];
}

static
zend_string *s_create_key(zval *entry)
{
	if (Z_TYPE_P(entry) == IS_RESOURCE) {
		/* zend_long since 8.1.0 */
		return strpprintf(0, "r:%ld", (long)Z_RES_P(entry)->handle);
	}
	else {
#if PHP_VERSION_ID >= 80100
		zend_string *hash = php_spl_object_hash(Z_OBJ_P(entry));
#else
		zend_string *hash = php_spl_object_hash(entry);
#endif
		zend_string *key = strpprintf(0, "o:%s", hash->val);
		zend_string_release(hash);
		return key;
	}
}

php_zmq_pollset *php_zmq_pollset_init()
{
	php_zmq_pollset *set = ecalloc (1, sizeof(php_zmq_pollset));

	array_init(&set->errors);

	set->items      = ecalloc(PHP_ZMQ_ALLOC_SIZE, sizeof(zmq_pollitem_t));
	set->keys       = ecalloc(PHP_ZMQ_ALLOC_SIZE, sizeof(zend_string *));
	set->zv         = ecalloc(PHP_ZMQ_ALLOC_SIZE, sizeof(zval));
	set->allocated  = PHP_ZMQ_ALLOC_SIZE;
	set->alloc_size = PHP_ZMQ_ALLOC_SIZE;
	set->num_items  = 0;

	return set;
}

zend_bool php_zmq_pollset_items(php_zmq_pollset *set, zval *return_value)
{
	size_t i;

	if (set->num_items == 0) {
		return 0;
	}

	for (i = 0; i < set->num_items; i++) {
		zval *zv = s_zval_for_index(set, i);

		if (zv) {
			Z_ADDREF_P(zv);
			add_assoc_zval(return_value, set->keys[i]->val, zv);
		}
	}
	return 1;
}

size_t php_zmq_pollset_num_items(php_zmq_pollset *set)
{
	return set->num_items;
}

zend_string *php_zmq_pollset_add(php_zmq_pollset *set, zval *entry, int events, int *error) 
{
	zend_string *key;
	size_t index;
	zmq_pollitem_t item;

	*error = 0;
	key = s_create_key(entry);

	// Does this already exist?
	if (s_index_for_key(set, key, &index)) {
		return key;
	}

	memset(&item, 0, sizeof(zmq_pollitem_t));

	if (Z_TYPE_P(entry) == IS_RESOURCE) {
		int fd;
		php_stream *stream;

		php_stream_from_zval_no_verify(stream, entry);

		if (!stream) {
			*error = PHP_ZMQ_POLLSET_ERR_NO_STREAM;
			zend_string_release(key);
			return NULL;
		}

		if (php_stream_can_cast(stream, (PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL | PHP_STREAM_AS_SOCKETD) & ~REPORT_ERRORS) == FAILURE) {
			*error = PHP_ZMQ_POLLSET_ERR_CANNOT_CAST;
			zend_string_release(key);
			return NULL;
		}

		if (php_stream_cast(stream, (PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL | PHP_STREAM_AS_SOCKETD) & ~REPORT_ERRORS, (void*)&fd, 0) == FAILURE) {
			*error = PHP_ZMQ_POLLSET_ERR_CAST_FAILED;
			zend_string_release(key);
			return NULL;
		}
		item.fd = fd;
		item.socket = NULL;
	}
	else {
		php_zmq_socket_object *intern = php_zmq_socket_fetch_object(Z_OBJ_P(entry));
		item.socket = intern->socket->z_socket;
		item.fd = 0;
	}
	item.events = events;

	s_pollset_append(set, &item, zend_string_copy(key), entry);
	return key;
}

zend_bool php_zmq_pollset_delete_by_key(php_zmq_pollset *set, zend_string *key)
{
	size_t index;

	if (!s_index_for_key(set, key, &index)) {
		return 0;
	}

	s_pollset_delete(set, index);
	return 1;
}

zend_bool php_zmq_pollset_delete(php_zmq_pollset *set, zval *entry)
{
	zend_bool retval;
	zend_string *key = s_create_key(entry);

	retval = php_zmq_pollset_delete_by_key(set, key);
	zend_string_release(key);

	return retval;
}

int php_zmq_pollset_poll(php_zmq_pollset *set, int timeout, zval *r_array, zval *w_array)
{
	int rc, i;
	zend_bool readable = 0, writable = 0;

	if (!set->items) {
		return -1;
	}

	zend_hash_clean(Z_ARRVAL(set->errors));

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

	rc = zmq_poll(set->items, set->num_items, timeout);

	if (rc == -1) {
		return -1;
	}

	if (rc > 0) {
		for (i = 0; i < set->num_items; i++) {
			if (readable && set->items[i].revents & ZMQ_POLLIN) {
				zval *zv = s_zval_for_index(set, i);

				if (zv) {
					Z_ADDREF_P(zv);
					add_next_index_zval(r_array, zv);
				}
			}

			if (writable && set->items[i].revents & ZMQ_POLLOUT) {
				zval *zv = s_zval_for_index(set, i);
				if (zv) {
					Z_ADDREF_P(zv);
					add_next_index_zval(w_array, zv);
				}
			}

			if (set->items[i].revents & ZMQ_POLLERR) {
				add_next_index_str(&set->errors, zend_string_copy(set->keys[i]));
			}
		}
	}
	return rc;
}

void php_zmq_pollset_clear(php_zmq_pollset *set)
{
	// Clear errors
	zend_hash_clean(Z_ARRVAL(set->errors));

	// clear the pollset
	s_pollset_clear(set, 1);
}

zval *php_zmq_pollset_errors(php_zmq_pollset *set)
{
	return &set->errors;
}

void php_zmq_pollset_destroy(php_zmq_pollset **ptr)
{
	php_zmq_pollset *set = *ptr;

	// clear the pollset
	s_pollset_clear(set, 0);

	// Errors
	zval_dtor(&(set->errors));

	efree(set);
	*ptr = NULL;
}

