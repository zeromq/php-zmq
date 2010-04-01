/*
Copyright (c) 2010, Mikko Koppanen <mkoppanen@php.net>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKKO KOPPANEN BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "php_zeromq.h"
#include "php_zeromq_private.h"

zend_class_entry *php_zeromq_sc_entry;
zend_class_entry *php_zeromq_message_sc_entry;
zend_class_entry *php_zeromq_socket_sc_entry;

zend_class_entry *php_zeromq_exception_sc_entry;
zend_class_entry *php_zeromq_message_exception_sc_entry;
zend_class_entry *php_zeromq_socket_exception_sc_entry;

static zend_object_handlers zeromq_object_handlers;
static zend_object_handlers zeromq_message_object_handlers;
static zend_object_handlers zeromq_socket_object_handlers;

ZEND_DECLARE_MODULE_GLOBALS(zeromq);

/* -- START ZeroMQ --- */

/* {{{
*/
PHP_METHOD(zeromq, __construct)
{
	
}
/* }}} */

/* {{{
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

/* {{{
*/
PHP_METHOD(zeromq, send)
{
	php_zeromq_object *intern;
	php_zeromq_message_object *intern_msg;
	php_zeromq_socket_object *intern_sock;
	
	zval *message_param; 
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &message_param, php_zeromq_message_sc_entry) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	if (!intern->sock_obj) {
		zend_throw_exception(php_zeromq_exception_sc_entry, "No socket set on the object", 1 TSRMLS_CC);
		return;
	}

	intern_msg  = (php_zeromq_message_object *)zend_object_store_get_object(message_param TSRMLS_CC);
	intern_sock = (php_zeromq_socket_object *)zend_object_store_get_object(intern->sock_obj TSRMLS_CC);
	
	if (zmq_send(intern_sock->zms->socket, intern_msg->message, 0) != 0) {
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to send the message: %s", zmq_strerror(errno));
		return;
	}
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* {{{
*/
PHP_METHOD(zeromq, recv)
{
	php_zeromq_object *intern;
	php_zeromq_socket_object *intern_sock;
	php_zeromq_message_object *intern_msg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_OBJECT;
	
	if (!intern->sock_obj) {
		zend_throw_exception(php_zeromq_exception_sc_entry, "No socket set on the object", 1 TSRMLS_CC);
		return;
	}

	intern_sock = (php_zeromq_socket_object *)zend_object_store_get_object(intern->sock_obj TSRMLS_CC);

	object_init_ex(return_value, php_zeromq_message_sc_entry);
	intern_msg = (php_zeromq_message_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	intern_msg->message = emalloc(sizeof(zmq_msg_t));
	
	if (zmq_msg_init(intern_msg->message) != 0) {
		efree(intern_msg->message);
		zend_throw_exception(php_zeromq_message_exception_sc_entry, "Failed to initialise the return object", 1 TSRMLS_CC);
		return;
	}
	
	if (zmq_recv(intern_sock->zms->socket, intern_msg->message, 0) != 0) {
		efree(intern_msg->message);
		zend_throw_exception_ex(php_zeromq_exception_sc_entry, errno TSRMLS_CC, "Failed to receive the message: %s", zmq_strerror(errno));
		return;
	}
	return;
}
/* }}} */

/* -- END ZeroMQ -- */

/* -- START ZeroMQMessage --- */

/* {{{
*/
PHP_METHOD(zeromqmessage, __construct)
{
	php_zeromq_message_object *intern;
	char *msg;
	int msg_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &msg, &msg_len) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_MESSAGE_OBJECT;
	intern->message = emalloc(sizeof(zmq_msg_t));
	
	if (zmq_msg_init_size(intern->message, msg_len + 1) != 0) {
		efree(intern->message);
		zend_throw_exception_ex(php_zeromq_message_exception_sc_entry, errno TSRMLS_CC, "Failed to initialize the ZeroMQMessage: %s", zmq_strerror(errno));
		return;
	}
	
	memcpy(zmq_msg_data(intern->message), msg, msg_len + 1);
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* {{{
*/
PHP_METHOD(zeromqmessage, setmessage)
{
	php_zeromq_message_object *intern;
	char *msg;
	int msg_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &msg, &msg_len) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_MESSAGE_OBJECT;

	if (!intern->message) {
		intern->message = emalloc(sizeof(zmq_msg_t));
	} else {
		zmq_msg_close(intern->message);
	}
	
	if (zmq_msg_init_size(intern->message, msg_len + 1) != 0) {
		efree(intern->message);
		zend_throw_exception_ex(php_zeromq_message_exception_sc_entry, errno TSRMLS_CC, "Failed to initialize the ZeroMQMessage: %s", zmq_strerror(errno));
		return;
	}
	
	memcpy(zmq_msg_data(intern->message), msg, msg_len + 1);
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* {{{
*/
PHP_METHOD(zeromqmessage, getmessage)
{
	php_zeromq_message_object *intern;
	zend_bool binary = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|b", &binary) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_MESSAGE_OBJECT;

	if (!intern->message) {
		return;
	}
	
	if (binary) {
		RETURN_STRINGL(zmq_msg_data(intern->message), zmq_msg_size(intern->message), 1);
	} else {
		/* Assume it's a null terminated string */
		RETURN_STRINGL(zmq_msg_data(intern->message), zmq_msg_size(intern->message) - 1, 1);
	}
}
/* }}} */

/* -- END ZeroMQMessage --- */

/* -- START ZeroMQSocket --- */

static int php_zeromq_nofree_dtor() 
{
	return ZEND_HASH_APPLY_REMOVE;
}

static php_zeromq_socket *php_zeromq_socket_new(int type, zend_bool persistent TSRMLS_DC)
{
	php_zeromq_socket *zmq_sock;
	
	if (persistent) {
		zmq_sock = malloc(sizeof(php_zeromq_socket));
		
		if (!zmq_sock) {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to allocate memory for connection");
		}
	} else {
		zmq_sock = emalloc(sizeof(php_zeromq_socket));
	}
	
	zmq_sock->context       = zmq_init(1, 1, 0);
	zmq_sock->socket        = zmq_socket(zmq_sock->context, (int) type);
	zmq_sock->is_persistent = persistent;
	
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
	
	if (zmq_sock->is_persistent) {
		free(zmq_sock);
	} else {
		efree(zmq_sock);
	}
}

/* Get a socket. If id = NULL create a new socket */
static php_zeromq_socket *php_zeromq_socket_get(int type, const char *p_id, int p_id_len TSRMLS_DC)
{
	php_zeromq_socket *zmq_sock_p;
	zend_bool persistent = (p_id && p_id_len);

	if (persistent) {
		php_zeromq_socket **zmq_sock_pp;
		
		if (zend_hash_find(&(ZEROMQ_G(sockets)), p_id, p_id_len + 1, (void **)&zmq_sock_pp) == SUCCESS) {
			return *zmq_sock_pp;
		}
		zmq_sock_p = php_zeromq_socket_new(type, 1 TSRMLS_CC);
	} else {
		zmq_sock_p = php_zeromq_socket_new(type, 0 TSRMLS_CC);
	}
	
	if (persistent) {
		if (zend_hash_update(&(ZEROMQ_G(sockets)), p_id, p_id_len + 1, (void *)&zmq_sock_p, sizeof(php_zeromq_socket *), NULL) != SUCCESS) {
			free(zmq_sock_p);
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Failed to store the persistent connection");
		}
	}
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

/* {{{ ZeroMQSocket::bind(string dsn)
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

/* {{{ ZeroMQSocket::connect(string dsn)
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

/* {{{ ZeroMQSocket::setSockOpt(int key, mixed value)
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
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->zms->socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));
		break;
		
		case ZMQ_RATE:
		case ZMQ_RECOVERY_IVL:
		case ZMQ_MCAST_LOOP:
		case ZMQ_SNDBUF:
		case ZMQ_RCVBUF:
		{
			uint64_t value;
			convert_to_long(pz_value);
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->zms->socket, key, &value, sizeof(uint64_t));
		}
		break;
		
		default:
			zend_throw_exception(php_zeromq_socket_exception_sc_entry, "Unknown option key", 1 TSRMLS_CC);
			return;
		break;
	}
	
	if (status != 0) {
		zend_throw_exception_ex(php_zeromq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to set socket option: %s", zmq_strerror(errno));
		return;
	}
	ZEROMQ_RETURN_THIS;
}
/* }}} */

/* -- END ZeroMQSocket --- */

ZEND_BEGIN_ARG_INFO_EX(zeromq_construct_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_setsocket_args, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ZeroMQSocket, ZeroMQSocket, 0) 
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_send_args, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ZeroMQMessage, ZeroMQMessage, 0) 
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_recv_args, 0, 0, 0)
ZEND_END_ARG_INFO()

static function_entry php_zeromq_class_methods[] = {
	PHP_ME(zeromq, __construct,	zeromq_construct_args,	ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(zeromq, setsocket,	zeromq_setsocket_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, send,		zeromq_send_args,		ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, recv,		zeromq_recv_args,		ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

ZEND_BEGIN_ARG_INFO_EX(zeromq_message_construct_args, 0, 0, 1)	
	ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_message_getmessage_args, 0, 0, 0)	
ZEND_END_ARG_INFO()

static function_entry php_zeromq_message_class_methods[] = {
	PHP_ME(zeromqmessage, __construct,	zeromq_message_construct_args,	ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(zeromqmessage, getmessage,	zeromq_message_getmessage_args,	ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
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

static function_entry php_zeromq_socket_class_methods[] = {
	PHP_ME(zeromqsocket, __construct,	zeromq_socket_construct_args,		ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(zeromqsocket, bind,			zeromq_socket_bind_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zeromqsocket, connect,		zeromq_socket_connect_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zeromqsocket, setsockopt,	zeromq_socket_setsockopt_args,		ZEND_ACC_PUBLIC)
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

static void php_zeromq_message_object_free_storage(void *object TSRMLS_DC)
{
	php_zeromq_message_object *intern = (php_zeromq_message_object *)object;

	if (!intern) {
		return;
	}
	
	if (intern->message) {
		(void) zmq_msg_close(intern->message);
		efree(intern->message);
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

static zend_object_value php_zeromq_message_object_new_ex(zend_class_entry *class_type, php_zeromq_message_object **ptr TSRMLS_DC)
{
	zval *tmp;
	zend_object_value retval;
	php_zeromq_message_object *intern;

	/* Allocate memory for it */
	intern = (php_zeromq_message_object *) emalloc(sizeof(php_zeromq_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	intern->message = NULL;

	if (ptr) {
		*ptr = intern;
	}

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	zend_hash_copy(intern->zo.properties, &class_type->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_zeromq_message_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &zeromq_message_object_handlers;
	return retval;
}

static zend_object_value php_zeromq_socket_object_new_ex(zend_class_entry *class_type, php_zeromq_socket_object **ptr TSRMLS_DC)
{
	zval *tmp;
	zend_object_value retval;
	php_zeromq_socket_object *intern;

	/* Allocate memory for it */
	intern = (php_zeromq_socket_object *) emalloc(sizeof(php_zeromq_object));
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

static zend_object_value php_zeromq_message_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zeromq_message_object_new_ex(class_type, NULL TSRMLS_CC);
}

static zend_object_value php_zeromq_socket_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zeromq_socket_object_new_ex(class_type, NULL TSRMLS_CC);
}

static zend_object_value php_zeromq_clone_object(zval *this_ptr TSRMLS_DC)
{
	php_zeromq_object *new_obj = NULL;
	php_zeromq_object *old_obj = (php_zeromq_object *) zend_object_store_get_object(this_ptr TSRMLS_CC);
	zend_object_value new_ov = php_zeromq_object_new_ex(old_obj->zo.ce, &new_obj TSRMLS_CC);
	
	zend_objects_clone_members(&new_obj->zo, new_ov, &old_obj->zo, Z_OBJ_HANDLE_P(this_ptr) TSRMLS_CC);
	return new_ov;
}

static zend_object_value php_zeromq_message_clone_object(zval *this_ptr TSRMLS_DC)
{
	php_zeromq_message_object *new_obj = NULL;
	php_zeromq_message_object *old_obj = (php_zeromq_message_object *) zend_object_store_get_object(this_ptr TSRMLS_CC);
	zend_object_value new_ov = php_zeromq_message_object_new_ex(old_obj->zo.ce, &new_obj TSRMLS_CC);
	
	zend_objects_clone_members(&new_obj->zo, new_ov, &old_obj->zo, Z_OBJ_HANDLE_P(this_ptr) TSRMLS_CC);
	return new_ov;
}

static zend_object_value php_zeromq_socket_clone_object(zval *this_ptr TSRMLS_DC)
{
	php_zeromq_socket_object *new_obj = NULL;
	php_zeromq_socket_object *old_obj = (php_zeromq_socket_object *) zend_object_store_get_object(this_ptr TSRMLS_CC);
	zend_object_value new_ov = php_zeromq_socket_object_new_ex(old_obj->zo.ce, &new_obj TSRMLS_CC);
	
	zend_objects_clone_members(&new_obj->zo, new_ov, &old_obj->zo, Z_OBJ_HANDLE_P(this_ptr) TSRMLS_CC);
	return new_ov;
}

PHP_INI_BEGIN()
PHP_INI_END()

static int php_zeromq_socket_dtor(void **datas TSRMLS_DC) 
{
	php_zeromq_socket *zms = (php_zeromq_socket *) *datas;
	php_zeromq_socket_destroy(zms);
	return ZEND_HASH_APPLY_REMOVE;
}

static void php_zeromq_init_globals(zend_zeromq_globals *zeromq_globals)
{
	/* ZeroMQ sockets */
	zend_hash_init(&(zeromq_globals->sockets), 0, NULL, (dtor_func_t)php_zeromq_socket_dtor, 1);
}

PHP_MINIT_FUNCTION(zeromq)
{
	zend_class_entry ce;
	ZEND_INIT_MODULE_GLOBALS(zeromq, php_zeromq_init_globals, NULL);
	
	REGISTER_INI_ENTRIES();
	
	memcpy(&zeromq_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&zeromq_message_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&zeromq_socket_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	
	INIT_CLASS_ENTRY(ce, "ZeroMQ", php_zeromq_class_methods);
	ce.create_object = php_zeromq_object_new;
	zeromq_object_handlers.clone_obj = php_zeromq_clone_object;
	php_zeromq_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);
	
	INIT_CLASS_ENTRY(ce, "ZeroMQSocket", php_zeromq_socket_class_methods);
	ce.create_object = php_zeromq_socket_object_new;
	zeromq_socket_object_handlers.clone_obj = php_zeromq_socket_clone_object;
	php_zeromq_socket_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);
	
	INIT_CLASS_ENTRY(ce, "ZeroMQMessage", php_zeromq_message_class_methods);
	ce.create_object = php_zeromq_message_object_new;
	zeromq_message_object_handlers.clone_obj = php_zeromq_message_clone_object;
	php_zeromq_message_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);
	
	INIT_CLASS_ENTRY(ce, "ZeroMQException", NULL);
	php_zeromq_exception_sc_entry = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);
	php_zeromq_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL;
	
	INIT_CLASS_ENTRY(ce, "ZeroMQMessageException", NULL);
	php_zeromq_message_exception_sc_entry = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);
	php_zeromq_message_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL;
	
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
	zend_hash_destroy(&(ZEROMQ_G(sockets)));
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