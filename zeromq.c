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

#include "php_zeromq.h"
#include "php_zeromq_private.h"

zend_class_entry *php_zeromq_sc_entry;
zend_class_entry *php_zeromq_poll_sc_entry;

zend_class_entry *php_zeromq_exception_sc_entry;
zend_class_entry *php_zeromq_poll_exception_sc_entry;

static zend_object_handlers zeromq_object_handlers;
static zend_object_handlers zeromq_poll_object_handlers;

ZEND_DECLARE_MODULE_GLOBALS(zeromq);

#ifndef Z_ADDREF_P
# define Z_ADDREF_P(pz) (pz)->refcount++
#endif

#ifndef Z_DELREF_P
# define Z_DELREF_P(pz) (pz)->refcount--
#endif

#ifndef Z_REFCOUNT_P
# define Z_REFCOUNT_P(pz) (pz)->refcount
#endif

static int le_zeromq_socket, le_zeromq_context;

/** {{{ static int php_zeromq_socket_list_entry(void)
*/
static int php_zeromq_socket_list_entry(void)
{
	return le_zeromq_socket;
}
/* }}} */

/* {{{ static int php_zeromq_context_list_entry(void)
*/
static int php_zeromq_context_list_entry(void)
{
	return le_zeromq_context;
}
/* }}} */

/* {{{ static void php_zeromq_context_destroy(php_zeromq_context *ctx, zend_bool is_persistent)
	Destroy the zeromq context and free memory associated
*/
static void php_zeromq_context_destroy(php_zeromq_context *ctx, zend_bool is_persistent)
{
	php_zeromq_printf("php_zeromq_context_destroy(ctx=[%p], persistent=[%d])\n", ctx, is_persistent);
		
	(void) zmq_term(ctx->context);
	pefree(ctx, is_persistent);
}
/* }}} */

/* {{{ static php_zeromq_context *php_zeromq_context_new(int app_threads, int io_threads, zend_bool poll, zend_bool persistent TSRMLS_DC)
	Create a new zeromq context
*/
static php_zeromq_context *php_zeromq_context_new(int app_threads, int io_threads, zend_bool poll, zend_bool persistent TSRMLS_DC)
{
	php_zeromq_context *ctx;
	
	php_zeromq_printf("php_zeromq_context_new(app_threads=[%d], io_threads=[%d], persistent=[%d])\n", app_threads, io_threads, persistent);
	
	ctx          = pecalloc(1, sizeof(php_zeromq_context), persistent);
	ctx->context = zmq_init(app_threads, io_threads, poll);
	
	if (!ctx->context) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error creating context: %s", zmq_strerror(errno));
	}
	
	ctx->is_persistent = persistent;
	return ctx;
}
/* }}} */

/* {{{ static php_zeromq_context *php_zeromq_context_get(int app_threads, int io_threads, zend_bool poll, zend_bool persistent TSRMLS_DC)
	Get a context. If context does not exist in persistent list allocates a new one
*/
static php_zeromq_context *php_zeromq_context_get(int app_threads, int io_threads, zend_bool poll, zend_bool persistent TSRMLS_DC)
{
	php_zeromq_context *ctx;

	char *plist_key;
	int plist_key_len;
	zend_rsrc_list_entry le, *le_p = NULL;
	
	php_zeromq_printf("php_zeromq_context_get(app_threads=[%d], io_threads=[%d], persistent=[%d])\n", app_threads, io_threads, persistent);
	
	if (persistent) {
		plist_key_len  = spprintf(&plist_key, 0, "zeromq_context:[%d]-[%d]-[%d]", app_threads, io_threads, poll);
		plist_key_len += 1;

		if (zend_hash_find(&EG(persistent_list), plist_key, plist_key_len, (void *)&le_p) == SUCCESS) {
			if (le_p->type == php_zeromq_context_list_entry()) {
				efree(plist_key);
				return (php_zeromq_context *) le_p->ptr;
			}
		}
	}
	
	ctx = php_zeromq_context_new(app_threads, io_threads, poll, persistent);

	if (persistent) {
		le.type = php_zeromq_context_list_entry();
		le.ptr  = ctx;

		if (zend_hash_update(&EG(persistent_list), (char *)plist_key, plist_key_len, (void *)&le, sizeof(le), NULL) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Could not register persistent entry");
		}
		efree(plist_key);
	}
	return ctx;
}
/* }}} */

