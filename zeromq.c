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

#define PHP_ZEROMQ_BUF_SIZE 512

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

/* {{{ static void php_zeromq_context_destroy(php_zeromq_context *ctx)
	Destroy the zeromq context and free memory associated
*/
static void php_zeromq_context_destroy(php_zeromq_context *ctx)
{	
	(void) zmq_term(ctx->context);
	pefree(ctx, ctx->opts.is_persistent);
}
/* }}} */

/* {{{ static php_zeromq_context *php_zeromq_context_new(php_zeromq_context_opts *ctx_opts TSRMLS_DC)
	Create a new zeromq context
*/
static php_zeromq_context *php_zeromq_context_new(php_zeromq_context_opts *ctx_opts TSRMLS_DC)
{
	php_zeromq_context *ctx;

	ctx          = pecalloc(1, sizeof(php_zeromq_context), ctx_opts->is_persistent);
	ctx->context = zmq_init(ctx_opts->app_threads, ctx_opts->io_threads, ctx_opts->poll);
	
	if (!ctx->context) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error creating context: %s", zmq_strerror(errno));
	}
	
	memcpy(&(ctx->opts), ctx_opts, sizeof(php_zeromq_context_opts));
	return ctx;
}
/* }}} */

/* {{{ static php_zeromq_context *php_zeromq_context_get(php_zeromq_context_opts *ctx_opts TSRMLS_DC)
	Get a context. If context does not exist in persistent list allocates a new one
*/
static php_zeromq_context *php_zeromq_context_get(php_zeromq_context_opts *ctx_opts TSRMLS_DC)
{
	php_zeromq_context *ctx;

	char *plist_key;
	int plist_key_len;
	zend_rsrc_list_entry le, *le_p = NULL;

	if (ctx_opts->is_persistent) {
		plist_key_len  = spprintf(&plist_key, 0, "zeromq_context:[%d]-[%d]-[%d]", ctx_opts->app_threads, ctx_opts->io_threads, ctx_opts->poll);
		plist_key_len += 1;

		if (zend_hash_find(&EG(persistent_list), plist_key, plist_key_len, (void *)&le_p) == SUCCESS) {
			if (le_p->type == php_zeromq_context_list_entry()) {
				efree(plist_key);
				return (php_zeromq_context *) le_p->ptr;
			}
		}
	}
	
	ctx = php_zeromq_context_new(ctx_opts);

	if (ctx_opts->is_persistent) {
		le.type = php_zeromq_context_list_entry();
		le.ptr  = ctx;

		if (zend_hash_update(&EG(persistent_list), (char *)plist_key, plist_key_len, (void *)&le, sizeof(le), NULL) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Could not register persistent entry for the context");
		}
		efree(plist_key);
	}
	return ctx;
}
/* }}} */

/* {{{ static php_zeromq_socket *php_zeromq_socket_new(php_zeromq_socket_opts *socket_opts, php_zeromq_context_opts *ctx_opts TSRMLS_DC)
	Create a new zeromq socket
*/
static php_zeromq_socket *php_zeromq_socket_new(php_zeromq_socket_opts *socket_opts, php_zeromq_context_opts *ctx_opts TSRMLS_DC)
{
	php_zeromq_socket *zmq_sock = pecalloc(1, sizeof(php_zeromq_socket), socket_opts->is_persistent);

	zmq_sock->ctx    = php_zeromq_context_get(ctx_opts TSRMLS_CC);
	zmq_sock->socket = zmq_socket(zmq_sock->ctx->context, socket_opts->type);
	
	if (!zmq_sock->socket) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error creating socket: %s", zmq_strerror(errno));
	}

	/* Copy the socket options */
	zmq_sock->opts.type          = socket_opts->type;
	zmq_sock->opts.is_persistent = socket_opts->is_persistent;
	zmq_sock->opts.p_id          = (socket_opts->p_id) ? pestrdup(socket_opts->p_id, socket_opts->is_persistent) : NULL;

	zend_hash_init(&(zmq_sock->connect), 0, NULL, NULL, socket_opts->is_persistent);
	zend_hash_init(&(zmq_sock->bind), 0, NULL, NULL, socket_opts->is_persistent);
	return zmq_sock;
}
/* }}} */

