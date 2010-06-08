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

zend_class_entry *php_zmq_sc_entry;
zend_class_entry *php_zmq_context_sc_entry;
zend_class_entry *php_zmq_poll_sc_entry;

zend_class_entry *php_zmq_exception_sc_entry;
zend_class_entry *php_zmq_context_exception_sc_entry;
zend_class_entry *php_zmq_poll_exception_sc_entry;

static zend_object_handlers zmq_object_handlers;
static zend_object_handlers zmq_context_object_handlers;
static zend_object_handlers zmq_poll_object_handlers;

ZEND_DECLARE_MODULE_GLOBALS(php_zmq);

#define PHP_ZMQ_IDENITTY_SIZE 255

#ifndef Z_ADDREF_P
# define Z_ADDREF_P(pz) (pz)->refcount++
#endif

#ifndef Z_DELREF_P
# define Z_DELREF_P(pz) (pz)->refcount--
#endif

#ifndef Z_REFCOUNT_P
# define Z_REFCOUNT_P(pz) (pz)->refcount
#endif

/* list entries */
static int le_zmq_socket, le_zmq_context;

/** {{{ static int php_zmq_socket_list_entry(void)
*/
static int php_zmq_socket_list_entry(void)
{
	return le_zmq_socket;
}
/* }}} */

/* {{{ static int php_zmq_context_list_entry(void)
*/
static int php_zmq_context_list_entry(void)
{
	return le_zmq_context;
}
/* }}} */

/* {{{ static void php_zmq_socket_opts_copy(php_zmq_socket_opts *target, php_zmq_socket_opts *source) 
*/
static void php_zmq_socket_opts_copy(php_zmq_socket_opts *target, php_zmq_socket_opts *source) 
{
	target->type          = source->type;
	target->is_persistent = source->is_persistent;
	target->p_id          = (source->p_id) ? pestrdup(source->p_id, source->is_persistent) : NULL;
}
/* }}} */

/* {{{ static void php_zmq_context_opts_copy(php_zmq_context_opts *target, php_zmq_context_opts *source)
*/
static void php_zmq_context_opts_copy(php_zmq_context_opts *target, php_zmq_context_opts *source) 
{
	memcpy(target, source, sizeof(php_zmq_context_opts));
}
/* }}} */

/* {{{ static void php_zmq_context_destroy(php_zmq_context *ctx)
	Destroy the zmq context and free memory associated
*/
static void php_zmq_context_destroy(php_zmq_context *ctx)
{	
	(void) zmq_term(ctx->context);
	pefree(ctx, ctx->opts.is_persistent);
}
/* }}} */

/* {{{ static php_zmq_context *php_zmq_context_new(php_zmq_context_opts *ctx_opts TSRMLS_DC)
	Create a new zmq context
*/
static php_zmq_context *php_zmq_context_new(php_zmq_context_opts *ctx_opts TSRMLS_DC)
{
	php_zmq_context *ctx;

	ctx          = pecalloc(1, sizeof(php_zmq_context), ctx_opts->is_persistent);
	ctx->context = zmq_init(ctx_opts->io_threads);
	
	if (!ctx->context) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error creating context: %s", zmq_strerror(errno));
	}
	
	php_zmq_context_opts_copy(&(ctx->opts), ctx_opts);
	return ctx;
}
/* }}} */

/* {{{ static php_zmq_context *php_zmq_context_get(php_zmq_context_opts *ctx_opts TSRMLS_DC)
	Get a context. If context does not exist in persistent list allocates a new one
*/
static php_zmq_context *php_zmq_context_get(php_zmq_context_opts *ctx_opts TSRMLS_DC)
{
	php_zmq_context *ctx;

	char *plist_key;
	int plist_key_len;
	zend_rsrc_list_entry le, *le_p = NULL;

	if (ctx_opts->is_persistent) {
		plist_key_len  = spprintf(&plist_key, 0, "zmq_context:[%d]", ctx_opts->io_threads);
		plist_key_len += 1;

		if (zend_hash_find(&EG(persistent_list), plist_key, plist_key_len, (void *)&le_p) == SUCCESS) {
			if (le_p->type == php_zmq_context_list_entry()) {
				efree(plist_key);
				return (php_zmq_context *) le_p->ptr;
			}
		}
	}
	
	ctx = php_zmq_context_new(ctx_opts TSRMLS_CC);

	if (ctx_opts->is_persistent) {
		le.type = php_zmq_context_list_entry();
		le.ptr  = ctx;

		if (zend_hash_update(&EG(persistent_list), (char *)plist_key, plist_key_len, (void *)&le, sizeof(le), NULL) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Could not register persistent entry for the context");
		}
		efree(plist_key);
	}
	return ctx;
}
/* }}} */