/* {{{ static php_zeromq_socket *php_zeromq_socket_new(int type, int app_threads, int io_threads, zend_bool poll, zend_bool persistent TSRMLS_DC)
	Create a new zeromq socket
*/
static php_zeromq_socket *php_zeromq_socket_new(int type, int app_threads, int io_threads, zend_bool poll, zend_bool persistent TSRMLS_DC)
{
	php_zeromq_socket *zmq_sock = pecalloc(1, sizeof(php_zeromq_socket), persistent);

	php_zeromq_printf("php_zeromq_socket_new(type=[%d], app_threads=[%d], io_threads=[%d], persistent=[%d])\n", type, app_threads, io_threads, persistent);

	zmq_sock->ctx    = php_zeromq_context_get(app_threads, io_threads, poll, ZEROMQ_G(persist_context) TSRMLS_CC);
	zmq_sock->socket = zmq_socket(zmq_sock->ctx->context, (int) type);
	
	if (!zmq_sock->socket) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error creating socket: %s", zmq_strerror(errno));
	}
	
	zmq_sock->is_persistent = persistent;
	zmq_sock->app_threads   = app_threads;
	zmq_sock->io_threads    = io_threads;
	zmq_sock->type          = type;
	
	zend_hash_init(&(zmq_sock->connect), 0, NULL, NULL, persistent);
	zend_hash_init(&(zmq_sock->bind), 0, NULL, NULL, persistent);
	return zmq_sock;
}
/* }}} */

/* {{{ static php_zeromq_socket *php_zeromq_socket_get(int type, const char *p_id, int app_threads, int io_threads, zend_bool persistent TSRMLS_DC)
	Tries to get context from plist and allocates a new context if context does not exist
*/
static php_zeromq_socket *php_zeromq_socket_get(int type, const char *p_id, int app_threads, int io_threads, zend_bool poll, zend_bool persistent TSRMLS_DC)
{
	php_zeromq_socket *zmq_sock_p;

	char *plist_key;
	int plist_key_len;
	
	php_zeromq_printf("php_zeromq_socket_get(type=[%d], p_id=[%s], app_threads=[%d], io_threads=[%d], persistent=[%d])\n", type, p_id, app_threads, io_threads, persistent);

	if (persistent) {
		zend_rsrc_list_entry *le = NULL;

		plist_key_len  = spprintf(&plist_key, 0, "zeromq_socket:[%d]-[%s]", type, p_id);
		plist_key_len += 1;
		
		if (zend_hash_find(&EG(persistent_list), plist_key, plist_key_len, (void *)&le) == SUCCESS) {
			if (le->type == php_zeromq_socket_list_entry()) {
				efree(plist_key);
				return (php_zeromq_socket *) le->ptr;
			}
		}	
	}
	zmq_sock_p = php_zeromq_socket_new(type, app_threads, io_threads, poll, persistent TSRMLS_CC);
	
	if (persistent) {
		zend_rsrc_list_entry le;

		le.type = php_zeromq_socket_list_entry();
		le.ptr  = zmq_sock_p;
		
		if (zend_hash_update(&EG(persistent_list), (char *)plist_key, plist_key_len, (void *)&le, sizeof(le), NULL) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Could not register persistent entry");
		}
		efree(plist_key);
	}
	return zmq_sock_p;	
}
/* }}} */

