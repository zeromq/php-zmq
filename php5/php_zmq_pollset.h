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

#ifndef _PHP_ZMQ_POLLSET_H_
# define _PHP_ZMQ_POLLSET_H_

#define PHP_ZMQ_POLLSET_ERR_NO_STREAM    -1
#define PHP_ZMQ_POLLSET_ERR_CANNOT_CAST  -2
#define PHP_ZMQ_POLLSET_ERR_CAST_FAILED  -3
#define PHP_ZMQ_POLLSET_ERR_NO_INIT      -4
#define PHP_ZMQ_POLLSET_ERR_NO_POLL      -5
#define PHP_ZMQ_POLLSET_ERR_KEY_FAIL     -6
#define PHP_ZMQ_POLLSET_ERR_INVALID_TYPE -7

/** {{{ void php_zmq_pollset_init(php_zmq_pollset *set);
*/
void php_zmq_pollset_init(php_zmq_pollset *set);
/* }}} */

/** {{{ void php_zmq_pollset_deinit(php_zmq_pollset *set TSRMLS_DC);
*/
void php_zmq_pollset_deinit(php_zmq_pollset *set TSRMLS_DC);
/* }}} */

/** {{{ void php_zmq_pollset_clear(php_zmq_pollset *set, zend_bool reinit);
*/
void php_zmq_pollset_clear(php_zmq_pollset *set, zend_bool reinit TSRMLS_DC);
/* }}} */

/** {{{ int php_zmq_pollset_add(php_zmq_pollset *set, zval *entry, int events TSRMLS_DC);
*/
int php_zmq_pollset_add(php_zmq_pollset *set, zval *entry, int events TSRMLS_DC);
/* }}} */

/** {{{ void php_zmq_pollset_rebuild(php_zmq_pollset *set);
*/
void php_zmq_pollset_rebuild(php_zmq_pollset *set);
/* }}} */

/** {{{ zend_bool php_zmq_pollset_delete(php_zmq_pollset *set, zval *entry TSRMLS_DC);
*/
zend_bool php_zmq_pollset_delete(php_zmq_pollset *set, zval *entry TSRMLS_DC);
/* }}} */

/** {{{ int php_zmq_pollset_poll(php_zmq_pollset *set, int timeout, zval *r_array, zval *w_array, zval *e_array);
*/
int php_zmq_pollset_poll(php_zmq_pollset *set, int timeout, zval *r_array, zval *w_array, zval *e_array);
/* }}} */

/** {{{ zend_bool php_zmq_pollset_get_key(php_zmq_pollset *set, int pos, char key[35], int *key_len TSRMLS_DC);
*/
zend_bool php_zmq_pollset_get_key(php_zmq_pollset *set, int pos, char key[35], int *key_len TSRMLS_DC);
/* }}} */

/** {{{ zend_bool php_zmq_pollset_delete_by_key(php_zmq_pollset *set, char key[35], int key_len TSRMLS_DC);
*/
zend_bool php_zmq_pollset_delete_by_key(php_zmq_pollset *set, char key[35], int key_len TSRMLS_DC);
/* }}} */

/** {{{ void php_zmq_pollset_delete_all(php_zmq_pollset *set TSRMLS_DC);
*/
void php_zmq_pollset_delete_all(php_zmq_pollset *set TSRMLS_DC);
/* }}} */

#endif /* _PHP_ZMQ_POLLSET_H_ */