/* {{{ static php_zmq_socket *php_zmq_socket_new(php_zmq_socket_opts *socket_opts, php_zmq_context_opts *ctx_opts TSRMLS_DC)
	Create a new zmq socket
*/
static php_zmq_socket *php_zmq_socket_new(php_zmq_socket_opts *socket_opts, php_zmq_context_opts *ctx_opts TSRMLS_DC)
{
	php_zmq_socket *zmq_sock = pecalloc(1, sizeof(php_zmq_socket), socket_opts->is_persistent);

	zmq_sock->ctx    = php_zmq_context_get(ctx_opts TSRMLS_CC);
	zmq_sock->socket = zmq_socket(zmq_sock->ctx->context, socket_opts->type);
	
	if (!zmq_sock->socket) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Error creating socket: %s", zmq_strerror(errno));
	}

	/* Copy the socket options */
	php_zmq_socket_opts_copy(&(zmq_sock->opts), socket_opts);

	zend_hash_init(&(zmq_sock->connect), 0, NULL, NULL, socket_opts->is_persistent);
	zend_hash_init(&(zmq_sock->bind), 0, NULL, NULL, socket_opts->is_persistent);
	return zmq_sock;
}
/* }}} */

/* {{{ static php_zmq_socket *php_zmq_socket_get(php_zmq_socket_opts *socket_opts, php_zmq_context_opts *ctx_opts TSRMLS_DC)
	Tries to get context from plist and allocates a new context if context does not exist
*/
static php_zmq_socket *php_zmq_socket_get(php_zmq_socket_opts *socket_opts, php_zmq_context_opts *ctx_opts TSRMLS_DC)
{
	php_zmq_socket *zmq_sock_p;

	char *plist_key;
	int plist_key_len;
	
	/* Socket is persistent if we got persistent id and context is persistent */
	socket_opts->is_persistent = (socket_opts->p_id && ctx_opts->is_persistent);
	
	if (socket_opts->is_persistent) {
		zend_rsrc_list_entry *le = NULL;

		plist_key_len  = spprintf(&plist_key, 0, "zmq_socket:[%d]-[%s]", socket_opts->type, socket_opts->p_id);
		plist_key_len += 1;
		
		if (zend_hash_find(&EG(persistent_list), plist_key, plist_key_len, (void *)&le) == SUCCESS) {
			if (le->type == php_zmq_socket_list_entry()) {
				efree(plist_key);
				return (php_zmq_socket *) le->ptr;
			}
		}	
	}
	zmq_sock_p = php_zmq_socket_new(socket_opts, ctx_opts TSRMLS_CC);
	
	if (socket_opts->is_persistent) {
		zend_rsrc_list_entry le;

		le.type = php_zmq_socket_list_entry();
		le.ptr  = zmq_sock_p;
		
		if (zend_hash_update(&EG(persistent_list), (char *)plist_key, plist_key_len, (void *)&le, sizeof(le), NULL) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Could not register persistent entry for the socket");
		}
		efree(plist_key);
	}
	return zmq_sock_p;	
}
/* }}} */

/* {{{ static void php_zmq_socket_destroy(php_zmq_socket *zmq_sock)
	Destroy the socket (note: does not touch context)
*/
static void php_zmq_socket_destroy(php_zmq_socket *zmq_sock)
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

/* -- START ZMQ --- */

/* {{{ ZMQ ZMQ::__construct(integer $type[, string $persistent_id = null])
	Build a new ZMQ object
*/
PHP_METHOD(zmq, __construct)
{
	php_zmq_object *intern;
	long type;
	char *p_id = NULL;
	int p_id_len = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|s!", &type, &p_id, &p_id_len) == FAILURE) {
		return;
	}

	intern                   = PHP_ZMQ_OBJECT;
	intern->socket_opts.type = type;
	
	if (p_id && p_id_len > 0) {
		intern->socket_opts.p_id = estrdup(p_id);
	}
	return;
}
/* }}} */

/* {{{ ZMQ ZMQ::send(string $message[, integer $flags = 0])
	Send a message
*/
PHP_METHOD(zmq, send)
{
	php_zmq_object *intern;
	char *message_param; 
	
	zmq_msg_t message;
	int rc, message_param_len;
	long flags = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &message_param, &message_param_len, &flags) == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_OBJECT;
	
	if (!intern->zms) {
		zend_throw_exception(php_zmq_poll_exception_sc_entry, "The socket has not been initialized yet", 1 TSRMLS_CC);
		return;
	}

	if (zmq_msg_init_size(&message, message_param_len) != 0) {
		zend_throw_exception_ex(php_zmq_exception_sc_entry, errno TSRMLS_CC, "Failed to initialize message structure: %s", zmq_strerror(errno));
		return;
	}
	memcpy(zmq_msg_data(&message), message_param, message_param_len);
	
	rc = zmq_send(intern->zms->socket, &message, flags);
	zmq_msg_close(&message);
	
	if (rc != 0) {
		zend_throw_exception_ex(php_zmq_exception_sc_entry, errno TSRMLS_CC, "Failed to send message: %s", zmq_strerror(errno));
		return;
	}
	ZMQ_RETURN_THIS;
}
/* }}} */