/* {{{ static void php_zeromq_socket_destroy(php_zeromq_socket *zmq_sock, zend_bool is_persistent)
	Destroy the socket (note: does not touch context)
*/
static void php_zeromq_socket_destroy(php_zeromq_socket *zmq_sock, zend_bool is_persistent)
{
	php_zeromq_printf("php_zeromq_socket_destroy(zmq_sock=[%p], persistent=[%d])\n", zmq_sock, is_persistent);
	
	zend_hash_destroy(&(zmq_sock->connect));
	zend_hash_destroy(&(zmq_sock->bind));
	
	(void) zmq_close(zmq_sock->socket);
	pefree(zmq_sock, is_persistent);
}
/* }}} */

/* -- START ZeroMQ --- */

/* {{{ ZeroMQ::__construct(int type[, string persistent_id])
	Build a new ZeroMQSocket object
*/
PHP_METHOD(zeromq, __construct)
{
	php_zeromq_object *intern;
	long type;
	char *p_id = NULL;
	int p_id_len = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|s!", &type, &p_id, &p_id_len) == FAILURE) {
		return;
	}

	intern       = PHP_ZEROMQ_OBJECT;
	intern->type = type;
	
	if (p_id) {
		intern->p_id = estrdup(p_id);
	}
	return;
}
/* }}} */

