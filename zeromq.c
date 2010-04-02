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
zend_class_entry *php_zeromq_socket_sc_entry;

zend_class_entry *php_zeromq_exception_sc_entry;
zend_class_entry *php_zeromq_socket_exception_sc_entry;

static zend_object_handlers zeromq_object_handlers;
static zend_object_handlers zeromq_socket_object_handlers;

ZEND_DECLARE_MODULE_GLOBALS(zeromq);

#ifndef Z_ADDREF_P
# define Z_ADDREF_P(pz) pz->refcount++
#endif

#ifndef Z_DELREF_P
# define Z_DELREF_P(pz) pz->refcount--
#endif

static int le_zeromq;

static inline int php_zeromq_list_entry(void)
{
	return le_zeromq;
}

/* -- START ZeroMQ --- */

/* {{{
*/
PHP_METHOD(zeromq, __construct)
{
	
}
/* }}} */

/* {{{ ZeroMQ ZeroMQ::setSocket(ZeroMQSocket socket)
	Set the ZeroMQ socket object
*/
PHP_METHOD(zeromq, setsocket)
{
	php_zeromq_object *intern;
	zval *sock_param; 
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &sock_param, php_zeromq_socket_sc_entry) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	if (intern->sock_obj) {
		Z_DELREF_P(intern->sock_obj);
	}
	
	intern->sock_obj = sock_param;
	Z_ADDREF_P(intern->sock_obj); 
	
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* {{{ ZeroMQSocket ZeroMQ::getSocket()
	Get the ZeroMQ socket object
*/
PHP_METHOD(zeromq, getsocket)
{
	php_zeromq_object *intern;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	if (!intern->sock_obj) {
		zend_throw_exception(php_zeromq_exception_sc_entry, "No socket set on the object", 1 TSRMLS_CC);
		return;
	}
	
	*return_value = *(intern->sock_obj);
	return;
}
/* }}} */

/* {{{ ZeroMQ ZeroMQ::send(string message)
	Send a message
*/
PHP_METHOD(zeromq, send)
{
	php_zeromq_object *intern;
	php_zeromq_socket_object *intern_sock;
	char *message_param; 
	
	zmq_msg_t message;
	int rc, message_param_len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &message_param, &message_param_len) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	if (!intern->sock_obj) {
		zend_throw_exception(php_zeromq_exception_sc_entry, "No socket set on the object", 1 TSRMLS_CC);
		return;
	}

	intern_sock = (php_zeromq_socket_object *)zend_object_store_get_object(intern->sock_obj TSRMLS_CC);
	
	if (zmq_msg_init_size(&message, message_param_len) != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to initialize message structure: %s", zmq_strerror(errno));
		return;
	}
	memcpy(zmq_msg_data(&message), message_param, message_param_len);
	
	rc = zmq_send(intern_sock->zms->socket, &message, zmq_msg_size(&message));
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
	php_zeromq_socket_object *intern_sock;
	zmq_msg_t message;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	if (!intern->sock_obj) {
		zend_throw_exception(php_zeromq_exception_sc_entry, "No socket set on the object", 1 TSRMLS_CC);
		return;
	}

	intern_sock = (php_zeromq_socket_object *)zend_object_store_get_object(intern->sock_obj TSRMLS_CC);

	if (zmq_msg_init(&message) != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to initialize message structure: %s", zmq_strerror(errno));
		return;
	}
	
	if (zmq_recv(intern_sock->zms->socket, &message, 0) != 0) {
		zmq_msg_close(&message);
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to receive message: %s", zmq_strerror(errno));
		return;
	}

	ZVAL_STRINGL(return_value, zmq_msg_data(&message), zmq_msg_size(&message), 1);	
	zmq_msg_close(&message);
	return;
}
/* }}} */

/* -- END ZeroMQ -- */

/* -- START ZeroMQSocket --- */

static int php_zeromq_nofree_dtor() 
{
	return ZEND_HASH_APPLY_REMOVE;
}

static php_zeromq_socket *php_zeromq_socket_new(int type, zend_bool persistent TSRMLS_DC)
{
	php_zeromq_socket *zmq_sock;
	zmq_sock = pecalloc(1, sizeof(php_zeromq_socket), persistent);

	zmq_sock->context       = zmq_init(ZEROMQ_G(app_threads), ZEROMQ_G(io_threads), 0);
	zmq_sock->socket        = zmq_socket(zmq_sock->context, (int) type);
	zmq_sock->is_persistent = persistent;
	
	zmq_sock->app_threads   = ZEROMQ_G(app_threads);
	zmq_sock->io_threads    = ZEROMQ_G(io_threads);
	
	zend_hash_init(&(zmq_sock->connect), 0, NULL, (dtor_func_t) php_zeromq_nofree_dtor, persistent);
	zend_hash_init(&(zmq_sock->bind), 0, NULL, (dtor_func_t) php_zeromq_nofree_dtor, persistent);
	return zmq_sock;
}

static void php_zeromq_socket_destroy(php_zeromq_socket *zmq_sock)
{
	zend_hash_destroy(&(zmq_sock->connect));
	zend_hash_destroy(&(zmq_sock->bind));
	
	(void) zmq_close(zmq_sock->socket);
	(void) zmq_term(zmq_sock->context);
	
	pefree(zmq_sock, zmq_sock->is_persistent);
}

/* Get a socket. If id = NULL create a new socket */
static php_zeromq_socket *php_zeromq_socket_get(int type, const char *p_id, int p_id_len TSRMLS_DC)
{
	php_zeromq_socket *zmq_sock_p;
	zend_bool persistent = (p_id && p_id_len);

	char *plist_key;
	int plist_key_len;

	plist_key_len  = spprintf(&plist_key, 0, "zeromq:id=%s", p_id);
	plist_key_len += 1;

	if (persistent) {
		zend_rsrc_list_entry *le = NULL;
		
		if (zend_hash_find(&EG(persistent_list), plist_key, plist_key_len, (void *)&le) == SUCCESS) {
			if (le->type == php_zeromq_list_entry()) {
				efree(plist_key);
				zmq_sock_p = (php_zeromq_socket *) le->ptr;
				return zmq_sock_p;
			}
		}	
	}
	zmq_sock_p = php_zeromq_socket_new(type, persistent TSRMLS_CC);
	
	if (persistent) {
		zend_rsrc_list_entry le;

		le.type = php_zeromq_list_entry();
		le.ptr  = zmq_sock_p;
		
		if (zend_hash_update(&EG(persistent_list), (char *)plist_key, plist_key_len, (void *)&le, sizeof(le), NULL) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Could not register persistent entry");
		}
	}
	efree(plist_key);
	return zmq_sock_p;	
}

/* {{{ ZeroMQSocket::__construct(int type[, string persistent_id])
	Build a new ZeroMQSocket object
*/
PHP_METHOD(zeromqsocket, __construct)
{
	php_zeromq_socket_object *intern;
	long type;
	char *p_id = NULL;
	int p_id_len = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|s!", &type, &p_id, &p_id_len) == FAILURE) {
		return;
	}

	intern      = PHP_ZEROMQ_SOCKET_OBJECT;
	intern->zms = php_zeromq_socket_get((int) type, p_id, p_id_len TSRMLS_CC);
	return;
}
/* }}} */

/* {{{ ZeroMQSocket::bind(string dsn[, bool force_new_connection])
	Bind the socket to an endpoint
*/
PHP_METHOD(zeromqsocket, bind)
{
	php_zeromq_socket_object *intern;
	char *dsn;
	int dsn_len;
	zend_bool force = 0;
	void *dummy = (void *) 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &dsn, &dsn_len, &force) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_SOCKET_OBJECT;
	
	if (!intern->zms) {
		zend_throw_exception(php_zeromq_socket_exception_sc_entry, "The ZeroMQSocket::__construct needs to be called before using the object", 1 TSRMLS_CC);
		return;
	}
	
	/* already connected ? */
	if (!force && zend_hash_exists(&(intern->zms->bind), dsn, dsn_len + 1)) {
		ZEROMQ_RETURN_THIS;
	}

	if (zmq_bind(intern->zms->socket, dsn) != 0) {
		zend_throw_exception_ex(php_zeromq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to bind the ZeroMQSocket: %s", zmq_strerror(errno));
		return;
	}
	
	zend_hash_add(&(intern->zms->bind), dsn, dsn_len + 1, &dummy, sizeof(void *), NULL);
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* {{{ ZeroMQSocket::connect(string dsn[, bool force_new_connection])
	Connect the socket to an endpoint
*/
PHP_METHOD(zeromqsocket, connect)
{
	php_zeromq_socket_object *intern;
	char *dsn;
	int dsn_len;
	zend_bool force = 0;
	void *dummy = (void *) 1;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &dsn, &dsn_len, &force) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_SOCKET_OBJECT;
	
	if (!intern->zms) {
		zend_throw_exception(php_zeromq_socket_exception_sc_entry, "The ZeroMQSocket::__construct needs to be called before using the object", 1 TSRMLS_CC);
		return;
	}
	
	/* already connected ? */
	if (!force && zend_hash_exists(&(intern->zms->connect), dsn, dsn_len + 1)) {
		ZEROMQ_RETURN_THIS;
	}

	if (zmq_connect(intern->zms->socket, dsn) != 0) {
		zend_throw_exception_ex(php_zeromq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to connect the ZeroMQSocket: %s", zmq_strerror(errno));
		return;
	}
	
	zend_hash_add(&(intern->zms->connect), dsn, dsn_len + 1, &dummy, sizeof(void *), NULL);
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* {{{ ZeroMQSocket::setSockOpt(int ZeroMQ::SOCKOPT_, mixed value)
	Set a socket option
*/
PHP_METHOD(zeromqsocket, setsockopt)
{
	php_zeromq_socket_object *intern;
	long key;
	zval *pz_value;
	int status;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &key, &pz_value) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_SOCKET_OBJECT;
	
	if (!intern->zms) {
		zend_throw_exception(php_zeromq_socket_exception_sc_entry, "The ZeroMQSocket::__construct needs to be called before using the object", 1 TSRMLS_CC);
		return;
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
				zend_throw_exception(php_zeromq_socket_exception_sc_entry, "The option value must be a positive integer", 1 TSRMLS_CC);
				return;
			}
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->zms->socket, key, &value, sizeof(uint64_t));
		}
		break;
		
		default:
		{
			zend_throw_exception(php_zeromq_socket_exception_sc_entry, "Unknown option key", 1 TSRMLS_CC);
			return;
		}
		break;
	}
	
	if (status != 0) {
		zend_throw_exception_ex(php_zeromq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to set socket option: %s", zmq_strerror(errno));
		return;
	}
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/** {{{ array ZeroMQSocket::getContextOptions() 
	Returns the amount of app and io threads in the internal context
*/
PHP_METHOD(zeromqsocket, getcontextoptions)
{
	php_zeromq_socket_object *intern;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_SOCKET_OBJECT;
	
	if (!intern->zms) {
		zend_throw_exception(php_zeromq_socket_exception_sc_entry, "The ZeroMQSocket::__construct needs to be called before using the object", 1 TSRMLS_CC);
		return;
	}
	
	array_init(return_value);
	add_assoc_long(return_value, "app_threads", intern->zms->app_threads);
	add_assoc_long(return_value, "io_threads",  intern->zms->io_threads);
	return;
}
/* }}} */

/* -- END ZeroMQSocket --- */

ZEND_BEGIN_ARG_INFO_EX(zeromq_construct_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_setsocket_args, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ZeroMQSocket, ZeroMQSocket, 0) 
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_getsocket_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_send_args, 0, 0, 1)
	ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_recv_args, 0, 0, 0)
ZEND_END_ARG_INFO()

static function_entry php_zeromq_class_methods[] = {
	PHP_ME(zeromq, __construct,	zeromq_construct_args,	ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(zeromq, setsocket,	zeromq_setsocket_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, getsocket,	zeromq_getsocket_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, send,		zeromq_send_args,		ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, recv,		zeromq_recv_args,		ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

ZEND_BEGIN_ARG_INFO_EX(zeromq_socket_construct_args, 0, 0, 2)	
	ZEND_ARG_INFO(0, type)
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_socket_bind_args, 0, 0, 1)	
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_socket_connect_args, 0, 0, 1)	
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_socket_setsockopt_args, 0, 0, 2)	
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_socket_getcontextoptions_args, 0, 0, 0)
ZEND_END_ARG_INFO()

static function_entry php_zeromq_socket_class_methods[] = {
	PHP_ME(zeromqsocket, __construct,		zeromq_socket_construct_args,			ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(zeromqsocket, bind,				zeromq_socket_bind_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zeromqsocket, connect,			zeromq_socket_connect_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zeromqsocket, setsockopt,		zeromq_socket_setsockopt_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zeromqsocket, getcontextoptions,	zeromq_socket_getcontextoptions_args,	ZEND_ACC_PUBLIC)
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
	
	if (intern->sock_obj) {
		Z_DELREF_P(intern->sock_obj);
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}


static void php_zeromq_socket_object_free_storage(void *object TSRMLS_DC)
{
	php_zeromq_socket_object *intern = (php_zeromq_socket_object *)object;

	if (!intern) {
		return;
	}
	
	if (intern->zms && !intern->zms->is_persistent) {
		php_zeromq_socket_destroy(intern->zms);
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
	
	/* Sock object is set in ->setSocket() */
	intern->sock_obj = NULL;
	
	if (ptr) {
		*ptr = intern;
	}

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	zend_hash_copy(intern->zo.properties, &class_type->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_zeromq_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &zeromq_object_handlers;
	return retval;
}

static zend_object_value php_zeromq_socket_object_new_ex(zend_class_entry *class_type, php_zeromq_socket_object **ptr TSRMLS_DC)
{
	zval *tmp;
	zend_object_value retval;
	php_zeromq_socket_object *intern;

	/* Allocate memory for it */
	intern = (php_zeromq_socket_object *) emalloc(sizeof(php_zeromq_socket_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	/* init in constructor */
	intern->zms = NULL;

	if (ptr) {
		*ptr = intern;
	}

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	zend_hash_copy(intern->zo.properties, &class_type->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_zeromq_socket_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &zeromq_socket_object_handlers;
	return retval;
}

static zend_object_value php_zeromq_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zeromq_object_new_ex(class_type, NULL TSRMLS_CC);
}

static zend_object_value php_zeromq_socket_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zeromq_socket_object_new_ex(class_type, NULL TSRMLS_CC);
}

ZEND_RSRC_DTOR_FUNC(php_zeromq_socket_dtor)
{
	if (rsrc->ptr) {
		php_zeromq_socket *zms = (php_zeromq_socket *)rsrc->ptr;
		php_zeromq_socket_destroy(zms);
		rsrc->ptr = NULL;
	}
}

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("zeromq.app_threads", "1", PHP_INI_ALL, OnUpdateLong, app_threads, zend_zeromq_globals, zeromq_globals)
	STD_PHP_INI_ENTRY("zeromq.io_threads", "1", PHP_INI_ALL, OnUpdateLong, io_threads, zend_zeromq_globals, zeromq_globals)
PHP_INI_END()

static void php_zeromq_init_globals(zend_zeromq_globals *zeromq_globals)
{
	zeromq_globals->app_threads = 1;
	zeromq_globals->io_threads  = 1;
}

PHP_MINIT_FUNCTION(zeromq)
{
	zend_class_entry ce;
	ZEND_INIT_MODULE_GLOBALS(zeromq, php_zeromq_init_globals, NULL);
	REGISTER_INI_ENTRIES();
	
	le_zeromq = zend_register_list_destructors_ex(NULL, php_zeromq_socket_dtor, "ZeroMQ persistent socket", module_number);

	memcpy(&zeromq_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&zeromq_socket_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	
	INIT_CLASS_ENTRY(ce, "ZeroMQ", php_zeromq_class_methods);
	ce.create_object = php_zeromq_object_new;
	zeromq_object_handlers.clone_obj = NULL;
	php_zeromq_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);
	
	INIT_CLASS_ENTRY(ce, "ZeroMQSocket", php_zeromq_socket_class_methods);
	ce.create_object = php_zeromq_socket_object_new;
	zeromq_socket_object_handlers.clone_obj = NULL;
	php_zeromq_socket_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);

	INIT_CLASS_ENTRY(ce, "ZeroMQException", NULL);
	php_zeromq_exception_sc_entry = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);
	php_zeromq_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL;

	INIT_CLASS_ENTRY(ce, "ZeroMQSocketException", NULL);
	php_zeromq_socket_exception_sc_entry = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);
	php_zeromq_socket_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL;
	
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
	php_info_print_table_start();

		php_info_print_table_header(2, "zeromq extension", "enabled");
		php_info_print_table_row(2, "zeromq extension version", PHP_ZEROMQ_EXTVER);

	php_info_print_table_end();

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