/* {{{ string ZMQ::recv([integer $flags = 0])
	Receive a message
*/
PHP_METHOD(zmq, recv)
{
	php_zmq_object *intern;
	zmq_msg_t message;
	long flags = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &flags) == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_OBJECT;
	
	if (!intern->zms) {
		zend_throw_exception(php_zmq_poll_exception_sc_entry, "The socket has not been initialized yet", 1 TSRMLS_CC);
		return;
	}

	if (zmq_msg_init(&message) != 0) {
		zend_throw_exception_ex(php_zmq_exception_sc_entry, errno TSRMLS_CC, "Failed to initialize message structure: %s", zmq_strerror(errno));
		return;
	}
	
	if (zmq_recv(intern->zms->socket, &message, flags) != 0) {
		zmq_msg_close(&message);
		zend_throw_exception_ex(php_zmq_exception_sc_entry, errno TSRMLS_CC, "Failed to receive message: %s", zmq_strerror(errno));
		return;
	}

	ZVAL_STRINGL(return_value, zmq_msg_data(&message), zmq_msg_size(&message), 1);	
	zmq_msg_close(&message);
	return;
}
/* }}} */

/* {{{ ZMQ ZMQ::setContextOptions(integer $io_threads)
	Set options for the internal context
*/
PHP_METHOD(zmq, setcontextoptions)
{
	php_zmq_object *intern;
	long io_threads;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &io_threads) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_OBJECT;
	
	if (intern->zms) {
		zend_throw_exception(php_zmq_exception_sc_entry, "Context options must be set before connect, bind or setSockOpt", 1 TSRMLS_CC);
		return;
	}

	if (io_threads <= 0) {
		zend_throw_exception_ex(php_zmq_exception_sc_entry, 34 TSRMLS_CC, "The io_threads argument must greater than zero, %ld given", io_threads);
		return;
	}

	/* Socket is created on-demand in connect / bind */
	intern->ctx_opts.io_threads  = io_threads;
	ZMQ_RETURN_THIS;
}
/* }}} */

/** {{{ array ZMQ::getContextOptions() 
	Returns the amount of app and io threads in the internal context
*/
PHP_METHOD(zmq, getcontextoptions)
{
	php_zmq_object *intern;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_OBJECT;
	array_init(return_value);
	
	/*
		If socket has not been initialised yet, return the context options from the main object
	*/
	add_assoc_long(return_value, "io_threads",  ((intern->zms) ? intern->zms->ctx->opts.io_threads  : intern->ctx_opts.io_threads));
	return;
}
/* }}} */

/** {{{ string ZMQ::getPersistentId() 
	Returns the persistent id of the object
*/
PHP_METHOD(zmq, getpersistentid)
{
	php_zmq_object *intern;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_OBJECT;
	
	if (intern->socket_opts.p_id) {
		/* Return the id */
		RETURN_STRING(intern->socket_opts.p_id, 1);
	}
	return;
}
/* }}} */

/* {{{ ZMQ ZMQ::bind(string $dsn[, boolean $force = false])
	Bind the socket to an endpoint
*/
PHP_METHOD(zmq, bind)
{
	php_zmq_object *intern;
	char *dsn;
	int dsn_len;
	zend_bool force = 0;
	void *dummy = (void *)1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &dsn, &dsn_len, &force) == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_OBJECT;
	
	if (!intern->zms) {
		/* Socket is persisted only if context is persistent */
		intern->zms = php_zmq_socket_get(&(intern->socket_opts), &(intern->ctx_opts) TSRMLS_CC);
	}
	
	/* already connected ? */
	if (!force && zend_hash_exists(&(intern->zms->bind), dsn, dsn_len + 1)) {
		ZMQ_RETURN_THIS;
	}

	if (zmq_bind(intern->zms->socket, dsn) != 0) {
		zend_throw_exception_ex(php_zmq_exception_sc_entry, errno TSRMLS_CC, "Failed to bind the ZMQ: %s", zmq_strerror(errno));
		return;
	}

	zend_hash_add(&(intern->zms->bind), dsn, dsn_len + 1, (void *)&dummy, sizeof(void *), NULL);
	ZMQ_RETURN_THIS;
}
/* }}} */