/* {{{ ZeroMQ ZeroMQ::send(string message)
	Send a message
*/
PHP_METHOD(zeromq, send)
{
	php_zeromq_object *intern;
	char *message_param; 
	
	zmq_msg_t message;
	int rc, message_param_len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &message_param, &message_param_len) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;

	if (zmq_msg_init_size(&message, message_param_len) != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to initialize message structure: %s", zmq_strerror(errno));
		return;
	}
	memcpy(zmq_msg_data(&message), message_param, message_param_len);
	
	rc = zmq_send(intern->zms->socket, &message, zmq_msg_size(&message));
	zmq_msg_close(&message);
	
	if (rc != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to send message: %s", zmq_strerror(errno));
		return;
	}
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* {{{ string ZeroMQ::recv()
	Receive a message
*/
PHP_METHOD(zeromq, recv)
{
	php_zeromq_object *intern;
	zmq_msg_t message;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;

	if (zmq_msg_init(&message) != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to initialize message structure: %s", zmq_strerror(errno));
		return;
	}
	
	if (zmq_recv(intern->zms->socket, &message, 0) != 0) {
		zmq_msg_close(&message);
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to receive message: %s", zmq_strerror(errno));
		return;
	}

	ZVAL_STRINGL(return_value, zmq_msg_data(&message), zmq_msg_size(&message), 1);	
	zmq_msg_close(&message);
	return;
}
/* }}} */

/* {{{ ZeroMQ::setContextOptions(int app_threads, int io_threads[, boolean poll = false])
	Set options for the internal context
*/
PHP_METHOD(zeromq, setcontextoptions)
{
	php_zeromq_object *intern;
	long app_threads, io_threads;
	zend_bool poll = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll|b", &app_threads, &io_threads, &poll) == FAILURE) {
		return;
	}

	intern = PHP_ZEROMQ_OBJECT;
	
	if (intern->zms) {
		zend_throw_exception(php_zeromq_exception_sc_entry, "Context options must be set before connect, bind or setSockOpt", 1 TSRMLS_CC);
		return;
	}
	
	if (app_threads <= 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, 33 TSRMLS_CC, "The first argument must be greater than zero, %ld given", app_threads);
		return;
	}
	
	if (io_threads <= 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, 33 TSRMLS_CC, "The second argument must greater than zero, %ld given", app_threads);
		return;
	}

	/* Socket is created on-demand in connect / bind */
	intern->app_threads = app_threads;
	intern->io_threads  = io_threads;
	intern->poll        = poll;
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/** {{{ array ZeroMQSocket::getContextOptions() 
	Returns the amount of app and io threads in the internal context
*/
PHP_METHOD(zeromq, getcontextoptions)
{
	php_zeromq_object *intern;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	array_init(return_value);
	
	add_assoc_long(return_value, "app_threads", ((intern->zms) ? intern->zms->app_threads : intern->app_threads));
	add_assoc_long(return_value, "io_threads",  ((intern->zms) ? intern->zms->io_threads  : intern->io_threads));
	return;
}
/* }}} */

/* {{{ ZeroMQSocket::bind(string dsn[, bool force_new_connection])
	Bind the socket to an endpoint
*/
PHP_METHOD(zeromq, bind)
{
	php_zeromq_object *intern;
	char *dsn;
	int dsn_len;
	zend_bool force = 0;
	void *dummy = (void *)1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &dsn, &dsn_len, &force) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	if (!intern->zms) {
		/* Socket is persisted only if context is persistent */
		zend_bool persistent = (intern->p_id && ZEROMQ_G(persist_context));
		intern->zms          = php_zeromq_socket_get(intern->type, intern->p_id, intern->app_threads, intern->io_threads, intern->poll, persistent TSRMLS_CC);
	}
	
	/* already connected ? */
	if (!force && zend_hash_exists(&(intern->zms->bind), dsn, dsn_len + 1)) {
		ZEROMQ_RETURN_THIS;
	}

	if (zmq_bind(intern->zms->socket, dsn) != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to bind the ZeroMQSocket: %s", zmq_strerror(errno));
		return;
	}

	zend_hash_add(&(intern->zms->bind), dsn, dsn_len + 1, (void *)&dummy, sizeof(void *), NULL);
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* {{{ ZeroMQSocket::connect(string dsn[, bool force_new_connection])
	Connect the socket to an endpoint
*/
PHP_METHOD(zeromq, connect)
{
	php_zeromq_object *intern;
	char *dsn;
	int dsn_len;
	zend_bool force = 0;
	void *dummy = (void *)1;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &dsn, &dsn_len, &force) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	if (!intern->zms) {
		/* Socket is persisted only if context is persistent */
		zend_bool persistent = (intern->p_id && ZEROMQ_G(persist_context));
		intern->zms          = php_zeromq_socket_get(intern->type, intern->p_id, intern->app_threads, intern->io_threads, intern->poll, persistent TSRMLS_CC);
	}
	
	/* already connected ? */
	if (!force && zend_hash_exists(&(intern->zms->connect), dsn, dsn_len + 1)) {
		ZEROMQ_RETURN_THIS;
	}

	if (zmq_connect(intern->zms->socket, dsn) != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to connect the ZeroMQSocket: %s", zmq_strerror(errno));
		return;
	}

	zend_hash_add(&(intern->zms->connect), dsn, dsn_len + 1, (void *)&dummy, sizeof(void *), NULL);
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* {{{ static int php_zeromq_get_keys(zval **ppzval TSRMLS_DC, int num_args, va_list args, zend_hash_key *hash_key) */
static int php_zeromq_get_keys(zval **ppzval TSRMLS_DC, int num_args, va_list args, zend_hash_key *hash_key)
{
	zval *retval;
	
	if (num_args != 1) {
		/* Incorrect args ? */
		return ZEND_HASH_APPLY_KEEP;
	}
	
	retval = va_arg(args, zval *);
	
	if (hash_key->nKeyLength == 0) {
		return ZEND_HASH_APPLY_REMOVE;
	}
	
	add_next_index_stringl(retval, hash_key->arKey, hash_key->nKeyLength - 1, 1);
	return ZEND_HASH_APPLY_KEEP;
}
/* }}} */

/* {{{ array ZeroMQSocket::getEndpoints()
	Returns endpoints where this socket is connected/bound to. Contains two keys ('bind', 'connect')
*/
PHP_METHOD(zeromq, getendpoints)
{
	php_zeromq_object *intern;
	zval *connect, *bind;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	array_init(return_value);
	
	MAKE_STD_ZVAL(connect);
	MAKE_STD_ZVAL(bind);
	
	array_init(connect);
	array_init(bind);
	
	if (!intern->zms) {
		add_assoc_zval(return_value, "connect", connect);
		add_assoc_zval(return_value, "bind", bind);
		return; /* No endpoints */
	}
	
	zend_hash_apply_with_arguments(&(intern->zms->connect) TSRMLS_CC, (apply_func_args_t) php_zeromq_get_keys, 1, connect);
	zend_hash_apply_with_arguments(&(intern->zms->bind) TSRMLS_CC, (apply_func_args_t) php_zeromq_get_keys, 1, bind);

	add_assoc_zval(return_value, "connect", connect);
	add_assoc_zval(return_value, "bind", bind);
	return;
}
/* }}} */

/* {{{ int ZeroMQSocket::getSocketType()
	Returns the socket type
*/
PHP_METHOD(zeromq, getsockettype)
{
	php_zeromq_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	/* intern->type should always match intern->zms->type */
	RETURN_LONG(intern->type);
}
/* }}} */


/* {{{ ZeroMQSocket::setSockOpt(int ZeroMQ::SOCKOPT_, mixed value)
	Set a socket option
*/
PHP_METHOD(zeromq, setsockopt)
{
	php_zeromq_object *intern;
	long key;
	zval *pz_value;
	int status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &key, &pz_value) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	if (!intern->zms) {
		/* Socket is persisted only if context is persistent */
		zend_bool persistent = (intern->p_id && ZEROMQ_G(persist_context));
		intern->zms          = php_zeromq_socket_get(intern->type, intern->p_id, intern->app_threads, intern->io_threads, intern->poll, persistent TSRMLS_CC);
	}
	
	switch (key) {
		
		case ZMQ_HWM:
		case ZMQ_LWM:
		case ZMQ_SWAP:
		case ZMQ_AFFINITY:
		{
			int64_t value;
			convert_to_long(pz_value);
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->zms->socket, key, &value, sizeof(int64_t));
		}
		break;
		
		case ZMQ_IDENTITY:
		case ZMQ_SUBSCRIBE:
		case ZMQ_UNSUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->zms->socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));
		}
		break;
		
		case ZMQ_RATE:
		case ZMQ_RECOVERY_IVL:
		case ZMQ_MCAST_LOOP:
		case ZMQ_SNDBUF:
		case ZMQ_RCVBUF:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			if (Z_LVAL_P(pz_value) < 0) {
				zend_throw_exception(php_zeromq_exception_sc_entry, "The option value must be a positive integer", 1 TSRMLS_CC);
				return;
			}
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->zms->socket, key, &value, sizeof(uint64_t));
		}
		break;
		
		default:
		{
			zend_throw_exception(php_zeromq_exception_sc_entry, "Unknown option key", 1 TSRMLS_CC);
			return;
		}
		break;
	}
	
	if (status != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to set socket option: %s", zmq_strerror(errno));
		return;
	}
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* -- END ZeroMQSocket --- */

/* -- START ZeroMQPoll --- */

PHP_METHOD(zeromqpoll, add)
{
	php_zeromq_poll_object *intern;
	php_zeromq_object *socket;
	
	zval *object;
	long type;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Ol", &object, php_zeromq_sc_entry, &type) == FAILURE) {
		return;
	}

	socket = (php_zeromq_object *)zend_object_store_get_object(object TSRMLS_CC);

	if (!socket->zms) {
		zend_throw_exception(php_zeromq_poll_exception_sc_entry, "The socket has not been initialized yet", 1 TSRMLS_CC);
		return;
	}
	
	if (!socket->poll) {
		zend_throw_exception(php_zeromq_poll_exception_sc_entry, "The socket has not been initialized with polling", 1 TSRMLS_CC);
		return;
	}
	
	intern = PHP_ZEROMQ_POLL_OBJECT;
	
	Z_ADDREF_P(object);
	
	intern->items   = erealloc(intern->items,   (intern->num_items + 1) * sizeof(zmq_pollitem_t));
	intern->objects = erealloc(intern->objects, (intern->num_items + 1) * sizeof(zval *));

	intern->items[intern->num_items].socket = socket->zms->socket;
	intern->items[intern->num_items].events = type;
	
	intern->objects[intern->num_items++]     = object;
	ZEROMQ_RETURN_THIS;
}

