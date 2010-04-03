/*
+-----------------------------------------------------------------------------------+
|  ZeroMQ extension for PHP                                                         |
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

#ifndef _PHP_ZEROMQ_PRIVATE_H_
# define _PHP_ZEROMQ_PRIVATE_H_

#include "ext/standard/info.h"
#include "Zend/zend_exceptions.h"
#include "php_ini.h"

#include <stdint.h>
#include <zmq.h>

/* {{{ */
typedef struct _php_zeromq_context {
	void *context;
	zend_bool is_persistent;
} php_zeromq_context;
/* }}} */

/* {{{ typedef struct _php_zeromq_socket */
typedef struct _php_zeromq_socket  {
	void *socket;
	php_zeromq_context *ctx;
	zend_bool is_persistent;
	
	HashTable connect;
	HashTable bind;
	
	int app_threads;
	int io_threads;
} php_zeromq_socket;
/* }}} */

/* {{{ typedef struct _php_zeromq_object */
typedef struct _php_zeromq_object  {
	zend_object zo;
	zval *sock_obj;
} php_zeromq_object;
/* }}} */

/* {{{ typedef struct _php_zeromq_socket_object */
typedef struct _php_zeromq_socket_object  {
	zend_object zo;
	php_zeromq_socket *zms;
	char *p_id;
	
	int type;
	int app_threads;
	int io_threads;
} php_zeromq_socket_object;
/* }}} */

ZEND_BEGIN_MODULE_GLOBALS(zeromq)
	zend_bool persist_context;
ZEND_END_MODULE_GLOBALS(zeromq)

ZEND_EXTERN_MODULE_GLOBALS(zeromq);

#ifdef ZTS
# define ZEROMQ_G(v) TSRMG(zeromq_globals_id, zend_zeromq_globals *, v)
#else
# define ZEROMQ_G(v) (zeromq_globals.v)
#endif

#define PHP_ZEROMQ_OBJECT (php_zeromq_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

#define PHP_ZEROMQ_SOCKET_OBJECT (php_zeromq_socket_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

#define ZEROMQ_RETURN_THIS RETURN_ZVAL(getThis(), 1, 0);

#ifdef _DEBUG_ZEROMQ_
# define php_zeromq_printf(fmt, ...) fprintf (stderr, fmt, __VA_ARGS__)
#else
# define php_zeromq_printf(...)
#endif

#endif /* _PHP_ZEROMQ_PRIVATE_H_ */