/* {{{ ZMQ ZMQ::connect(string $dsn[, boolean $force = false])
	Connect the socket to an endpoint
*/
PHP_METHOD(zmq, connect)
{
	php_zmq_object *intern;
	char *dsn;
	int dsn_len;
	zend_bool force = 0;
	void *dummy = (void *)1;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &dsn, &dsn_len, &force) == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_OBJECT;
	
	if (!intern->zms) {
		/* Socket is persisted only if context is persistent */
		intern->zms = php_zmq_socket_get(&(intern->socket_opts), &(intern->ctx_opts) TSRMLS_CC);
	}
	
	/* already connected ? */
	if (!force && zend_hash_exists(&(intern->zms->connect), dsn, dsn_len + 1)) {
		ZMQ_RETURN_THIS;
	}

	if (zmq_connect(intern->zms->socket, dsn) != 0) {
		zend_throw_exception_ex(php_zmq_exception_sc_entry, errno TSRMLS_CC, "Failed to connect the ZMQ: %s", zmq_strerror(errno));
		return;
	}

	zend_hash_add(&(intern->zms->connect), dsn, dsn_len + 1, (void *)&dummy, sizeof(void *), NULL);
	ZMQ_RETURN_THIS;
}
/* }}} */

/* {{{ static int php_zmq_get_keys(zval **ppzval TSRMLS_DC, int num_args, va_list args, zend_hash_key *hash_key) */
static int php_zmq_get_keys(zval **ppzval TSRMLS_DC, int num_args, va_list args, zend_hash_key *hash_key)
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

/* {{{ array ZMQ::getEndpoints()
	Returns endpoints where this socket is connected/bound to. Contains two keys ('bind', 'connect')
*/
PHP_METHOD(zmq, getendpoints)
{
	php_zmq_object *intern;
	zval *connect, *bind;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_OBJECT;
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
	
	zend_hash_apply_with_arguments(&(intern->zms->connect) TSRMLS_CC, (apply_func_args_t) php_zmq_get_keys, 1, connect);
	zend_hash_apply_with_arguments(&(intern->zms->bind) TSRMLS_CC, (apply_func_args_t) php_zmq_get_keys, 1, bind);

	add_assoc_zval(return_value, "connect", connect);
	add_assoc_zval(return_value, "bind", bind);
	return;
}
/* }}} */

/* {{{ integer ZMQ::getSocketType()
	Returns the socket type
*/
PHP_METHOD(zmq, getsockettype)
{
	php_zmq_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_OBJECT;
	
	/* intern->type should always match intern->zms->type */
	RETURN_LONG(intern->socket_opts.type);
}
/* }}} */

/* {{{ ZMQ ZMQ::setSockOpt(integer $SOCKOPT, mixed $value)
	Set a socket option
*/
PHP_METHOD(zmq, setsockopt)
{
	php_zmq_object *intern;
	long key;
	zval *pz_value;
	int status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &key, &pz_value) == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_OBJECT;
	
	if (!intern->zms) {
		/* Socket is persisted only if context is persistent */
		intern->zms = php_zmq_socket_get(&(intern->socket_opts), &(intern->ctx_opts) TSRMLS_CC);
	}
	
	switch (key) {
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
				zend_throw_exception(php_zmq_exception_sc_entry, "The option value must be a positive integer", 1 TSRMLS_CC);
				return;
			}
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->zms->socket, key, &value, sizeof(uint64_t));
		}
		break;
		
		default:
		{
			zend_throw_exception(php_zmq_exception_sc_entry, "Unknown option key", 1 TSRMLS_CC);
			return;
		}
		break;
	}
	
	if (status != 0) {
		zend_throw_exception_ex(php_zmq_exception_sc_entry, errno TSRMLS_CC, "Failed to set socket option: %s", zmq_strerror(errno));
		return;
	}
	ZMQ_RETURN_THIS;
}
/* }}} */