PHP_METHOD(zeromqpoll, poll)
{
	php_zeromq_poll_object *intern;
	
	long timeout = -1;
	zval *readable, *writable;
	int rc, i;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa|l", &readable, &writable, &timeout) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_POLL_OBJECT;
	
	if (intern->num_items == 0) {
		zend_throw_exception(php_zeromq_poll_exception_sc_entry, "No sockets assigned to the ZeroMQPoll", 1 TSRMLS_CC);
		return;
	}

	rc = zmq_poll(intern->items, intern->num_items, timeout);
	
	if (rc == -1) {
		zend_throw_exception_ex(php_zeromq_poll_exception_sc_entry, errno TSRMLS_CC, "Poll failed: %s", zmq_strerror(errno));
		return;
	}
	
	array_init(readable);
	array_init(writable);
	
	for (i = 0; i < intern->num_items; i++) {
		if (intern->items[i].revents & ZMQ_POLLIN) {
			add_next_index_zval(readable, intern->objects[i]);
		} 
		
		if (intern->items[i].revents & ZMQ_POLLOUT) {
			add_next_index_zval(writable, intern->objects[i]);
		}
		
		if (intern->items[i].revents & ZMQ_POLLERR) {
			// todo: errors
		}
	}
	RETURN_TRUE;
}

