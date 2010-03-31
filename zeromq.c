/*
   +----------------------------------------------------------------------+
   | PHP Version 5 / ZeroMQ 	     	     	     	     	          |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Mikko Koppanen                                    |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Mikko Kopppanen <mkoppanen@php.net>                          |
   +----------------------------------------------------------------------+
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
	
	RETURN_TRUE;
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
	
	if (zmq_send(intern_sock->socket, &(intern_msg->message), 0) != 0) {
		zend_throw_exception_ex(php_zeromq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to send the message: %s", zmq_strerror(errno));
		return;
	}
	RETURN_TRUE;
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
	
	if (zmq_msg_init_size(&(intern->message), msg_len + 1) != 0) {
	}
	
	memcpy(zmq_msg_data(&(intern->message)), msg, msg_len + 1);
	


	RETURN_TRUE;
}
/* }}} */

/* -- END ZeroMQMessage --- */

/* -- START ZeroMQSocket --- */

/* {{{ ZeroMQSocket::__construct(int type[, string dsn])
	Build a new ZeroMQSocket object
*/
PHP_METHOD(zeromqsocket, __construct)
{
	php_zeromq_socket_object *intern;
	char *dsn;
	int dsn_len = 0;
	long type;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|s", &type, &dsn, &dsn_len) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_SOCKET_OBJECT;
	intern->socket = zmq_socket(ZEROMQ_G(context), (int) type);	
	
	if (dsn_len > 0) {	
		if (zmq_bind(intern->socket, dsn) != 0) {
			zend_throw_exception_ex(php_zeromq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to bind the ZeroMQSocket: %s", zmq_strerror(errno));
			return;
		}
	}
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

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &dsn, &dsn_len) == FAILURE) {
		return;
	}
	
	intern = PHP_ZEROMQ_SOCKET_OBJECT;

	if (zmq_bind(intern->socket, dsn) != 0) {
		zend_throw_exception_ex(php_zeromq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to bind the ZeroMQSocket: %s", zmq_strerror(errno));
		return;
	}
	RETURN_TRUE;
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

static function_entry php_zeromq_class_methods[] = {
	PHP_ME(zeromq, __construct,	zeromq_construct_args,	ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(zeromq, setsocket,	zeromq_setsocket_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zeromq, send,		zeromq_send_args,		ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

ZEND_BEGIN_ARG_INFO_EX(zeromq_message_construct_args, 0, 0, 1)	
	ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()

static function_entry php_zeromq_message_class_methods[] = {
	PHP_ME(zeromqmessage, __construct,	zeromq_message_construct_args,	ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	{NULL, NULL, NULL}
};

ZEND_BEGIN_ARG_INFO_EX(zeromq_socket_construct_args, 0, 0, 2)	
	ZEND_ARG_INFO(0, type)
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zeromq_socket_bind_args, 0, 0, 1)	
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

static function_entry php_zeromq_socket_class_methods[] = {
	PHP_ME(zeromqsocket, __construct,	zeromq_socket_construct_args,	ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(zeromqsocket, bind,			zeromq_socket_bind_args,		ZEND_ACC_PUBLIC)
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

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}

static void php_zeromq_message_object_free_storage(void *object TSRMLS_DC)
{
	php_zeromq_message_object *intern = (php_zeromq_message_object *)object;

	if (!intern) {
		return;
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
	intern->socket = NULL;

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

static void php_zeromq_init_globals(zend_zeromq_globals *zeromq_globals)
{
	/* ZeroMQ context */
	zeromq_globals->context = zmq_init (1, 1, 0);
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
        zeromq_functions,			/* Functions */
        PHP_MINIT(zeromq),		/* MINIT */
        PHP_MSHUTDOWN(zeromq),	/* MSHUTDOWN */
        NULL,							/* RINIT */
        NULL,							/* RSHUTDOWN */
        PHP_MINFO(zeromq),		/* MINFO */
        PHP_ZEROMQ_EXTVER,		/* version */
        STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ZEROMQ
ZEND_GET_MODULE(zeromq)
#endif /* COMPILE_DL_ZEROMQ */