#ifdef HAVE_ZMQ_GETSOCKOPT
/* {{{ mixed ZMQ::getSockOpt()
	Get a socket option
*/
PHP_METHOD(zmq, getsockopt)
{
	php_zmq_object *intern;
	long key;
	size_t value_len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &key) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_OBJECT;
	
	if (!intern->zms) {
		zend_throw_exception(php_zmq_exception_sc_entry, "The socket has not been initialized yet", 1 TSRMLS_CC);
		return;
	}
	
	switch (key) {
		case ZMQ_SWAP:
		case ZMQ_AFFINITY:
		{
			int64_t value;
			
			value_len = sizeof(int64_t);
			if (zmq_getsockopt (intern->zms->socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_exception_sc_entry, errno TSRMLS_CC, "Failed to get the option value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_IDENTITY:
		{
			unsigned char value[255];
			
			value_len = 255;
			if (zmq_getsockopt(intern->zms->socket, (int) key, value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_exception_sc_entry, errno TSRMLS_CC, "Failed to get the option value: %s", zmq_strerror(errno));
				return;
			}
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
				zend_throw_exception_ex(php_zmq_exception_sc_entry, errno TSRMLS_CC, "Failed to get the option value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SUBSCRIBE:
		case ZMQ_UNSUBSCRIBE:
			zend_throw_exception(php_zmq_exception_sc_entry, "Retrieving SOCKOPT_SUBSCRIBE and SOCKOPT_UNSUBSCRIBE is not support", 1 TSRMLS_CC);
			return;
		break;
		
		default:
		{
			zend_throw_exception(php_zmq_exception_sc_entry, "Unknown option key", 1 TSRMLS_CC);
			return;
		}
		break;
	}
}
/* }}} */
#endif

/* -- END ZMQ --- */

/* -- START ZMQPoll --- */

/* {{{ integer ZMQPoll::add(ZMQ $object, integer $events)
	Add a ZMQ object into the pollset
*/
PHP_METHOD(zmqpoll, add)
{
	php_zmq_poll_object *intern;
	zval *object;
	long events;
	int pos, key_len = 35;
	char key[35];
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &object, &events) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_POLL_OBJECT;
	
	switch (Z_TYPE_P(object)) {
		case IS_OBJECT:
			if (!instanceof_function(Z_OBJCE_P(object), php_zmq_sc_entry TSRMLS_CC)) {
				zend_throw_exception(php_zmq_poll_exception_sc_entry, "The object must be an instanceof ZMQ", 1 TSRMLS_CC);
				return;
			}
		break;
		
		case IS_RESOURCE:
			// todo: check
		break;
		
		default:
		
		break;
	}

	pos = php_zmq_pollset_add(&(intern->set), object, events TSRMLS_CC);

	if (pos < 0) {
		
		char *message = NULL;
		
		switch (pos) {
			
			case PHP_ZMQ_POLLSET_ERR_NO_STREAM:
				message = "The supplied resource is not a valid stream resource";
			break;
			
			case PHP_ZMQ_POLLSET_ERR_CANNOT_CAST:
				message = "The supplied resource is not castable";
			break;
			
			case PHP_ZMQ_POLLSET_ERR_CAST_FAILED:
				message = "Failed to cast the supplied stream resource";
			break;
			
			case PHP_ZMQ_POLLSET_ERR_NO_INIT:
				message = "The ZMQ object has not been initialized properly";
			break;
			
			case PHP_ZMQ_POLLSET_ERR_NO_POLL:
				message = "The ZMQ object has not been initialized with polling";
			break;
			
			default:
				message = "Unknown error";
			break;
		}
		
		zend_throw_exception(php_zmq_poll_exception_sc_entry, message, 1 TSRMLS_CC);
		return;
	}
	
	if (!php_zmq_pollset_get_key(&(intern->set), pos, key, &key_len)) {
		zend_throw_exception(php_zmq_poll_exception_sc_entry, "Failed to get the item key", 1 TSRMLS_CC);
		return;
	}
	
	RETURN_STRINGL(key, key_len, 1);
	return;
}
/* }}} */

/* {{{ ZMQPoll ZMQPoll::remove(mixed $item)
	Remove item from poll set
*/
PHP_METHOD(zmqpoll, remove)
{
	php_zmq_poll_object *intern;
	zval *item;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &item) == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_POLL_OBJECT;
	
	if (intern->set.num_items == 0) {
		zend_throw_exception(php_zmq_poll_exception_sc_entry, "No sockets assigned to the ZMQPoll", 1 TSRMLS_CC);
		return;
	}
	
	switch (Z_TYPE_P(item)) {
		
		case IS_OBJECT:
			if (!instanceof_function(Z_OBJCE_P(item), php_zmq_sc_entry TSRMLS_CC)) {
				zend_throw_exception(php_zmq_poll_exception_sc_entry, "The object must be an instanceof ZMQ", 1 TSRMLS_CC);
				return;
			}
			/* break intentionally missing */
		case IS_RESOURCE:
			RETVAL_BOOL(php_zmq_pollset_delete(&(intern->set), item));
		break;
		
		default:
			convert_to_string(item);
			RETVAL_BOOL(php_zmq_pollset_delete_by_key(&(intern->set), Z_STRVAL_P(item), Z_STRLEN_P(item)));
		break;
	}
	
	return;
}
/* }}} */

/* {{{ integer ZMQPoll::poll(array &$readable, array &$writable[, integer $timeout = -1])
	Poll the sockets
*/
PHP_METHOD(zmqpoll, poll)
{
	php_zmq_poll_object *intern;
	zval *r_array, *w_array;
	
	long timeout = -1;
	int rc;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a!a!|l", &r_array, &w_array, &timeout) == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_POLL_OBJECT;
	
	if (intern->set.num_items == 0) {
		zend_throw_exception(php_zmq_poll_exception_sc_entry, "No sockets assigned to the ZMQPoll", 1 TSRMLS_CC);
		return;
	}
		
	rc = php_zmq_pollset_poll(&(intern->set), timeout, r_array, w_array, intern->set.errors);

	if (rc == -1) {
		zend_throw_exception_ex(php_zmq_poll_exception_sc_entry, errno TSRMLS_CC, "Poll failed: %s", zmq_strerror(errno));
		return;
	}
	RETURN_LONG(rc);
}
/* }}} */

/* {{{ integer ZMQPoll::count()
	Returns the number of items in the set
*/
PHP_METHOD(zmqpoll, count)
{
	php_zmq_poll_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_POLL_OBJECT;
	RETURN_LONG(intern->set.num_items);
}
/* }}} */

/* {{{ integer ZMQPoll::clear()
	Clear the pollset
*/
PHP_METHOD(zmqpoll, clear)
{
	php_zmq_poll_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZMQ_POLL_OBJECT;
	
	php_zmq_pollset_delete_all(&(intern->set));
	ZMQ_RETURN_THIS;
}
/* }}} */

/* {{{ array ZMQPoll::getLastErrors()
	Returns last errors
*/
PHP_METHOD(zmqpoll, getlasterrors)
{
	php_zmq_poll_object *intern;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_POLL_OBJECT;
	
	Z_ADDREF_P(intern->set.errors);
	RETVAL_ZVAL(intern->set.errors, 1, 0);
	return;
}
/* }}} */

/* -- END ZMQPoll */

ZEND_BEGIN_ARG_INFO_EX(zmq_construct_args, 0, 0, 2)	
	ZEND_ARG_INFO(0, type)
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_bind_args, 0, 0, 1)	
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_connect_args, 0, 0, 1)	
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_setsockopt_args, 0, 0, 2)	
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_getcontextoptions_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_setcontextoptions_args, 0, 0, 1)
	ZEND_ARG_INFO(0, io_threads)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_getendpoints_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_getsockettype_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_send_args, 0, 0, 1)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_recv_args, 0, 0, 0)
	ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_getpersistentid_args, 0, 0, 0)