/* -- END ZeroMQPoll */

ZEND_BEGIN_ARG_INFO_EX(zeromq_construct_args, 0, 0, 2)	
	ZEND_ARG_INFO(0, type)
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_bind_args, 0, 0, 1)	
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_connect_args, 0, 0, 1)	
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_setsockopt_args, 0, 0, 2)	
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_getcontextoptions_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_setcontextoptions_args, 0, 0, 2)
	ZEND_ARG_INFO(0, app_threads)
	ZEND_ARG_INFO(0, io_threads)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_getendpoints_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_getsockettype_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_send_args, 0, 0, 1)
	ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_recv_args, 0, 0, 0)
ZEND_END_ARG_INFO()

static function_entry php_zeromq_class_methods[] = {
	PHP_ME(zeromq, __construct,			zeromq_construct_args,			ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(zeromq, send,				zeromq_send_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, recv,				zeromq_recv_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, bind,				zeromq_bind_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, connect,				zeromq_connect_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, setsockopt,			zeromq_setsockopt_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, getcontextoptions,	zeromq_getcontextoptions_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, setcontextoptions,	zeromq_setcontextoptions_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, getendpoints,		zeromq_getendpoints_args,		ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, getsockettype,		zeromq_getsockettype_args,		ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

ZEND_BEGIN_ARG_INFO_EX(zeromq_poll_add_args, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, ZeroMQ, ZeroMQ, 0)
	ZEND_ARG_INFO(0, type) 
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_poll_poll_args, 0, 0, 2)
	ZEND_ARG_INFO(1, readable) 
	ZEND_ARG_INFO(1, writable) 
ZEND_END_ARG_INFO()

static function_entry php_zeromq_poll_class_methods[] = {
	PHP_ME(zeromqpoll, add,				zeromq_poll_add_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zeromqpoll, poll,			zeromq_poll_poll_args,	ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

zend_function_entry zeromq_functions[] = {
	{NULL, NULL, NULL} 
};

static void php_zeromq_object_free_storage(void *object TSRMLS_DC)
{
	php_zeromq_object *intern = (php_zeromq_object *)object;

	if (!intern) {
		return;
	}

	if (intern->p_id) {
		efree(intern->p_id);
	}
	
	if (intern->zms && !intern->zms->is_persistent) {
		if (intern->zms->ctx && !intern->zms->ctx->is_persistent) {
			php_zeromq_context_destroy(intern->zms->ctx, intern->zms->ctx->is_persistent);
		}
		php_zeromq_socket_destroy(intern->zms, intern->zms->is_persistent);
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}

static void php_zeromq_poll_object_free_storage(void *object TSRMLS_DC)
{
	php_zeromq_poll_object *intern = (php_zeromq_poll_object *)object;

	if (!intern) {
		return;
	}
	
	if (intern->num_items > 0) {
		int i;
		
		for (i = 0; i < intern->num_items; i++) {
			Z_DELREF_P(intern->objects[i]);
			
			if (Z_REFCOUNT_P(intern->objects[i]) <= 0) {
				zval_dtor(intern->objects[i]);
				FREE_ZVAL(intern->objects[i]);
			}
		}
		efree(intern->objects);
		efree(intern->items);
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}

static zend_object_value php_zeromq_object_new_ex(zend_class_entry *class_type, php_zeromq_object **ptr TSRMLS_DC)
{
	zval *tmp;
	zend_object_value retval;
	php_zeromq_object *intern;

	/* Allocate memory for it */
	intern = (php_zeromq_object *) emalloc(sizeof(php_zeromq_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	intern->zms         = NULL;
	intern->p_id        = NULL;
	intern->app_threads = 1;
	intern->io_threads  = 1;
	intern->type        = -1;
	intern->poll        = 0;
	
	if (ptr) {
		*ptr = intern;
	}

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	zend_hash_copy(intern->zo.properties, &class_type->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_zeromq_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &zeromq_object_handlers;
	return retval;
}

static zend_object_value php_zeromq_poll_object_new_ex(zend_class_entry *class_type, php_zeromq_poll_object **ptr TSRMLS_DC)
{
	zval *tmp;
	zend_object_value retval;
	php_zeromq_poll_object *intern;

	/* Allocate memory for it */
	intern = (php_zeromq_poll_object *) emalloc(sizeof(php_zeromq_poll_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	intern->items     = NULL;
	intern->objects   = NULL;
	intern->num_items = 0;

	if (ptr) {
		*ptr = intern;
	}

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	zend_hash_copy(intern->zo.properties, &class_type->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_zeromq_poll_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &zeromq_poll_object_handlers;
	return retval;
}

static zend_object_value php_zeromq_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zeromq_object_new_ex(class_type, NULL TSRMLS_CC);
}

static zend_object_value php_zeromq_poll_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zeromq_poll_object_new_ex(class_type, NULL TSRMLS_CC);
}

ZEND_RSRC_DTOR_FUNC(php_zeromq_socket_dtor)
{
	if (rsrc->ptr) {
		php_zeromq_socket *zms = (php_zeromq_socket *)rsrc->ptr;
		php_zeromq_socket_destroy(zms, zms->is_persistent);
		rsrc->ptr = NULL;
	}
}

ZEND_RSRC_DTOR_FUNC(php_zeromq_context_dtor)
{
	if (rsrc->ptr) {
		php_zeromq_context *ctx = (php_zeromq_context *)rsrc->ptr;
		php_zeromq_context_destroy(ctx, ctx->is_persistent);
		rsrc->ptr = NULL;
	}
}

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("zeromq.persist_context", "1", PHP_INI_ALL, OnUpdateBool, persist_context, zend_zeromq_globals, zeromq_globals)
PHP_INI_END()

static void php_zeromq_init_globals(zend_zeromq_globals *zeromq_globals)
{
	zeromq_globals->persist_context = 1;
}

PHP_MINIT_FUNCTION(zeromq)
{
	zend_class_entry ce;
	
	ZEND_INIT_MODULE_GLOBALS(zeromq, php_zeromq_init_globals, NULL);
	REGISTER_INI_ENTRIES();
	
	le_zeromq_socket  = zend_register_list_destructors_ex(NULL, php_zeromq_socket_dtor, "ZeroMQ persistent socket", module_number);
	le_zeromq_context = zend_register_list_destructors_ex(NULL, php_zeromq_context_dtor, "ZeroMQ persistent context", module_number);

	memcpy(&zeromq_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&zeromq_poll_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	
	INIT_CLASS_ENTRY(ce, "ZeroMQ", php_zeromq_class_methods);
	ce.create_object = php_zeromq_object_new;
	zeromq_object_handlers.clone_obj = NULL;
	php_zeromq_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);

	INIT_CLASS_ENTRY(ce, "ZeroMQPoll", php_zeromq_poll_class_methods);
	ce.create_object = php_zeromq_poll_object_new;
	zeromq_poll_object_handlers.clone_obj = NULL;
	php_zeromq_poll_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);

	INIT_CLASS_ENTRY(ce, "ZeroMQException", NULL);
	php_zeromq_exception_sc_entry = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);
	php_zeromq_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL;

	INIT_CLASS_ENTRY(ce, "ZeroMQPollException", NULL);
	php_zeromq_poll_exception_sc_entry = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);
	php_zeromq_poll_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL;
	
#define PHP_ZEROMQ_REGISTER_CONST_LONG(const_name, value) \
	zend_declare_class_constant_long(php_zeromq_sc_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);	
	
	/* Socket constants */
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKET_P2P", ZMQ_P2P);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKET_PUB", ZMQ_PUB);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKET_SUB", ZMQ_SUB);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKET_REQ", ZMQ_REQ);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKET_REP", ZMQ_REP);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKET_XREQ", ZMQ_XREQ);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKET_XREP", ZMQ_XREP);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKET_UPSTREAM", ZMQ_UPSTREAM);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKET_DOWNSTREAM", ZMQ_DOWNSTREAM);
	
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKOPT_HWM", ZMQ_HWM);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKOPT_LWM", ZMQ_LWM);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKOPT_SWAP", ZMQ_SWAP);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKOPT_AFFINITY", ZMQ_AFFINITY);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKOPT_IDENTITY", ZMQ_IDENTITY);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKOPT_SUBSCRIBE", ZMQ_SUBSCRIBE);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKOPT_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKOPT_RATE", ZMQ_RATE);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKOPT_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKOPT_MCAST_LOOP", ZMQ_MCAST_LOOP);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKOPT_SNDBUF", ZMQ_SNDBUF);
	PHP_ZEROMQ_REGISTER_CONST_LONG("SOCKOPT_RCVBUF", ZMQ_RCVBUF);
	
	PHP_ZEROMQ_REGISTER_CONST_LONG("POLL_IN", ZMQ_POLLIN);
	PHP_ZEROMQ_REGISTER_CONST_LONG("POLL_OUT", ZMQ_POLLOUT);
	
