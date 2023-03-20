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

#ifndef _PHP_ZMQ_PRIVATE_H_
# define _PHP_ZMQ_PRIVATE_H_

#include "ext/standard/info.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_llist.h"
#include "main/php_ini.h"

#include <zmq.h>

#ifdef HAVE_CZMQ
# include <czmq.h>
# if CZMQ_VERSION_MAJOR >= 2
#  define HAVE_CZMQ_2
# endif
#endif

#if (PHP_VERSION_ID < 80000) && defined(PHP_WIN32)
# include "win32/php_stdint.h"
#else
# include <stdint.h>
#endif

typedef struct _php_zmq_pollset php_zmq_pollset;

/* {{{ typedef struct _php_zmq_context
*/
typedef struct _php_zmq_context {
	/* zmq context */
	void *z_ctx;

	/* Amount of io-threads */
	int io_threads;

	/* Is this a persistent context */
	zend_bool is_persistent;

	/* Should this context live to end of process */
	zend_bool use_shared_ctx;

	/* How many active sockets */
	zend_long socket_count;

	/* Who created me */
	int pid;
} php_zmq_context;
/* }}} */

/* {{{ typedef struct _php_zmq_socket
*/
typedef struct _php_zmq_socket  {
	void *z_socket;
	int socket_type;
	php_zmq_context *ctx;

	HashTable connect;
	HashTable bind;

	zend_bool is_persistent;

	/* Who created me */
	int pid;
} php_zmq_socket;
/* }}} */

/* {{{ typedef struct _php_zmq_context_object 
*/
typedef struct _php_zmq_context_object  {
	php_zmq_context *context;
	zend_object zo;
} php_zmq_context_object;

/* }}} */

/* {{{ typedef struct _php_zmq_socket_object 
*/
typedef struct _php_zmq_socket_object  {
	php_zmq_socket *socket;

	/* options for the context */
	char *persistent_id;

	/* zval of the context */
	zval context_obj;
	zend_object zo;
} php_zmq_socket_object;
/* }}} */

/* {{{ typedef struct _php_zmq_poll_object 
*/
typedef struct _php_zmq_poll_object  {
	php_zmq_pollset *set;
	zend_object zo;
} php_zmq_poll_object;
/* }}} */

typedef struct _php_zmq_device_cb_t {
	zend_bool initialized;
	long timeout;
	zend_fcall_info fci;
	zend_fcall_info_cache fci_cache;
	zval user_data;
	uint64_t scheduled_at;
} php_zmq_device_cb_t;

/* {{{ typedef struct _php_zmq_device_object 
*/
typedef struct _php_zmq_device_object  {
	php_zmq_device_cb_t idle_cb;
	php_zmq_device_cb_t timer_cb;

	zval front;
	zval back;
	zval capture;
	zend_object zo;
} php_zmq_device_object;
/* }}} */

#ifdef ZTS
# define ZMQ_G(v) TSRMG(php_zmq_globals_id, zend_php_zmq_globals *, v)
#else
# define ZMQ_G(v) (php_zmq_globals.v)
#endif

#define ZMQ_RETURN_THIS RETURN_ZVAL(getThis(), 1, 0);

#define PHP_ZMQ_ERROR_HANDLING_INIT() zend_error_handling error_handling;

#define PHP_ZMQ_ERROR_HANDLING_THROW() zend_replace_error_handling(EH_THROW, php_zmq_socket_exception_sc_entry, &error_handling);

#define PHP_ZMQ_ERROR_HANDLING_RESTORE() zend_restore_error_handling(&error_handling);

/* Compatibility macros between zeromq 2.x and 3.x */
#ifndef ZMQ_DONTWAIT
#	define ZMQ_DONTWAIT ZMQ_NOBLOCK
#endif
#ifndef ZMQ_HWM
#   define ZMQ_HWM (ZMQ_DONTWAIT + 2000)
#endif
#ifndef ZMQ_FORWARDER
#   define ZMQ_FORWARDER 0
#endif
#ifndef ZMQ_QUEUE
#   define ZMQ_QUEUE 0
#endif
#ifndef ZMQ_STREAMER
#   define ZMQ_STREAMER 0
#endif
#if ZMQ_VERSION_MAJOR == 2
#	define zmq_sendmsg zmq_send
#	define zmq_recvmsg zmq_recv
#	define PHP_ZMQ_TIMEOUT 1000
#else
#	define PHP_ZMQ_TIMEOUT 1
#endif

#define PHP_ZMQ_INTERNAL_ERROR -99

PHP_METHOD(zmqsocket, getsockopt);
PHP_METHOD(zmqsocket, setsockopt);
zend_bool php_zmq_device(php_zmq_device_object *intern);

zend_class_entry *php_zmq_socket_exception_sc_entry_get ();
zend_class_entry *php_zmq_device_exception_sc_entry_get ();

php_stream *php_zmq_create_zmq_fd(zval *obj);

void php_zmq_register_sockopt_constants (zend_class_entry *ce);

typedef struct _php_zmq_clock_ctx_t php_zmq_clock_ctx_t;

php_zmq_clock_ctx_t *php_zmq_clock_init ();

uint64_t php_zmq_clock (php_zmq_clock_ctx_t *clock_ctx);

void php_zmq_clock_destroy (php_zmq_clock_ctx_t **clock_ctx);

char *php_zmq_get_libzmq_version();

zend_long php_zmq_get_libzmq_version_id();

char *php_zmq_printable_func (zend_fcall_info *fci, zend_fcall_info_cache *fci_cache);


zend_bool php_zmq_shared_ctx_init();

void php_zmq_shared_ctx_assign_to(php_zmq_context *context);

void php_zmq_shared_ctx_destroy();

int php_zmq_shared_ctx_socket_count();

void php_zmq_shared_ctx_socket_count_incr();

void php_zmq_shared_ctx_socket_count_decr();




ZEND_BEGIN_MODULE_GLOBALS(php_zmq)
	php_zmq_clock_ctx_t *clock_ctx;
ZEND_END_MODULE_GLOBALS(php_zmq)

#ifdef HAVE_CZMQ_2

# define PHP_ZMQ_AUTH_TYPE_PLAIN 0
# define PHP_ZMQ_AUTH_TYPE_CURVE 1

typedef struct _php_zmq_cert {
	zcert_t *zcert;
	zend_object zo;
} php_zmq_cert_object;

typedef struct _php_zmq_auth {
	zctx_t *shadow_context;
	zauth_t *zauth;
	zend_object zo;
} php_zmq_auth_object;
#endif

#endif /* _PHP_ZMQ_PRIVATE_H_ */