ZEND_END_ARG_INFO()

#ifdef HAVE_ZMQ_GETSOCKOPT
ZEND_BEGIN_ARG_INFO_EX(zmq_getsockopt_args, 0, 0, 0)
ZEND_END_ARG_INFO()
#endif

static function_entry php_zmq_class_methods[] = {
	PHP_ME(zmq, __construct,			zmq_construct_args,			ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(zmq, send,				zmq_send_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmq, recv,				zmq_recv_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmq, bind,				zmq_bind_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmq, connect,				zmq_connect_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zmq, setsockopt,			zmq_setsockopt_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zmq, getcontextoptions,	zmq_getcontextoptions_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmq, setcontextoptions,	zmq_setcontextoptions_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmq, getendpoints,		zmq_getendpoints_args,		ZEND_ACC_PUBLIC)
	PHP_ME(zmq, getsockettype,		zmq_getsockettype_args,		ZEND_ACC_PUBLIC)
	PHP_ME(zmq, getpersistentid,		zmq_getpersistentid_args,	ZEND_ACC_PUBLIC)
#ifdef HAVE_ZMQ_GETSOCKOPT
	PHP_ME(zmq, getsockopt,			zmq_getsockopt_args,			ZEND_ACC_PUBLIC)
#endif
	{NULL, NULL, NULL}
};

ZEND_BEGIN_ARG_INFO_EX(zmq_poll_add_args, 0, 0, 2)
	ZEND_ARG_INFO(0, entry) 
	ZEND_ARG_INFO(0, type) 
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_poll_poll_args, 0, 0, 2)
	ZEND_ARG_INFO(0, readable) 
	ZEND_ARG_INFO(0, writable)
	ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_poll_getlasterrors_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_poll_remove_args, 0, 0, 2)
	ZEND_ARG_INFO(0, remove) 
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_poll_count_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_poll_clear_args, 0, 0, 0)
ZEND_END_ARG_INFO()