/* {{{ static php_zeromq_socket *php_zeromq_socket_get(php_zeromq_socket_opts *socket_opts, php_zeromq_context_opts *ctx_opts TSRMLS_DC)
	Tries to get context from plist and allocates a new context if context does not exist
*/
static php_zeromq_socket *php_zeromq_socket_get(php_zeromq_socket_opts *socket_opts, php_zeromq_context_opts *ctx_opts TSRMLS_DC)
{
	php_zeromq_socket *zmq_sock_p;

	char *plist_key;
	int plist_key_len;
	
	/* Socket is persistent if we got persistent id and context is persistent */
	socket_opts->is_persistent = (socket_opts->p_id && ctx_opts->is_persistent);
	
	if (socket_opts->is_persistent) {
		zend_rsrc_list_entry *le = NULL;

		plist_key_len  = spprintf(&plist_key, 0, "zeromq_socket:[%d]-[%s]", socket_opts->type, socket_opts->p_id);
		plist_key_len += 1;
		
		if (zend_hash_find(&EG(persistent_list), plist_key, plist_key_len, (void *)&le) == SUCCESS) {
			if (le->type == php_zeromq_socket_list_entry()) {
				efree(plist_key);
				return (php_zeromq_socket *) le->ptr;
			}
		}	
	}
	zmq_sock_p = php_zeromq_socket_new(socket_opts, ctx_opts TSRMLS_CC);
	
	if (socket_opts->is_persistent) {
		zend_rsrc_list_entry le;

		le.type = php_zeromq_socket_list_entry();
		le.ptr  = zmq_sock_p;
		
		if (zend_hash_update(&EG(persistent_list), (char *)plist_key, plist_key_len, (void *)&le, sizeof(le), NULL) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Could not register persistent entry for the socket");
		}
		efree(plist_key);
	}
	return zmq_sock_p;	
}
/* }}} */

/* {{{ static void php_zeromq_socket_destroy(php_zeromq_socket *zmq_sock)
	Destroy the socket (note: does not touch context)
*/
static void php_zeromq_socket_destroy(php_zeromq_socket *zmq_sock)
{
	zend_hash_destroy(&(zmq_sock->connect));
	zend_hash_destroy(&(zmq_sock->bind));
	
	if (zmq_sock->opts.p_id) {
		pefree(zmq_sock->opts.p_id, zmq_sock->opts.is_persistent);
	}
	
	(void) zmq_close(zmq_sock->socket);
	pefree(zmq_sock, zmq_sock->opts.is_persistent);
}
/* }}} */

/* -- START ZeroMQ --- */

/* {{{ ZeroMQ::__construct(int type[, string persistent_id])
	Build a new ZeroMQ object
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

	intern                   = PHP_ZEROMQ_OBJECT;
	intern->socket_opts.type = type;
	
	if (p_id && p_id_len > 0) {
		intern->socket_opts.p_id = estrdup(p_id);
	}
	return;
}
/* }}} */