#undef PHP_ZEROMQ_REGISTER_CONST_LONG

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(zeromq)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_MINFO_FUNCTION(zeromq)
{
	char *version;
	int major = 0, minor = 0, patch = 0;
	
	zmq_version(&major, &minor, &patch);
	(void) spprintf(&version, 0, "%d.%d.%d", major, minor, patch);
	
	php_info_print_table_start();

		php_info_print_table_header(2, "ZeroMQ extension", "enabled");
		php_info_print_table_row(2, "ZeroMQ extension version", PHP_ZEROMQ_EXTVER);
		php_info_print_table_row(2, "libzmq version", version);

	php_info_print_table_end();

	efree(version);
	DISPLAY_INI_ENTRIES();
}

zend_module_entry zeromq_module_entry =
{
        STANDARD_MODULE_HEADER,
        PHP_ZEROMQ_EXTNAME,
        zeromq_functions,		/* Functions */
        PHP_MINIT(zeromq),		/* MINIT */
        PHP_MSHUTDOWN(zeromq),	/* MSHUTDOWN */
        NULL,					/* RINIT */
        NULL,					/* RSHUTDOWN */
        PHP_MINFO(zeromq),		/* MINFO */
        PHP_ZEROMQ_EXTVER,		/* version */
        STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ZEROMQ
ZEND_GET_MODULE(zeromq)
#endif /* COMPILE_DL_ZEROMQ */