static function_entry php_zmq_poll_class_methods[] = {
	PHP_ME(zmqpoll, add,			zmq_poll_add_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmqpoll, poll,			zmq_poll_poll_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmqpoll, getlasterrors,	zmq_poll_getlasterrors_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmqpoll, remove,			zmq_poll_remove_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zmqpoll, count,			zmq_poll_count_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zmqpoll, clear,			zmq_poll_clear_args,			ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

zend_function_entry zmq_functions[] = {
	{NULL, NULL, NULL} 
};

static void php_zmq_object_free_storage(void *object TSRMLS_DC)
{
	php_zmq_object *intern = (php_zmq_object *)object;

	if (!intern) {
		return;
	}

	if (intern->socket_opts.p_id) {
		efree(intern->socket_opts.p_id);
	}
	
	if (intern->zms && !intern->zms->opts.is_persistent) {
		if (intern->zms->ctx && !intern->zms->ctx->opts.is_persistent) {
			php_zmq_context_destroy(intern->zms->ctx);
		}
		php_zmq_socket_destroy(intern->zms);
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}

static void php_zmq_poll_object_free_storage(void *object TSRMLS_DC)
{
	php_zmq_poll_object *intern = (php_zmq_poll_object *)object;

	if (!intern) {
		return;
	}

	php_zmq_pollset_deinit(&(intern->set)); 
	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	
	efree(intern);
}

static zend_object_value php_zmq_object_new_ex(zend_class_entry *class_type, php_zmq_object **ptr TSRMLS_DC)
{
	zval *tmp;
	zend_object_value retval;
	php_zmq_object *intern;

	/* Allocate memory for it */
	intern = (php_zmq_object *) emalloc(sizeof(php_zmq_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	intern->zms  = NULL;
	
	/* Initialize socket options */
	intern->socket_opts.p_id = NULL;
	intern->socket_opts.type = -1;
	
	/* Initialized the context options */
	intern->ctx_opts.io_threads    = 1;
	intern->ctx_opts.is_persistent = ZMQ_G(persist_context);
	
	if (ptr) {
		*ptr = intern;
	}

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	zend_hash_copy(intern->zo.properties, &class_type->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_zmq_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &zmq_object_handlers;
	return retval;
}

static zend_object_value php_zmq_context_object_new_ex(zend_class_entry *class_type, php_zmq_context_object **ptr TSRMLS_DC)
{
	zval *tmp;
	zend_object_value retval;
	php_zmq_context_object *intern;

	/* Allocate memory for it */
	intern = (php_zmq_context_object *) emalloc(sizeof(php_zmq_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	/*
		TODO: initialize properties here
	*/
	
	if (ptr) {
		*ptr = intern;
	}

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	zend_hash_copy(intern->zo.properties, &class_type->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_zmq_context_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &zmq_context_object_handlers;
	return retval;
}

static zend_object_value php_zmq_poll_object_new_ex(zend_class_entry *class_type, php_zmq_poll_object **ptr TSRMLS_DC)
{
	zval *tmp;
	zend_object_value retval;
	php_zmq_poll_object *intern;

	/* Allocate memory for it */
	intern = (php_zmq_poll_object *) emalloc(sizeof(php_zmq_poll_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	php_zmq_pollset_init(&(intern->set));

	if (ptr) {
		*ptr = intern;
	}

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	zend_hash_copy(intern->zo.properties, &class_type->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_zmq_poll_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &zmq_poll_object_handlers;
	return retval;
}

static zend_object_value php_zmq_context_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zmq_context_object_new_ex(class_type, NULL TSRMLS_CC);
}

static zend_object_value php_zmq_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zmq_object_new_ex(class_type, NULL TSRMLS_CC);
}

static zend_object_value php_zmq_poll_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zmq_poll_object_new_ex(class_type, NULL TSRMLS_CC);
}

ZEND_RSRC_DTOR_FUNC(php_zmq_socket_dtor)
{
	if (rsrc->ptr) {
		php_zmq_socket *zms = (php_zmq_socket *)rsrc->ptr;
		php_zmq_socket_destroy(zms);
		rsrc->ptr = NULL;
	}
}

ZEND_RSRC_DTOR_FUNC(php_zmq_context_dtor)
{
	if (rsrc->ptr) {
		php_zmq_context *ctx = (php_zmq_context *)rsrc->ptr;
		php_zmq_context_destroy(ctx);
		rsrc->ptr = NULL;
	}
}

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("zmq.persist_context", "1", PHP_INI_SYSTEM, OnUpdateBool, persist_context, zend_php_zmq_globals, php_zmq_globals)
PHP_INI_END()

static void php_zmq_init_globals(zend_php_zmq_globals *zmq_globals)
{
	zmq_globals->persist_context = 1;
}

PHP_MINIT_FUNCTION(zmq)
{
	zend_class_entry ce;
	
	ZEND_INIT_MODULE_GLOBALS(php_zmq, php_zmq_init_globals, NULL);
	REGISTER_INI_ENTRIES();
	
	le_zmq_socket  = zend_register_list_destructors_ex(NULL, php_zmq_socket_dtor, "ZMQ persistent socket", module_number);
	le_zmq_context = zend_register_list_destructors_ex(NULL, php_zmq_context_dtor, "ZMQ persistent context", module_number);

	memcpy(&zmq_context_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&zmq_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&zmq_poll_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	
	INIT_CLASS_ENTRY(ce, "ZMQContext", php_zmq_context_class_methods);
	ce.create_object = php_zmq_context_object_new;
	zmq_context_object_handlers.clone_obj = NULL;
	php_zmq_context_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);
	
	INIT_CLASS_ENTRY(ce, "ZMQ", php_zmq_class_methods);
	ce.create_object = php_zmq_object_new;
	zmq_object_handlers.clone_obj = NULL;
	php_zmq_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);

	INIT_CLASS_ENTRY(ce, "ZMQPoll", php_zmq_poll_class_methods);
	ce.create_object = php_zmq_poll_object_new;
	zmq_poll_object_handlers.clone_obj = NULL;
	php_zmq_poll_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);

	INIT_CLASS_ENTRY(ce, "ZMQException", NULL);
	php_zmq_exception_sc_entry = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);
	php_zmq_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL;

	INIT_CLASS_ENTRY(ce, "ZMQPollException", NULL);
	php_zmq_poll_exception_sc_entry = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);
	php_zmq_poll_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL;
	
#define PHP_ZMQ_REGISTER_CONST_LONG(const_name, value) \
	zend_declare_class_constant_long(php_zmq_sc_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);	
	
	/* Socket constants */
#if defined(ZMQ_PAIR)
    PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_PAIR", ZMQ_PAIR);
    PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_P2P", ZMQ_PAIR);
#else
    PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_P2P", ZMQ_P2P);
#endif
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_PUB", ZMQ_PUB);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_SUB", ZMQ_SUB);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_REQ", ZMQ_REQ);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_REP", ZMQ_REP);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_XREQ", ZMQ_XREQ);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_XREP", ZMQ_XREP);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_UPSTREAM", ZMQ_UPSTREAM);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_DOWNSTREAM", ZMQ_DOWNSTREAM);

	PHP_ZMQ_REGISTER_CONST_LONG("SOCKOPT_SWAP", ZMQ_SWAP);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKOPT_AFFINITY", ZMQ_AFFINITY);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKOPT_IDENTITY", ZMQ_IDENTITY);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKOPT_SUBSCRIBE", ZMQ_SUBSCRIBE);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKOPT_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKOPT_RATE", ZMQ_RATE);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKOPT_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKOPT_MCAST_LOOP", ZMQ_MCAST_LOOP);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKOPT_SNDBUF", ZMQ_SNDBUF);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKOPT_RCVBUF", ZMQ_RCVBUF);