/* {{{ ZeroMQ ZeroMQ::send(string message[, int flags = 0])
	Send a message
*/
PHP_METHOD(zeromq, send)
{
	php_zeromq_object *intern;
	char *message_param; 
	
	zmq_msg_t message;
	int rc, message_param_len;
	long flags = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &message_param, &message_param_len, &flags) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	if (!intern->zms) {
		zend_throw_exception(php_zeromq_poll_exception_sc_entry, "The socket has not been initialized yet", 1 TSRMLS_CC);
		return;
	}

	if (zmq_msg_init_size(&message, message_param_len) != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to initialize message structure: %s", zmq_strerror(errno));
		return;
	}
	memcpy(zmq_msg_data(&message), message_param, message_param_len);
	
	rc = zmq_send(intern->zms->socket, &message, flags);
	zmq_msg_close(&message);
	
	if (rc != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to send message: %s", zmq_strerror(errno));
		return;
	}
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* {{{ string ZeroMQ::recv([int $flags = 0])
	Receive a message
*/
PHP_METHOD(zeromq, recv)
{
	php_zeromq_object *intern;
	zmq_msg_t message;
	long flags = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &flags) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	if (!intern->zms) {
		zend_throw_exception(php_zeromq_poll_exception_sc_entry, "The socket has not been initialized yet", 1 TSRMLS_CC);
		return;
	}

	if (zmq_msg_init(&message) != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to initialize message structure: %s", zmq_strerror(errno));
		return;
	}
	
	if (zmq_recv(intern->zms->socket, &message, flags) != 0) {
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
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, 34 TSRMLS_CC, "The second argument must greater than zero, %ld given", app_threads);
		return;
	}

	/* Socket is created on-demand in connect / bind */
	intern->ctx_opts.app_threads = app_threads;
	intern->ctx_opts.io_threads  = io_threads;
	intern->ctx_opts.poll        = poll;
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/** {{{ array ZeroMQ::getContextOptions() 
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
	
	/*
		If socket has not been initialised yet, return the context options from the main object
	*/
	add_assoc_long(return_value, "app_threads", ((intern->zms) ? intern->zms->ctx->opts.app_threads : intern->ctx_opts.app_threads));
	add_assoc_long(return_value, "io_threads",  ((intern->zms) ? intern->zms->ctx->opts.io_threads  : intern->ctx_opts.io_threads));
	add_assoc_bool(return_value, "poll",        ((intern->zms) ? intern->zms->ctx->opts.poll        : intern->ctx_opts.poll));
	return;
}
/* }}} */

/** {{{ string ZeroMQ::getPersistentId() 
	Returns the persistent id of the object
*/
PHP_METHOD(zeromq, getpersistentid)
{
	php_zeromq_object *intern;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	if (intern->socket_opts.p_id) {
		/* Return the id */
		RETURN_STRING(intern->socket_opts.p_id, 1);
	}
	return;
}
/* }}} */

/* {{{ ZeroMQ::bind(string dsn[, bool force_new_connection])
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
		intern->zms = php_zeromq_socket_get(&(intern->socket_opts), &(intern->ctx_opts) TSRMLS_CC);
	}
	
	/* already connected ? */
	if (!force && zend_hash_exists(&(intern->zms->bind), dsn, dsn_len + 1)) {
		ZEROMQ_RETURN_THIS;
	}

	if (zmq_bind(intern->zms->socket, dsn) != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to bind the ZeroMQ: %s", zmq_strerror(errno));
		return;
	}

	zend_hash_add(&(intern->zms->bind), dsn, dsn_len + 1, (void *)&dummy, sizeof(void *), NULL);
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* {{{ ZeroMQ::connect(string dsn[, bool force_new_connection])
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
		intern->zms = php_zeromq_socket_get(&(intern->socket_opts), &(intern->ctx_opts) TSRMLS_CC);
	}
	
	/* already connected ? */
	if (!force && zend_hash_exists(&(intern->zms->connect), dsn, dsn_len + 1)) {
		ZEROMQ_RETURN_THIS;
	}

	if (zmq_connect(intern->zms->socket, dsn) != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to connect the ZeroMQ: %s", zmq_strerror(errno));
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
		/* Should not happen */
		return ZEND_HASH_APPLY_REMOVE;
	}
	
	add_next_index_stringl(retval, hash_key->arKey, hash_key->nKeyLength - 1, 1);
	return ZEND_HASH_APPLY_KEEP;
}
/* }}} */

/* {{{ array ZeroMQ::getEndpoints()
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

/* {{{ int ZeroMQ::getSocketType()
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
	RETURN_LONG(intern->socket_opts.type);
}
/* }}} */

/* {{{ ZeroMQ ZeroMQ::setSockOpt(int ZeroMQ::SOCKOPT_, mixed value)
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
		intern->zms = php_zeromq_socket_get(&(intern->socket_opts), &(intern->ctx_opts) TSRMLS_CC);
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

#ifdef HAVE_ZMQ_GETSOCKOPT
/* {{{ mixed ZeroMQ::getSockOpt()
	Get a socket option
*/
PHP_METHOD(zeromq, getsockopt)
{
	php_zeromq_object *intern;
	long key;
	size_t value_len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &key) == FAILURE) {
		return;
	}

	intern = PHP_ZEROMQ_OBJECT;
	
	if (!intern->zms) {
		zend_throw_exception(php_zeromq_exception_sc_entry, "The socket has not been initialized yet", 1 TSRMLS_CC);
		return;
	}
	
	switch (key) {
		
		case ZMQ_HWM:
		case ZMQ_LWM:
		case ZMQ_SWAP:
		case ZMQ_AFFINITY:
		{
			int64_t value;
			value_len = sizeof(int64_t);
			if (zmq_getsockopt (intern->zms->socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to get the option value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_IDENTITY:
		{
			int rc = 0, i = 1;
			unsigned char *value = NULL;
			
			do {
				value_len = PHP_ZEROMQ_BUF_SIZE * i++;
				value     = emalloc(value_len);
				rc        = zmq_getsockopt (intern->zms->socket, (int) key, value, &value_len);
			} while (rc == -1 && errno == EINVAL);

			RETURN_STRINGL((char *)value, value_len, 1);
		}
		break;
		
		case ZMQ_RATE:
		case ZMQ_RECOVERY_IVL:
		case ZMQ_MCAST_LOOP:
		case ZMQ_SNDBUF:
		case ZMQ_RCVBUF:
		{
			uint64_t value;
			value = sizeof(uint64_t);
			if (zmq_getsockopt (intern->zms->socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to get the option value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SUBSCRIBE:
		case ZMQ_UNSUBSCRIBE:
			zend_throw_exception(php_zeromq_exception_sc_entry, "Retrieving SOCKOPT_SUBSCRIBE and SOCKOPT_UNSUBSCRIBE is not support", 1 TSRMLS_CC);
			return;
		break;
		
		default:
		{
			zend_throw_exception(php_zeromq_exception_sc_entry, "Unknown option key", 1 TSRMLS_CC);
			return;
		}
		break;
	}
}
/* }}} */
#endif

/* -- END ZeroMQ --- */

/* -- START ZeroMQPoll --- */

/* {{{ ZeroMQPoll ZeroMQPoll::add(ZeroMQ $object, int events)
	Add a ZeroMQ object into the pollset
*/
PHP_METHOD(zeromqpoll, add)
{
	php_zeromq_poll_object *intern;
	php_zeromq_object *item;
	
	zval *object;
	long type;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Ol", &object, php_zeromq_sc_entry, &type) == FAILURE) {
		return;
	}

	item = (php_zeromq_object *)zend_object_store_get_object(object TSRMLS_CC);

	if (!item->zms) {
		zend_throw_exception(php_zeromq_poll_exception_sc_entry, "The socket has not been initialized yet", 1 TSRMLS_CC);
		return;
	}
	
	if (!item->ctx_opts.poll) {
		zend_throw_exception(php_zeromq_poll_exception_sc_entry, "The socket has not been initialized with polling", 1 TSRMLS_CC);
		return;
	}
	
	intern = PHP_ZEROMQ_POLL_OBJECT;
	
	intern->items   = erealloc(intern->items,   (intern->num_items + 1) * sizeof(zmq_pollitem_t));
	intern->objects = erealloc(intern->objects, (intern->num_items + 1) * sizeof(zval *));

	intern->items[intern->num_items].socket = item->zms->socket;
	intern->items[intern->num_items].events = type;
	
	intern->objects[intern->num_items++] = object;
	zend_objects_store_add_ref(object TSRMLS_CC);
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* {{{ boolean ZeroMQPoll::poll(array &$readable, array &$writable[, int timeout = -1])
	Poll the sockets
*/
PHP_METHOD(zeromqpoll, poll)
{
	php_zeromq_poll_object *intern;
	zval *r_array, *w_array;
	
	long timeout = -1;
	int rc, i;
	
	zend_bool readable = 0, writable = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a!a!|l", &r_array, &w_array, &timeout) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_POLL_OBJECT;
	
	if (intern->num_items == 0) {
		zend_throw_exception(php_zeromq_poll_exception_sc_entry, "No sockets assigned to the ZeroMQPoll", 1 TSRMLS_CC);
		return;
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
	
	rc = zmq_poll(intern->items, intern->num_items, timeout);
	
	if (rc == -1) {
		zend_throw_exception_ex(php_zeromq_poll_exception_sc_entry, errno TSRMLS_CC, "Poll failed: %s", zmq_strerror(errno));
		return;
	}

	for (i = 0; i < intern->num_items; i++) {
		if (readable && intern->items[i].revents & ZMQ_POLLIN) {
			Z_ADDREF_P(intern->objects[i]);
			add_next_index_zval(r_array, intern->objects[i]);
		} 
		
		if (writable && intern->items[i].revents & ZMQ_POLLOUT) {
			Z_ADDREF_P(intern->objects[i]);
			add_next_index_zval(w_array, intern->objects[i]);
		}
		
		if (intern->items[i].revents & ZMQ_POLLERR) {
			// todo: errors
		}
	}
	RETURN_TRUE;
}
/* }}} */

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
	ZEND_ARG_INFO(0, poll)
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

ZEND_BEGIN_ARG_INFO_EX(zeromq_getpersistentid_args, 0, 0, 0)
ZEND_END_ARG_INFO()

#ifdef HAVE_ZMQ_GETSOCKOPT
ZEND_BEGIN_ARG_INFO_EX(zeromq_getsockopt_args, 0, 0, 0)
ZEND_END_ARG_INFO()
#endif

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
	PHP_ME(zeromq, getpersistentid,		zeromq_getpersistentid_args,	ZEND_ACC_PUBLIC)
#ifdef HAVE_ZMQ_GETSOCKOPT
	PHP_ME(zeromq, getsockopt,			zeromq_getsockopt_args,			ZEND_ACC_PUBLIC)
#endif
	{NULL, NULL, NULL}
};

ZEND_BEGIN_ARG_INFO_EX(zeromq_poll_add_args, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, ZeroMQ, ZeroMQ, 0)
	ZEND_ARG_INFO(0, type) 
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_poll_poll_args, 0, 0, 2)
	ZEND_ARG_INFO(0, readable) 
	ZEND_ARG_INFO(0, writable) 
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

	if (intern->socket_opts.p_id) {
		efree(intern->socket_opts.p_id);
	}
	
	if (intern->zms && !intern->zms->opts.is_persistent) {
		if (intern->zms->ctx && !intern->zms->ctx->opts.is_persistent) {
			php_zeromq_context_destroy(intern->zms->ctx);
		}
		php_zeromq_socket_destroy(intern->zms);
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
			zend_objects_store_del_ref(intern->objects[i] TSRMLS_CC);
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

	intern->zms  = NULL;
	
	/* Initialize socket options */
	intern->socket_opts.p_id = NULL;
	intern->socket_opts.type = -1;
	
	/* Initialized the context options */
	intern->ctx_opts.app_threads   = 1;
	intern->ctx_opts.io_threads    = 1;
	intern->ctx_opts.poll          = 0;
	intern->ctx_opts.is_persistent = ZEROMQ_G(persist_context);
	
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
		php_zeromq_socket_destroy(zms);
		rsrc->ptr = NULL;
	}
}

ZEND_RSRC_DTOR_FUNC(php_zeromq_context_dtor)
{
	if (rsrc->ptr) {
		php_zeromq_context *ctx = (php_zeromq_context *)rsrc->ptr;
		php_zeromq_context_destroy(ctx);
		rsrc->ptr = NULL;
	}
}

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("zeromq.persist_context", "1", PHP_INI_SYSTEM, OnUpdateBool, persist_context, zend_zeromq_globals, zeromq_globals)
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
	
	PHP_ZEROMQ_REGISTER_CONST_LONG("MODE_NOBLOCK", ZMQ_NOBLOCK);
	
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