#ifdef ZMQ_SNDMORE
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKOPT_SNDMORE", ZMQ_SNDMORE);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKOPT_RECVMORE", ZMQ_RCVMORE);
#endif	
	
	PHP_ZMQ_REGISTER_CONST_LONG("POLL_IN", ZMQ_POLLIN);
	PHP_ZMQ_REGISTER_CONST_LONG("POLL_OUT", ZMQ_POLLOUT);
	
	PHP_ZMQ_REGISTER_CONST_LONG("MODE_NOBLOCK", ZMQ_NOBLOCK);	
#undef PHP_ZMQ_REGISTER_CONST_LONG

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(zmq)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_MINFO_FUNCTION(zmq)
{
	char *version;
	int major = 0, minor = 0, patch = 0;
	
	zmq_version(&major, &minor, &patch);
	(void) spprintf(&version, 0, "%d.%d.%d", major, minor, patch);
	
	php_info_print_table_start();

		php_info_print_table_header(2, "ZMQ extension", "enabled");
		php_info_print_table_row(2, "ZMQ extension version", PHP_ZMQ_EXTVER);
		php_info_print_table_row(2, "libzmq version", version);

	php_info_print_table_end();

	efree(version);
	DISPLAY_INI_ENTRIES();
}

zend_module_entry zmq_module_entry =
{
        STANDARD_MODULE_HEADER,
        PHP_ZMQ_EXTNAME,
        zmq_functions,			/* Functions */
        PHP_MINIT(zmq),			/* MINIT */
        PHP_MSHUTDOWN(zmq),		/* MSHUTDOWN */
        NULL,					/* RINIT */
        NULL,					/* RSHUTDOWN */
        PHP_MINFO(zmq),			/* MINFO */
        PHP_ZMQ_EXTVER,			/* version */
        STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ZMQ
ZEND_GET_MODULE(zmq)
#endif /* COMPILE_DL_ZMQ */