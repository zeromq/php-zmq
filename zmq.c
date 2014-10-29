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

/* PHP 5.4 */
#if PHP_VERSION_ID < 50399
# define object_properties_init(zo, class_type) { \
			zval *tmp; \
			zend_hash_copy((*zo).properties, \
							&class_type->default_properties, \
							(copy_ctor_func_t) zval_add_ref, \
							(void *) &tmp, \
							sizeof(zval *)); \
		 }
#endif

ZEND_DECLARE_MODULE_GLOBALS(php_zmq)

zend_class_entry *php_zmq_sc_entry;
zend_class_entry *php_zmq_context_sc_entry;
zend_class_entry *php_zmq_socket_sc_entry;
zend_class_entry *php_zmq_poll_sc_entry;
zend_class_entry *php_zmq_device_sc_entry;

#ifdef HAVE_CZMQ_2
zend_class_entry *php_zmq_cert_sc_entry;
zend_class_entry *php_zmq_auth_sc_entry;
#endif

zend_class_entry *php_zmq_exception_sc_entry;
zend_class_entry *php_zmq_context_exception_sc_entry;
zend_class_entry *php_zmq_socket_exception_sc_entry;
zend_class_entry *php_zmq_poll_exception_sc_entry;
zend_class_entry *php_zmq_device_exception_sc_entry;

#ifdef HAVE_CZMQ_2
zend_class_entry *php_zmq_cert_exception_sc_entry;
zend_class_entry *php_zmq_auth_exception_sc_entry;
#endif

static zend_object_handlers zmq_object_handlers;
static zend_object_handlers zmq_socket_object_handlers;
static zend_object_handlers zmq_context_object_handlers;
static zend_object_handlers zmq_poll_object_handlers;
static zend_object_handlers zmq_device_object_handlers;

#ifdef PHP_ZMQ_PTHREADS
#include <pthread.h>

static void *php_zmq_global_context = NULL;
static pthread_mutex_t php_zmq_global_context_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

#ifdef HAVE_CZMQ_2
static zend_object_handlers zmq_cert_object_handlers;
static zend_object_handlers zmq_auth_object_handlers;
#endif

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 3)
static const zend_fcall_info empty_fcall_info = { 0, NULL, NULL, NULL, NULL, 0, NULL, NULL, 0 };
#endif

zend_class_entry *php_zmq_context_exception_sc_entry_get ()
{
	return php_zmq_context_exception_sc_entry;
}

zend_class_entry *php_zmq_socket_exception_sc_entry_get ()
{
	return php_zmq_socket_exception_sc_entry;
}

zend_class_entry *php_zmq_device_exception_sc_entry_get ()
{
	return php_zmq_device_exception_sc_entry;
}

/* list entries */
static int le_zmq_socket, le_zmq_context;

/** {{{ static void php_zmq_get_lib_version(char buffer[PHP_ZMQ_VERSION_LEN])
*/
static void php_zmq_get_lib_version(char buffer[PHP_ZMQ_VERSION_LEN]) 
{
	int major = 0, minor = 0, patch = 0;
	zmq_version(&major, &minor, &patch);
	(void) snprintf(buffer, PHP_ZMQ_VERSION_LEN - 1, "%d.%d.%d", major, minor, patch);
}
/* }}} */

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

/* {{{ static void php_zmq_context_destroy(php_zmq_context *context)
	Destroy the context
*/
static void php_zmq_context_destroy(php_zmq_context *context)
{
	if (!context->is_global) {
		if(context->pid == getpid())
			(void) zmq_term(context->z_ctx);
	}
	pefree(context, context->is_persistent);
}
/* }}} */

/* {{{ static void php_zmq_socket_destroy(php_zmq_socket *zmq_sock)
	Destroy the socket (note: does not touch context)
*/
static void php_zmq_socket_destroy(php_zmq_socket *zmq_sock)
{
	zend_hash_destroy(&(zmq_sock->connect));
	zend_hash_destroy(&(zmq_sock->bind));

	if (zmq_sock->pid == getpid ())
		(void) zmq_close(zmq_sock->z_socket);

	pefree(zmq_sock, zmq_sock->is_persistent);
}
/* }}} */

/* --- START ZMQContext --- */

/* {{{ static php_zmq_context *php_zmq_context_new(long io_threads, zend_bool is_persistent, zend_bool is_global TSRMLS_DC)
	Create a new zmq context
*/
static php_zmq_context *php_zmq_context_new(long io_threads, zend_bool is_persistent, zend_bool is_global TSRMLS_DC)
{
	php_zmq_context *context;

	context = pecalloc(1, sizeof(php_zmq_context), is_persistent);
#ifdef PHP_ZMQ_PTHREADS
	if (is_global) {
		/* Guard the context creation */
		pthread_mutex_lock (&php_zmq_global_context_mutex);
		{
			if (!php_zmq_global_context) {
				php_zmq_global_context = zmq_init(io_threads);
			}
			context->z_ctx = php_zmq_global_context;
		}
		pthread_mutex_unlock (&php_zmq_global_context_mutex);
	}
#else
	if (0) {}
#endif
	else {
		context->z_ctx = zmq_init(io_threads);
	}

	if (!context->z_ctx) {
		pefree(context, is_persistent);
		return NULL;
	}

	context->io_threads    = io_threads;
	context->is_persistent = is_persistent;
	context->is_global     = is_global;
	context->pid           = getpid();
	return context;
}
/* }}} */

/* {{{ static php_zmq_context *php_zmq_context_get(long io_threads, zend_bool is_persistent TSRMLS_DC)
*/
static php_zmq_context *php_zmq_context_get(long io_threads, zend_bool is_persistent TSRMLS_DC)
{
	php_zmq_context *context;

	char plist_key[48];
	int plist_key_len;
	zend_rsrc_list_entry le, *le_p = NULL;

	if (is_persistent) {
		plist_key_len  = snprintf(plist_key, 48, "zmq_context:[%d]", io_threads);
		plist_key_len += 1;

		if (zend_hash_find(&EG(persistent_list), plist_key, plist_key_len, (void *)&le_p) == SUCCESS) {
			if (le_p->type == php_zmq_context_list_entry()) {
				return (php_zmq_context *) le_p->ptr;
			}
		}
	}

	context = php_zmq_context_new(io_threads, is_persistent, 0 TSRMLS_CC);

	if (!context) {
		return NULL;
	}

	if (is_persistent) {
		le.type = php_zmq_context_list_entry();
		le.ptr  = context;

		if (zend_hash_update(&EG(persistent_list), (char *)plist_key, plist_key_len, (void *)&le, sizeof(le), NULL) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Could not register persistent entry for the context");
		}
	}
	return context;
}
/* }}} */

/* {{{ proto ZMQ ZMQ::__construct()
	Private constructor
*/
PHP_METHOD(zmq, __construct) {}
/* }}} */

/* {{{ proto integer ZMQ::clock()
	A monotonic clock
*/
PHP_METHOD(zmq, clock)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	RETURN_LONG((long) php_zmq_clock (ZMQ_G (clock_ctx)));
}
/* }}} */

/* {{{ proto ZMQContext ZMQContext::__construct(integer $io_threads[, boolean $is_persistent = true])
	Build a new ZMQContext object
*/
PHP_METHOD(zmqcontext, __construct)
{
	php_zmq_context_object *intern;
	long io_threads = 1;
	zend_bool is_persistent = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|lb", &io_threads, &is_persistent) == FAILURE) {
		return;
	}
	intern          = PHP_ZMQ_CONTEXT_OBJECT;
	intern->context = php_zmq_context_get(io_threads, is_persistent TSRMLS_CC);

	if (!intern->context) {
		zend_throw_exception_ex(php_zmq_context_exception_sc_entry, errno TSRMLS_CC, "Error creating context: %s", zmq_strerror(errno));
		return;
	}
	return;
}
/* }}} */

#ifdef PHP_ZMQ_PTHREADS
/* {{{ proto ZMQContext ZMQContext::acquire()
	Acquires a handle to the request global context
*/
PHP_METHOD(zmqcontext, acquire)
{
	php_zmq_context *context;
	php_zmq_context_object *intern;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	// Create a request global context
	context = php_zmq_context_new(1, 1, 1 TSRMLS_CC);

	object_init_ex(return_value, php_zmq_context_sc_entry);
	intern          = (php_zmq_context_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	intern->context = context;
	return;
}
/* }}} */
#endif

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
/* {{{ proto ZMQContext ZMQContext::setOpt(int option, int value)
	Set a context option
*/
PHP_METHOD(zmqcontext, setOpt)
{
	php_zmq_context_object *intern;
	long option, value;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &option, &value) == FAILURE) {
		return;
	}
	intern = PHP_ZMQ_CONTEXT_OBJECT;

	switch (option) {
		case ZMQ_MAX_SOCKETS:
		{
			if (zmq_ctx_set(intern->context->z_ctx, option, value) != 0) {
				zend_throw_exception_ex(php_zmq_context_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set the option ZMQ::CTXOPT_MAX_SOCKETS value: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

		default:
		{
			zend_throw_exception(php_zmq_context_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
	}
	return;
}
/* }}} */

/* {{{ proto ZMQContext ZMQContext::getOpt(int option)
	Set a context option
*/
PHP_METHOD(zmqcontext, getOpt)
{
	php_zmq_context_object *intern;
	long option;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &option) == FAILURE) {
		return;
	}
	intern = PHP_ZMQ_CONTEXT_OBJECT;

	switch (option) {

		case ZMQ_MAX_SOCKETS:
		{
			int value = zmq_ctx_get(intern->context->z_ctx, option);
			RETURN_LONG(value);
		}
		break;

		default:
		{
			zend_throw_exception(php_zmq_context_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
	}
	return;
}
/* }}} */
#endif


/* {{{ static php_zmq_socket *php_zmq_socket_new(php_zmq_context *context, int type, zend_bool is_persistent TSRMLS_DC)
	Create a new zmq socket
*/
static php_zmq_socket *php_zmq_socket_new(php_zmq_context *context, int type, zend_bool is_persistent TSRMLS_DC)
{
	php_zmq_socket *zmq_sock;

	zmq_sock           = pecalloc(1, sizeof(php_zmq_socket), is_persistent);
	zmq_sock->z_socket = zmq_socket(context->z_ctx, type);
	zmq_sock->pid      = getpid();

	if (!zmq_sock->z_socket) {
		pefree(zmq_sock, is_persistent);
		return NULL;
	}

	zmq_sock->is_persistent = is_persistent;

	zend_hash_init(&(zmq_sock->connect), 0, NULL, NULL, is_persistent);
	zend_hash_init(&(zmq_sock->bind),    0, NULL, NULL, is_persistent);
	return zmq_sock;
}
/* }}} */

static char *php_zmq_socket_plist_key(int type, const char *persistent_id, int *plist_key_len)
{
	char *plist_key = NULL;
	*plist_key_len = spprintf(&plist_key, 0, "zmq_socket:[%d]-[%s]", type, persistent_id);
	return plist_key;
}

static void php_zmq_socket_store(php_zmq_socket *zmq_sock_p, int type, const char *persistent_id TSRMLS_DC)
{
	zend_rsrc_list_entry le;

	char *plist_key = NULL;
	int plist_key_len = 0;

	plist_key = php_zmq_socket_plist_key(type, persistent_id, &plist_key_len);

	le.type = php_zmq_socket_list_entry();
	le.ptr  = zmq_sock_p;

	if (zend_hash_update(&EG(persistent_list), plist_key, plist_key_len + 1, (void *)&le, sizeof(le), NULL) == FAILURE) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Could not register persistent entry for the socket");
	}
	efree(plist_key);
}

/* {{{ static php_zmq_socket *php_zmq_socket_get(php_zmq_context *context, int type, const char *persistent_id, zend_bool *is_new TSRMLS_DC)
	Tries to get context from plist and allocates a new context if context does not exist
*/
static php_zmq_socket *php_zmq_socket_get(php_zmq_context *context, int type, const char *persistent_id, zend_bool *is_new TSRMLS_DC)
{
	php_zmq_socket *zmq_sock_p;
	zend_bool is_persistent;

	is_persistent = (context->is_persistent && persistent_id) ? 1 : 0;
	*is_new        = 0;

	if (is_persistent) {
		char *plist_key = NULL;
		int plist_key_len = 0;

		zend_rsrc_list_entry *le = NULL;

		plist_key = php_zmq_socket_plist_key(type, persistent_id, &plist_key_len);

		if (zend_hash_find(&EG(persistent_list), plist_key, plist_key_len + 1, (void *)&le) == SUCCESS) {
			if (le->type == php_zmq_socket_list_entry()) {
				efree(plist_key);
				return (php_zmq_socket *) le->ptr;
			}
		}
		efree(plist_key);
	}

	zmq_sock_p = php_zmq_socket_new(context, type, is_persistent TSRMLS_CC);

	if (!zmq_sock_p) {
		return NULL;
	}

	*is_new = 1;
	return zmq_sock_p;
}
/* }}} */

char *php_zmq_printable_func (zend_fcall_info *fci, zend_fcall_info_cache *fci_cache TSRMLS_DC)
{
	char *buffer = NULL;

	if (fci->object_ptr) {
		spprintf (&buffer, 0, "%s::%s", Z_OBJCE_P (fci->object_ptr)->name, fci_cache->function_handler->common.function_name);
	} else {
		if (Z_TYPE_P (fci->function_name) == IS_OBJECT) {
			spprintf (&buffer, 0, "%s", Z_OBJCE_P (fci->function_name)->name);
		}
		else {
			spprintf (&buffer, 0, "%s", Z_STRVAL_P (fci->function_name));
		}
	}
	return buffer;
}

static zend_bool php_zmq_connect_callback(zval *socket, zend_fcall_info *fci, zend_fcall_info_cache *fci_cache, const char *persistent_id TSRMLS_DC)
{
	zval *retval_ptr, *pid_z;
	zval **params[2];
	zend_bool retval = 1;

	ALLOC_INIT_ZVAL(pid_z);

	if (persistent_id) {
		ZVAL_STRING(pid_z, persistent_id, 1);
	} else {
		ZVAL_NULL(pid_z);
	}

	/* Call the cb */
	params[0] = &socket;
	params[1] = &pid_z;

	fci->params         = params;
	fci->param_count    = 2;
	fci->retval_ptr_ptr = &retval_ptr;
	fci->no_separation  = 1;

	if (zend_call_function(fci, fci_cache TSRMLS_CC) == FAILURE) {
		if (!EG(exception)) {
			char *buf = php_zmq_printable_func (fci, fci_cache TSRMLS_CC);

			zend_throw_exception_ex(php_zmq_socket_exception_sc_entry, 0 TSRMLS_CC, "Failed to invoke 'on_new_socket' callback %s()", buf);
			efree (buf);
		}
		retval = 0;
	}
	zval_ptr_dtor(&pid_z);

	if (retval_ptr) {
		zval_ptr_dtor(&retval_ptr);
	}

	if (EG(exception)) {
		retval = 0;
	}

	return retval;
}

/* {{{ proto ZMQContext ZMQContext::getSocket(integer $type[, string $persistent_id = null[, callback $on_new_socket = null]])
	Build a new ZMQContext object
*/
PHP_METHOD(zmqcontext, getsocket)
{
	php_zmq_socket *socket;
	php_zmq_socket_object *interns;
	php_zmq_context_object *intern;
	long type;
	char *persistent_id = NULL;
	int rc, persistent_id_len;
	zend_bool is_new;

	zend_fcall_info fci;
	zend_fcall_info_cache fci_cache;

	PHP_ZMQ_ERROR_HANDLING_INIT()
	PHP_ZMQ_ERROR_HANDLING_THROW()

	fci.size = 0;
	rc = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|s!f!", &type, &persistent_id, &persistent_id_len, &fci, &fci_cache);

	PHP_ZMQ_ERROR_HANDLING_RESTORE()

	if (rc == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_CONTEXT_OBJECT;
	socket = php_zmq_socket_get(intern->context, type, persistent_id, &is_new TSRMLS_CC);

	if (!socket) {
		zend_throw_exception_ex(php_zmq_socket_exception_sc_entry, errno TSRMLS_CC, "Error creating socket: %s", zmq_strerror(errno));
		return;
	}

	object_init_ex(return_value, php_zmq_socket_sc_entry);
	interns         = (php_zmq_socket_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	interns->socket = socket;

	/* Need to add refcount if context is not persistent */
	if (!intern->context->is_persistent) {
		zend_objects_store_add_ref(getThis() TSRMLS_CC);
		interns->context_obj = getThis();
		Z_ADDREF_P(interns->context_obj);
	}

	if (is_new) {
		if(fci.size) {
			if (!php_zmq_connect_callback(return_value, &fci, &fci_cache, persistent_id TSRMLS_CC)) {
				php_zmq_socket_destroy(socket);
				interns->socket = NULL;
				zval_dtor(return_value);
				return;
			}
		}
		if (socket->is_persistent) {
			php_zmq_socket_store(socket, type, persistent_id TSRMLS_CC);
		}
	}
	if (socket->is_persistent) {
		interns->persistent_id = estrdup(persistent_id);
	}
	return;
}
/* }}} */

/* {{{ proto ZMQContext ZMQContext::isPersistent()
	Whether the context is persistent
*/
PHP_METHOD(zmqcontext, ispersistent)
{
	php_zmq_context_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_CONTEXT_OBJECT;
	RETURN_BOOL(intern->context->is_persistent);
}
/* }}} */

/* {{{ proto ZMQContext ZMQContext::__clone()
	Clones the instance of the ZMQContext class
*/
PHP_METHOD(zmqcontext, __clone) { }
/* }}} */

/* --- END ZMQContext --- */

/* --- START ZMQSocket --- */

/* {{{ proto ZMQSocket ZMQSocket::__construct(ZMQContext $context, integer $type[, string $persistent_id = null[, callback $on_new_socket = null]])
	Build a new ZMQSocket object
*/
PHP_METHOD(zmqsocket, __construct)
{
	php_zmq_socket *socket;
	php_zmq_socket_object *intern;
	php_zmq_context_object *internc;
	long type;
	char *persistent_id = NULL;
	int rc, persistent_id_len;
	zval *obj;
	zend_bool is_new;

	zend_fcall_info fci;
	zend_fcall_info_cache fci_cache;

	PHP_ZMQ_ERROR_HANDLING_INIT()
	PHP_ZMQ_ERROR_HANDLING_THROW()

	fci.size = 0;
	rc = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Ol|s!f!", &obj, php_zmq_context_sc_entry, &type, &persistent_id, &persistent_id_len, &fci, &fci_cache);

	PHP_ZMQ_ERROR_HANDLING_RESTORE()

	if (rc == FAILURE) {
		return;
	}

	internc = (php_zmq_context_object *) zend_object_store_get_object(obj TSRMLS_CC);
	socket  = php_zmq_socket_get(internc->context, type, persistent_id, &is_new TSRMLS_CC);

	if (!socket) {
		zend_throw_exception_ex(php_zmq_socket_exception_sc_entry, errno TSRMLS_CC, "Error creating socket: %s", zmq_strerror(errno));
		return;
	}

	intern         = PHP_ZMQ_SOCKET_OBJECT;
	intern->socket = socket;

	/* Need to add refcount if context is not persistent */
	if (!internc->context->is_persistent) {
	    intern->context_obj = obj;
		zend_objects_store_add_ref(intern->context_obj TSRMLS_CC);
        Z_ADDREF_P(intern->context_obj);
	}

	if (is_new) {
		if (fci.size) {
			if (!php_zmq_connect_callback(getThis(), &fci, &fci_cache, persistent_id TSRMLS_CC)) {
				php_zmq_socket_destroy(socket);
				intern->socket = NULL;
				return;
			}
		}
		if (socket->is_persistent) {
			php_zmq_socket_store(socket, type, persistent_id TSRMLS_CC);
		}
	}
	if (socket->is_persistent) {
		intern->persistent_id = estrdup(persistent_id);
	}

	return;
}
/* }}} */

/* {{{ static zend_bool php_zmq_send(php_zmq_socket_object *intern, char *message_param, int message_param_len, long flags TSRMLS_DC)
*/
static zend_bool php_zmq_send(php_zmq_socket_object *intern, char *message_param, int message_param_len, long flags TSRMLS_DC)
{
	int rc, errno_;
	zmq_msg_t message;

	if (zmq_msg_init_size(&message, message_param_len) != 0) {
		zend_throw_exception_ex(php_zmq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to initialize message structure: %s", zmq_strerror(errno));
		return 0;
	}
	memcpy(zmq_msg_data(&message), message_param, message_param_len);

	rc = zmq_sendmsg(intern->socket->z_socket, &message, flags);
	errno_ = errno;

	zmq_msg_close(&message);

	if (rc == -1) {
	    if (errno_ == EAGAIN) {
			return 0;
	    }
		zend_throw_exception_ex(php_zmq_socket_exception_sc_entry, errno_ TSRMLS_CC, "Failed to send message: %s", zmq_strerror(errno_));
		return 0;
	}

	return 1;
}
/* }}} */

static void php_zmq_sendmsg_impl(INTERNAL_FUNCTION_PARAMETERS)
{
	php_zmq_socket_object *intern;
	char *message_param;
	int message_param_len;
	long flags = 0;
	zend_bool ret;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &message_param, &message_param_len, &flags) == FAILURE) {
		return;
	}
	intern = PHP_ZMQ_SOCKET_OBJECT;
	ret = php_zmq_send(intern, message_param, message_param_len, flags TSRMLS_CC);

	if (ret) {
		ZMQ_RETURN_THIS;
	} else {
		RETURN_FALSE;
	}
}

/* {{{ proto ZMQSocket ZMQSocket::send(string $message[, integer $flags = 0])
	Send a message. Return true if message was sent and false on EAGAIN
*/
PHP_METHOD(zmqsocket, send)
{
	php_zmq_sendmsg_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 3)
static int php_zmq_send_cb(zval **ppzval, int num_args, va_list args, zend_hash_key *hash_key)
{
	TSRMLS_FETCH();
#else
static int php_zmq_send_cb(zval **ppzval TSRMLS_DC, int num_args, va_list args, zend_hash_key *hash_key)
{
#endif
    zval tmpcopy;
	php_zmq_socket_object *intern;
	int flags, *rc, *to_send;

	intern  = va_arg(args, php_zmq_socket_object *);
	flags   = va_arg(args, int);
	to_send = va_arg(args, int *);
	rc      = va_arg(args, int *);

	if (--(*to_send)) {
		flags = flags | ZMQ_SNDMORE;
	} else {
		flags = flags & ~ZMQ_SNDMORE;
	}

	tmpcopy = **ppzval;
	zval_copy_ctor(&tmpcopy);
	INIT_PZVAL(&tmpcopy);

	if (Z_TYPE(tmpcopy) != IS_STRING) {
		convert_to_string(&tmpcopy);
	}

	*rc = php_zmq_send(intern, Z_STRVAL(tmpcopy), Z_STRLEN(tmpcopy), flags TSRMLS_CC);

	zval_dtor(&tmpcopy);

	if (!*rc) {
		return ZEND_HASH_APPLY_STOP;
	}
	return ZEND_HASH_APPLY_KEEP;
}

/* {{{ proto ZMQSocket ZMQSocket::sendmulti(arrays $messages[, integer $flags = 0])
	Send a multipart message. Return true if message was sent and false on EAGAIN
*/
PHP_METHOD(zmqsocket, sendmulti)
{
	zval *messages;
	php_zmq_socket_object *intern;
	int to_send, ret = 0;
	long flags = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a|l", &messages, &flags) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;
	to_send = zend_hash_num_elements(Z_ARRVAL_P(messages));

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 3)
	zend_hash_apply_with_arguments(Z_ARRVAL_P(messages), (apply_func_args_t) php_zmq_send_cb, 4, intern, flags, &to_send, &ret);
#else
	zend_hash_apply_with_arguments(Z_ARRVAL_P(messages) TSRMLS_CC, (apply_func_args_t) php_zmq_send_cb, 4, intern, flags, &to_send, &ret);
#endif

	if (ret) {
		ZMQ_RETURN_THIS;
	} else {
		RETURN_FALSE;
	}
}

/* {{{ static zend_bool php_zmq_recv(php_zmq_socket_object *intern, long flags, zval *return_value TSRMLS_DC)
*/
static zend_bool php_zmq_recv(php_zmq_socket_object *intern, long flags, zval *return_value TSRMLS_DC)
{
	int rc, errno_;
	zmq_msg_t message;

	if (zmq_msg_init(&message) != 0) {
		zend_throw_exception_ex(php_zmq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to initialize message structure: %s", zmq_strerror(errno));
		return 0;
	}

	rc = zmq_recvmsg(intern->socket->z_socket, &message, flags);
	errno_ = errno;

	if (rc == -1) {
		zmq_msg_close(&message);
		if (errno == EAGAIN) {
			return 0;
		}
		zend_throw_exception_ex(php_zmq_socket_exception_sc_entry, errno_ TSRMLS_CC, "Failed to receive message: %s", zmq_strerror(errno_));
		return 0;
	}

	ZVAL_STRINGL(return_value, zmq_msg_data(&message), zmq_msg_size(&message), 1);
	zmq_msg_close(&message);
	return 1;
}
/* }}} */

static void php_zmq_recvmsg_impl(INTERNAL_FUNCTION_PARAMETERS)
{
	php_zmq_socket_object *intern;
	zend_bool retval;
	long flags = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &flags) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;
	retval = php_zmq_recv(intern, flags, return_value TSRMLS_CC);

	if (retval == 0) {
		RETURN_FALSE;
	}
	return;
}

/* {{{ proto string ZMQ::recv([integer $flags = 0])
	Receive a message
*/
PHP_METHOD(zmqsocket, recv)
{
	php_zmq_recvmsg_impl(INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ proto array ZMQ::recvmulti([integer $flags = 0])
	Receive an array of message parts
*/
PHP_METHOD(zmqsocket, recvmulti)
{
	php_zmq_socket_object *intern;
	size_t value_len;
	long flags = 0;
	zend_bool retval;
	zval *msg;
#if ZMQ_VERSION_MAJOR < 3	
	int64_t value;
#else
	int value;
#endif

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &flags) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;
	array_init(return_value);
	value_len = sizeof (value);

	do {
		MAKE_STD_ZVAL(msg);
		retval = php_zmq_recv(intern, flags, msg TSRMLS_CC);
		if (retval == 0) {
			FREE_ZVAL(msg);
			zval_dtor(return_value);
			RETURN_FALSE;
		}
		add_next_index_zval(return_value, msg);
		zmq_getsockopt(intern->socket->z_socket, ZMQ_RCVMORE, &value, &value_len);
	} while (value > 0);

	return;
}
/* }}} */

/** {{{ string ZMQ::getPersistentId() 
	Returns the persistent id of the object
*/
PHP_METHOD(zmqsocket, getpersistentid)
{
	php_zmq_socket_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (intern->socket->is_persistent && intern->persistent_id) {
		RETURN_STRING(intern->persistent_id, 1);
	}
	RETURN_NULL();
}
/* }}} */

/* {{{ proto ZMQSocket ZMQSocket::bind(string $dsn[, boolean $force = false])
	Bind the socket to an endpoint
*/
PHP_METHOD(zmqsocket, bind)
{
	php_zmq_socket_object *intern;
	char *dsn;
	int dsn_len;
	zend_bool force = 0;
	void *dummy = (void *)1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &dsn, &dsn_len, &force) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	/* already connected ? */
	if (!force && zend_hash_exists(&(intern->socket->bind), dsn, dsn_len + 1)) {
		ZMQ_RETURN_THIS;
	}

	if (zmq_bind(intern->socket->z_socket, dsn) != 0) {
		zend_throw_exception_ex(php_zmq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to bind the ZMQ: %s", zmq_strerror(errno));
		return;
	}

	zend_hash_add(&(intern->socket->bind), dsn, dsn_len + 1, (void *)&dummy, sizeof(void *), NULL);
	ZMQ_RETURN_THIS;
}
/* }}} */

/* {{{ proto ZMQSocket ZMQSocket::connect(string $dsn[, boolean $force = false])
	Connect the socket to an endpoint
*/
PHP_METHOD(zmqsocket, connect)
{
	php_zmq_socket_object *intern;
	char *dsn;
	int dsn_len;
	zend_bool force = 0;
	void *dummy = (void *)1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &dsn, &dsn_len, &force) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	/* already connected ? */
	if (!force && zend_hash_exists(&(intern->socket->connect), dsn, dsn_len + 1)) {
		ZMQ_RETURN_THIS;
	}

	if (zmq_connect(intern->socket->z_socket, dsn) != 0) {
		zend_throw_exception_ex(php_zmq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to connect the ZMQ: %s", zmq_strerror(errno));
		return;
	}

	(void) zend_hash_add(&(intern->socket->connect), dsn, dsn_len + 1, (void *)&dummy, sizeof(void *), NULL);
	ZMQ_RETURN_THIS;
}
/* }}} */

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
/* {{{ proto ZMQSocket ZMQSocket::unbind(string $dsn)
	Unbind the socket from an endpoint
*/
PHP_METHOD(zmqsocket, unbind)
{
	php_zmq_socket_object *intern;
	char *dsn;
	int dsn_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &dsn, &dsn_len) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (zmq_unbind(intern->socket->z_socket, dsn) != 0) {
		zend_throw_exception_ex(php_zmq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to unbind the ZMQ socket: %s", zmq_strerror(errno));
		return;
	}

	zend_hash_del(&(intern->socket->bind), dsn, dsn_len + 1);
	ZMQ_RETURN_THIS;
}
/* }}} */

/* {{{ proto ZMQSocket ZMQSocket::disconnect(string $dsn)
	Disconnect the socket from an endpoint
*/
PHP_METHOD(zmqsocket, disconnect)
{
	php_zmq_socket_object *intern;
	char *dsn;
	int dsn_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &dsn, &dsn_len) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (zmq_disconnect(intern->socket->z_socket, dsn) != 0) {
		zend_throw_exception_ex(php_zmq_socket_exception_sc_entry, errno TSRMLS_CC, "Failed to disconnect the ZMQ socket: %s", zmq_strerror(errno));
		return;
	}

	zend_hash_del(&(intern->socket->connect), dsn, dsn_len + 1);
	ZMQ_RETURN_THIS;
}
/* }}} */
#endif

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 3)
static int php_zmq_get_keys(zval **ppzval, int num_args, va_list args, zend_hash_key *hash_key)
{
	TSRMLS_FETCH();
#else
static int php_zmq_get_keys(zval **ppzval TSRMLS_DC, int num_args, va_list args, zend_hash_key *hash_key)
{
#endif
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

/* {{{ proto array ZMQ::getEndpoints()
	Returns endpoints where this socket is connected/bound to. Contains two keys ('bind', 'connect')
*/
PHP_METHOD(zmqsocket, getendpoints)
{
	php_zmq_socket_object *intern;
	zval *connect, *bind;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;
	array_init(return_value);

	MAKE_STD_ZVAL(connect);
	MAKE_STD_ZVAL(bind);

	array_init(connect);
	array_init(bind);

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 3)
	zend_hash_apply_with_arguments(&(intern->socket->connect), (apply_func_args_t) php_zmq_get_keys, 1, connect);
	zend_hash_apply_with_arguments(&(intern->socket->bind), (apply_func_args_t) php_zmq_get_keys, 1, bind);
#else
	zend_hash_apply_with_arguments(&(intern->socket->connect) TSRMLS_CC, (apply_func_args_t) php_zmq_get_keys, 1, connect);
	zend_hash_apply_with_arguments(&(intern->socket->bind) TSRMLS_CC, (apply_func_args_t) php_zmq_get_keys, 1, bind);
#endif

	add_assoc_zval(return_value, "connect", connect);
	add_assoc_zval(return_value, "bind", bind);
	return;
}
/* }}} */

/* {{{ proto integer ZMQSocket::getSocketType()
	Returns the socket type
*/
PHP_METHOD(zmqsocket, getsockettype)
{
	int type;
	size_t type_siz;
	php_zmq_socket_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}
	intern = PHP_ZMQ_SOCKET_OBJECT;
	type_siz = sizeof (int);

	if (zmq_getsockopt(intern->socket->z_socket, ZMQ_TYPE, &type, &type_siz) != -1) {
		RETURN_LONG(type);
	}
	RETURN_LONG(-1);
}
/* }}} */

/* {{{ proto boolean ZMQSocket::isPersistent()
	Whether the socket is persistent
*/
PHP_METHOD(zmqsocket, ispersistent)
{
	php_zmq_socket_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;
	RETURN_BOOL(intern->socket->is_persistent);
}
/* }}} */

/* {{{ proto ZMQSocket ZMQSocket::__clone()
	Clones the instance of the ZMQSocket class
*/
PHP_METHOD(zmqsocket, __clone) { }
/* }}} */

/* -- END ZMQSocket--- */

/* -- START ZMQPoll --- */

/* {{{ proto integer ZMQPoll::add(ZMQSocket $object, integer $events)
	Add a ZMQSocket object into the pollset
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
			if (!instanceof_function(Z_OBJCE_P(object), php_zmq_socket_sc_entry TSRMLS_CC)) {
				zend_throw_exception(php_zmq_poll_exception_sc_entry, "The first argument must be an instance of ZMQSocket or a resource", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
				return;
			}
		break;

		case IS_RESOURCE:
			/* noop */
		break;

		default:
			zend_throw_exception(php_zmq_poll_exception_sc_entry, "The first argument must be an instance of ZMQSocket or a resource", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		break;
	}

	pos = php_zmq_pollset_add(&(intern->set), object, events TSRMLS_CC);

	if (pos < 0) {
		const char *message = NULL;

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
				message = "The ZMQSocket object has not been initialized properly";
			break;

			case PHP_ZMQ_POLLSET_ERR_NO_POLL:
				message = "The ZMQSocket object has not been initialized with polling";
			break;

			default:
				message = "Unknown error";
			break;
		}

		zend_throw_exception(php_zmq_poll_exception_sc_entry, message, PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	if (!php_zmq_pollset_get_key(&(intern->set), pos, key, &key_len TSRMLS_CC)) {
		zend_throw_exception(php_zmq_poll_exception_sc_entry, "Failed to get the item key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	RETURN_STRINGL(key, key_len, 1);
}
/* }}} */

/* {{{ proto boolean ZMQPoll::remove(mixed $item)
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
		zend_throw_exception(php_zmq_poll_exception_sc_entry, "No sockets assigned to the ZMQPoll", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (Z_TYPE_P(item)) {

		case IS_OBJECT:
			if (!instanceof_function(Z_OBJCE_P(item), php_zmq_socket_sc_entry TSRMLS_CC)) {
				zend_throw_exception(php_zmq_poll_exception_sc_entry, "The object must be an instanceof ZMQSocket", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
				return;
			}
			/* break intentionally missing */
		case IS_RESOURCE:
			RETVAL_BOOL(php_zmq_pollset_delete(&(intern->set), item TSRMLS_CC));
		break;

		default:
			convert_to_string(item);
			RETVAL_BOOL(php_zmq_pollset_delete_by_key(&(intern->set), Z_STRVAL_P(item), Z_STRLEN_P(item) TSRMLS_CC));
		break;
	}

	return;
}
/* }}} */

/* {{{ proto integer ZMQPoll::poll(array &$readable, array &$writable[, integer $timeout = -1])
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
		zend_throw_exception(php_zmq_poll_exception_sc_entry, "No sockets assigned to the ZMQPoll", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	rc = php_zmq_pollset_poll(&(intern->set), timeout * PHP_ZMQ_TIMEOUT, r_array, w_array, intern->set.errors);

	if (rc == -1) {
		zend_throw_exception_ex(php_zmq_poll_exception_sc_entry, errno TSRMLS_CC, "Poll failed: %s", zmq_strerror(errno));
		return;
	}
	RETURN_LONG(rc);
}
/* }}} */

/* {{{ proto integer ZMQPoll::count()
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

/* {{{ proto ZMQPoll ZMQPoll::clear()
	Clear the pollset
*/
PHP_METHOD(zmqpoll, clear)
{
	php_zmq_poll_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_POLL_OBJECT;

	php_zmq_pollset_delete_all(&(intern->set) TSRMLS_CC);
	ZMQ_RETURN_THIS;
}
/* }}} */

/* {{{ proto array ZMQPoll::getLastErrors()
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

/* {{{ proto ZMQPoll ZMQPoll::__clone()
	Clones the instance of the ZMQPoll class
*/
PHP_METHOD(zmqpoll, __clone) { }
/* }}} */

/* -- END ZMQPoll */

/* {{{ proto void ZMQDevice::__construct(ZMQSocket frontend, ZMQSocket backend)
	Construct a device
*/
PHP_METHOD(zmqdevice, __construct)
{
	php_zmq_device_object *intern;
	zval *f, *b, *c = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "OO|O!", &f, php_zmq_socket_sc_entry, &b, php_zmq_socket_sc_entry, &c, php_zmq_socket_sc_entry) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_DEVICE_OBJECT;

	intern->front = f;
	intern->back  = b;
	if (c) {
		intern->capture = c;
		zend_objects_store_add_ref(c TSRMLS_CC);
		Z_ADDREF_P(c);
	} else
		intern->capture = NULL;

	zend_objects_store_add_ref(f TSRMLS_CC);
	Z_ADDREF_P(f);

	zend_objects_store_add_ref(b TSRMLS_CC);
	Z_ADDREF_P(b);
}
/* }}} */

/* {{{ proto void ZMQDevice::run()
	Start a device
*/
PHP_METHOD(zmqdevice, run)
{
	php_zmq_device_object *intern;
	zend_bool rc;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_DEVICE_OBJECT;
	rc = php_zmq_device (intern TSRMLS_CC);

	if (!rc && !EG (exception)) {
		zend_throw_exception_ex(php_zmq_device_exception_sc_entry, errno TSRMLS_CC, "Failed to start the device: %s", zmq_strerror (errno));
		return;
	}
	return;
}
/* }}} */

static
void s_clear_device_callback (php_zmq_device_cb_t *cb)
{
	if (cb->initialized) {
		zval_ptr_dtor(&cb->fci.function_name);

		if (cb->user_data) {
			zval_ptr_dtor(&cb->user_data);
		}
		if (cb->fci.object_ptr != NULL) {
			zval_ptr_dtor(&cb->fci.object_ptr);
		}

		memset (cb, 0, sizeof (php_zmq_device_cb_t));
		cb->initialized = 0;
	}
}

/* {{{ proto void ZMQDevice::setIdleTimeout (int $milliseconds)
	Set the idle timeout value
*/
PHP_METHOD(zmqdevice, setidletimeout)
{
	php_zmq_device_object *intern;
	long timeout;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &timeout) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_DEVICE_OBJECT;
	intern->idle_cb.timeout = timeout;
	ZMQ_RETURN_THIS;

}
/* }}} */

PHP_METHOD(zmqdevice, getidletimeout)
{
	php_zmq_device_object *intern;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_DEVICE_OBJECT;
	RETURN_LONG(intern->idle_cb.timeout);
}


PHP_METHOD(zmqdevice, settimertimeout)
{
	php_zmq_device_object *intern;
	long timeout;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &timeout) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_DEVICE_OBJECT;
	intern->timer_cb.timeout = timeout;
	ZMQ_RETURN_THIS;
}

PHP_METHOD(zmqdevice, gettimertimeout)
{
	php_zmq_device_object *intern;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_DEVICE_OBJECT;
	RETURN_LONG(intern->timer_cb.timeout);
}


static
void s_init_device_callback (php_zmq_device_cb_t *cb, zend_fcall_info *fci, zend_fcall_info_cache *fci_cache, long timeout, zval *user_data TSRMLS_DC)
{
	if (user_data) {
		cb->user_data = user_data;
		Z_ADDREF_P(user_data);
	} else {
		MAKE_STD_ZVAL (user_data);
		ZVAL_NULL(user_data);
		Z_ADDREF_P(user_data);

		cb->user_data = user_data;
	}
	memcpy (&cb->fci, fci, sizeof (*fci));
	memcpy (&cb->fci_cache, fci_cache, sizeof (*fci_cache));

	Z_ADDREF_P (fci->function_name);
	if (fci->object_ptr) {
		Z_ADDREF_P (fci->object_ptr);
	}
	cb->initialized  = 1;
	cb->scheduled_at = php_zmq_clock (ZMQ_G (clock_ctx)) + timeout;
	cb->timeout      = timeout;
}

/* {{{ proto void ZMQDevice::setIdleCallback (callable $function, integer timeout [, mixed $userdata])
	Set the idle timeout value
*/
PHP_METHOD(zmqdevice, setidlecallback)
{
	php_zmq_device_object *intern;
	zval *user_data = NULL;
	zend_fcall_info fci;
	zend_fcall_info_cache fci_cache;
	long timeout = 0;

	if (ZEND_NUM_ARGS() == 2) {
		php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "The signature for setIdleCallback has changed, please update your code");
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f|z!", &fci, &fci_cache, &user_data) == FAILURE) {
			return;
		}
	}
	else {
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "fl|z!", &fci, &fci_cache, &timeout, &user_data) == FAILURE) {
			return;
		}
	}

	intern = PHP_ZMQ_DEVICE_OBJECT;

	/* Hack for backwards compatible behaviour */
	if (!timeout) {
		if (intern->idle_cb.timeout) {
			timeout = intern->idle_cb.timeout;
		}
	}

	s_clear_device_callback (&intern->idle_cb);

	if (fci.size > 0) {
		s_init_device_callback (&intern->idle_cb, &fci, &fci_cache, timeout, user_data TSRMLS_CC);
	}
	ZMQ_RETURN_THIS;

}
/* }}} */

/* {{{ proto void ZMQDevice::setTimerCallback (callable $function, integer timeout [, mixed $userdata])
	Set the timer function
*/
PHP_METHOD(zmqdevice, settimercallback)
{
	php_zmq_device_object *intern;
	zval *user_data = NULL;
	zend_fcall_info fci;
	zend_fcall_info_cache fci_cache;
	long timeout;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "fl|z!", &fci, &fci_cache, &timeout, &user_data) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_DEVICE_OBJECT;

	s_clear_device_callback (&intern->timer_cb);
	if (fci.size > 0) {
		s_init_device_callback (&intern->timer_cb, &fci, &fci_cache, timeout, user_data TSRMLS_CC);
	}
	ZMQ_RETURN_THIS;
}
/* }}} */

/* {{{ proto ZMQDevice ZMQDevice::__clone()
	Clones the instance of the ZMQDevice class
*/
PHP_METHOD(zmqdevice, __clone) { }
/* }}} */

/* -- END ZMQPoll */

#ifdef HAVE_CZMQ_2

/* --- START ZMQCert --- */

static void php_zmq_cert_free_storage(void *object TSRMLS_DC)
{
	php_zmq_cert_object *zmq_cert = (php_zmq_cert_object *) object;

	zcert_destroy(&zmq_cert->zcert);

	zend_object_std_dtor(&zmq_cert->zend_object TSRMLS_CC);

	efree(zmq_cert);
}

static zend_object_value php_zmq_cert_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value result;
	php_zmq_cert_object *zmq_cert;

	zmq_cert = (php_zmq_cert_object *) emalloc(sizeof(php_zmq_cert_object));
	memset(&zmq_cert->zend_object, 0, sizeof(zend_object));

	/* zcert is initialised in ZMQCert#__construct. */
	zmq_cert->zcert = NULL;

	zend_object_std_init(&zmq_cert->zend_object, class_type TSRMLS_CC);
	object_properties_init(&zmq_cert->zend_object, class_type);

	result.handle = zend_objects_store_put(
		zmq_cert,
		NULL,
		(zend_objects_free_object_storage_t) php_zmq_cert_free_storage,
		NULL TSRMLS_CC
	);
	result.handlers = &zmq_cert_object_handlers;

	return result;
}

PHP_METHOD(zmqcert, __construct)
{
	char *filename;
	int filename_length;
	zend_error_handling error_handling;
	int parse_parameters_result;
	php_zmq_cert_object *intern;

	filename = NULL;

	zend_replace_error_handling(EH_THROW, php_zmq_cert_exception_sc_entry, &error_handling TSRMLS_CC);
	parse_parameters_result = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &filename, &filename_length);
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	if (parse_parameters_result != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	if (filename == NULL) {
		intern->zcert = zcert_new();

		if (intern->zcert == NULL) {
			zend_throw_exception_ex(php_zmq_cert_exception_sc_entry, PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC, "Failed to create the underlying zcert object. Is libsodium installed?", filename);
		}

		return;
	}

	intern->zcert = zcert_load(filename);

	if (intern->zcert == NULL) {
		zend_throw_exception_ex(php_zmq_cert_exception_sc_entry, PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC, "Failed to load the certificate from %s", filename);
	}

	return;
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert___construct_args, 0, 0, 0)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO();

PHP_METHOD(zmqcert, getPublicKey)
{
	php_zmq_cert_object *intern;
	byte *public_key;

	if (zend_parse_parameters_none() != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	public_key = zcert_public_key(intern->zcert);

	RETURN_STRINGL((char *) public_key, 32, 1);
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert_getPublicKey_args, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(zmqcert, getSecretKey)
{
	php_zmq_cert_object *intern;
	byte *secret_key;

	if (zend_parse_parameters_none() != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	secret_key = zcert_secret_key(intern->zcert);

	RETURN_STRINGL((char *) secret_key, 32, 1);
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert_getSecretKey_args, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(zmqcert, getPublicTxt)
{
	php_zmq_cert_object *intern;
	char *public_txt;

	if (zend_parse_parameters_none() != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	public_txt = zcert_public_txt(intern->zcert);

	RETURN_STRING(public_txt, 1);
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert_getPublicTxt_args, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(zmqcert, getSecretTxt)
{
	php_zmq_cert_object *intern;
	char *secret_txt;

	if (zend_parse_parameters_none() != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	secret_txt = zcert_secret_txt(intern->zcert);

	RETURN_STRING(secret_txt, 1);
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert_getSecretTxt_args, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(zmqcert, setMeta)
{
	php_zmq_cert_object *intern;
	char *name;
	int name_length;
	char *format;
	int format_length;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &name, &name_length, &format, &format_length) != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	zcert_set_meta(intern->zcert, name, format);

	return;
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert_setMeta_args, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO()

PHP_METHOD(zmqcert, getMeta)
{
	char *name;
	int name_length;
	php_zmq_cert_object *intern;
	char *result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_length) != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	result = zcert_meta(intern->zcert, name);

	if (result == NULL) {
		RETURN_NULL();
	}

	RETURN_STRING(result, 1);
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert_getMeta_args, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

PHP_METHOD(zmqcert, getMetaKeys)
{
	php_zmq_cert_object *intern;
	zlist_t *meta_keys;
	char *meta_key;
	int i;

	if (zend_parse_parameters_none() != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	meta_keys = zcert_meta_keys(intern->zcert);
	meta_key = (char *) zlist_first(meta_keys);

	array_init(return_value);
	i = 0;

	while (meta_key) {
		add_index_string(return_value, i, meta_key, 1);
		++i;

		meta_key = zlist_next(meta_keys);
	}

	return;
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert_getMetaKeys_args, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(zmqcert, save)
{
	php_zmq_cert_object *intern;
	char *filename;
	int filename_length;
	int zcert_save_result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_length) != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	zcert_save_result = zcert_save(intern->zcert, filename);

	if (zcert_save_result == -1) {
		zend_throw_exception_ex(php_zmq_cert_exception_sc_entry, PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC, "Failed to save the certificate to %s", filename);
	}

	return;
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert_save_args, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

PHP_METHOD(zmqcert, savePublic)
{
	char *filename;
	int filename_length;
	php_zmq_cert_object *intern;
	int zcert_save_public_result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_length) != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	zcert_save_public_result = zcert_save_public(intern->zcert, filename);

	if (zcert_save_public_result == -1) {
		zend_throw_exception_ex(php_zmq_cert_exception_sc_entry, PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC, "Failed to save the public certificate to %s", filename);
	}

	return;
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert_savePublic_args, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

PHP_METHOD(zmqcert, saveSecret)
{
	char *filename;
	int filename_length;
	php_zmq_cert_object *intern;
	int zcert_save_secret_result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_length) != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	zcert_save_secret_result = zcert_save_secret(intern->zcert, filename);

	if (zcert_save_secret_result == -1) {
		zend_throw_exception_ex(php_zmq_cert_exception_sc_entry, PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC, "Failed to save the secret certificate to %s", filename);
	}

	return;
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert_saveSecret_args, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

PHP_METHOD(zmqcert, apply)
{
	php_zmq_cert_object *intern;
	zval *object;
	php_zmq_socket_object *socket_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &object, php_zmq_socket_sc_entry) != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	socket_object = (php_zmq_socket_object *) zend_object_store_get_object(object TSRMLS_CC);

	zcert_apply(intern->zcert, socket_object->socket->z_socket);

	return;
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert_apply_args, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ZMQSocket, ZMQSocket, 0)
ZEND_END_ARG_INFO()

static zend_object_value php_zmq_cert_clone(zval *object TSRMLS_DC)
{
	php_zmq_cert_object *intern;
	zend_object_value result;
	php_zmq_cert_object *that;

	intern = (php_zmq_cert_object *) zend_object_store_get_object(object TSRMLS_CC);

	result = php_zmq_cert_new(php_zmq_cert_sc_entry TSRMLS_CC);

	that = (php_zmq_cert_object *) zend_object_store_get_object_by_handle(result.handle TSRMLS_CC);
	that->zcert = zcert_dup(intern->zcert);

	return result;
}

PHP_METHOD(zmqcert, equals)
{
	php_zmq_cert_object *intern;
	zval *object;
	php_zmq_cert_object *that;
	bool result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &object, php_zmq_cert_sc_entry) != SUCCESS) {
		return;
	}

	intern = (php_zmq_cert_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	that = (php_zmq_cert_object *) zend_object_store_get_object(object TSRMLS_CC);

	result = zcert_eq(intern->zcert, that->zcert);

	RETURN_BOOL(result);
}

ZEND_BEGIN_ARG_INFO_EX(zmqcert_equals_args, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ZMQCert, ZMQCert, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_zmq_cert_class_methods[] = {
	PHP_ME(zmqcert, __construct,	zmqcert___construct_args,	ZEND_ACC_PUBLIC|ZEND_ACC_CTOR|ZEND_ACC_FINAL)
	PHP_ME(zmqcert, getPublicKey,	zmqcert_getPublicKey_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmqcert, getSecretKey,	zmqcert_getSecretKey_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmqcert, getPublicTxt,	zmqcert_getPublicTxt_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmqcert, getSecretTxt,	zmqcert_getSecretTxt_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmqcert, setMeta,		zmqcert_setMeta_args,		ZEND_ACC_PUBLIC)
	PHP_ME(zmqcert, getMeta,		zmqcert_getMeta_args,		ZEND_ACC_PUBLIC)
	PHP_ME(zmqcert, getMetaKeys,	zmqcert_getMetaKeys_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmqcert, save,			zmqcert_save_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zmqcert, savePublic,		zmqcert_savePublic_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmqcert, saveSecret,		zmqcert_saveSecret_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmqcert, apply,			zmqcert_apply_args,			ZEND_ACC_PUBLIC)
	/* PHP_ME(zmqcert, __clone, zmqcert___clone_args, ZEND_ACC_PUBLIC) */
	PHP_ME(zmqcert, equals,			zmqcert_equals_args,		ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

/* --- END ZMQCert --- */

/* --- START ZMQAuth --- */

static void php_zmq_auth_free_storage(void *object TSRMLS_DC)
{
	php_zmq_auth_object *zmq_auth = (php_zmq_auth_object *) object;

	zauth_destroy(&zmq_auth->zauth);
	zctx_destroy(&zmq_auth->shadow_context);

	zend_object_std_dtor(&zmq_auth->zend_object TSRMLS_CC);

	efree(zmq_auth);
}

static zend_object_value php_zmq_auth_new(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value result;
	php_zmq_auth_object *zmq_auth;

	zmq_auth = (php_zmq_auth_object *) emalloc(sizeof(php_zmq_auth_object));
	memset(&zmq_auth->zend_object, 0, sizeof(zend_object));

	/* zauth is initialised in ZMQAuth#__construct. */
	zmq_auth->zauth = NULL;

	zend_object_std_init(&zmq_auth->zend_object, class_type TSRMLS_CC);
	object_properties_init(&zmq_auth->zend_object, class_type);

	result.handle = zend_objects_store_put(
		zmq_auth,
		NULL,
		(zend_objects_free_object_storage_t) php_zmq_auth_free_storage,
		NULL TSRMLS_CC
	);
	result.handlers = &zmq_auth_object_handlers;

	return result;
}

PHP_METHOD(zmqauth, __construct)
{
	php_zmq_auth_object *intern;
	zval *object;
	zend_error_handling error_handling;
	int parse_parameters_result;
	php_zmq_context_object *context_object;

	zend_replace_error_handling(EH_THROW, php_zmq_cert_exception_sc_entry, &error_handling TSRMLS_CC);
	parse_parameters_result = zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &object, php_zmq_context_sc_entry);
	zend_restore_error_handling(&error_handling TSRMLS_CC);

	if (parse_parameters_result != SUCCESS) {
		return;
	}

	intern = (php_zmq_auth_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	context_object = (php_zmq_context_object *) zend_object_store_get_object(object TSRMLS_CC);

	// NOTE (phuedx, 2014-05-14): A zauth object needs a context so that it
	// can take over authentication for all incoming connections in that
	// context. Creating a shadow context from the specified context allows
	// us to continue working with CZMQ.
	intern->shadow_context = zctx_shadow_zmq_ctx(context_object->context->z_ctx);

	if (intern->shadow_context == NULL) {
		zend_throw_exception_ex(php_zmq_auth_exception_sc_entry, PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC, "Failed to create the underlying shadow context object.");

		return;
	}

	intern->zauth = zauth_new(intern->shadow_context);

	if (intern->zauth == NULL) {
		zend_throw_exception_ex(php_zmq_auth_exception_sc_entry, PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC, "Failed to create the underlying zauth object.");
	}

	return;
}

ZEND_BEGIN_ARG_INFO_EX(zmqauth___construct_args, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, ZMQContext, ZMQContext, 0)
ZEND_END_ARG_INFO();

PHP_METHOD(zmqauth, allow)
{
	char *address;
	int address_length;
	php_zmq_auth_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &address, &address_length) != SUCCESS) {
		return;
	}

	intern = (php_zmq_auth_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	zauth_allow(intern->zauth, address);

	RETURN_ZVAL(getThis(), 1, 0);
}

ZEND_BEGIN_ARG_INFO_EX(zmqauth_allow_args, 0, 0, 1)
	ZEND_ARG_INFO(0, address)
ZEND_END_ARG_INFO();

PHP_METHOD(zmqauth, deny)
{
	char *address;
	int address_length;
	php_zmq_auth_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &address, &address_length) != SUCCESS) {
		return;
	}

	intern = (php_zmq_auth_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	zauth_deny(intern->zauth, address);

	RETURN_ZVAL(getThis(), 1, 0);
}

ZEND_BEGIN_ARG_INFO_EX(zmqauth_deny_args, 0, 0, 1)
	ZEND_ARG_INFO(0, address)
ZEND_END_ARG_INFO();

PHP_METHOD(zmqauth, configure)
{
	php_zmq_auth_object *intern;
	int parse_parameters_result;
	long type;
	char *domain;
	int domain_length;
	char *filename;
	int filename_length;

	intern = (php_zmq_auth_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	parse_parameters_result = zend_parse_parameters(
		ZEND_NUM_ARGS() TSRMLS_CC,
		"lss",
		&type,
		&domain, &domain_length,
		&filename,
		&filename_length
	);

	if (parse_parameters_result != SUCCESS) {
		return;
	}

	switch (type) {
		case PHP_ZMQ_AUTH_TYPE_PLAIN:
			zauth_configure_plain(intern->zauth, domain, filename);
		break;

		case PHP_ZMQ_AUTH_TYPE_CURVE:
			zauth_configure_curve(intern->zauth, domain, filename);
		break;

		// TODO (phuedx, 2014-05-16): CZMQ now supports GSSAPI (see
		// zauth_configure_gssapi).

		default:
			zend_throw_exception_ex(php_zmq_auth_exception_sc_entry, PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC, "Unknown auth type. Are you using one of the ZMQAuth constants?");
		break;
	}

	RETURN_ZVAL(getThis(), 1, 0);
}

ZEND_BEGIN_ARG_INFO_EX(zmqauth_configure_args, 0, 0, 3)
	ZEND_ARG_INFO(0, type)
	ZEND_ARG_INFO(0, domain)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO();

static zend_function_entry php_zmq_auth_class_methods[] = {
	PHP_ME(zmqauth, __construct,	zmqauth___construct_args,	ZEND_ACC_PUBLIC|ZEND_ACC_CTOR|ZEND_ACC_FINAL)
	PHP_ME(zmqauth, allow,			zmqauth_allow_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zmqauth, deny,			zmqauth_deny_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zmqauth, configure,		zmqauth_configure_args,		ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

/* --- END ZMQAuth --- */

#endif // HAVE_CZMQ_2

ZEND_BEGIN_ARG_INFO_EX(zmq_construct_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_clock_args, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_zmq_class_methods[] = {
	PHP_ME(zmq, __construct,    zmq_construct_args,  ZEND_ACC_PRIVATE|ZEND_ACC_CTOR)
	PHP_ME(zmq, clock,          zmq_clock_args,      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};

ZEND_BEGIN_ARG_INFO_EX(zmq_context_construct_args, 0, 0, 0)
	ZEND_ARG_INFO(0, io_threads)
	ZEND_ARG_INFO(0, persistent)
ZEND_END_ARG_INFO()

#ifdef PHP_ZMQ_PTHREADS
ZEND_BEGIN_ARG_INFO_EX(zmq_context_acquire_args, 0, 0, 0)
ZEND_END_ARG_INFO()
#endif

ZEND_BEGIN_ARG_INFO_EX(zmq_context_getsocket_args, 0, 0, 2)
	ZEND_ARG_INFO(0, type)
	ZEND_ARG_INFO(0, dsn)
	ZEND_ARG_INFO(0, on_new_socket)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_context_ispersistent_args, 0, 0, 2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_context_clone_args, 0, 0, 0)
ZEND_END_ARG_INFO()

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
ZEND_BEGIN_ARG_INFO_EX(zmq_context_setopt_args, 0, 0, 2)
	ZEND_ARG_INFO(0, option)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_context_getopt_args, 0, 0, 2)
	ZEND_ARG_INFO(0, option)
ZEND_END_ARG_INFO()
#endif

static zend_function_entry php_zmq_context_class_methods[] = {
	PHP_ME(zmqcontext, __construct,		zmq_context_construct_args,		ZEND_ACC_PUBLIC|ZEND_ACC_CTOR|ZEND_ACC_FINAL)
#ifdef PHP_ZMQ_PTHREADS
	PHP_ME(zmqcontext, acquire,			zmq_context_acquire_args,		ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
#endif
	PHP_ME(zmqcontext, getsocket,		zmq_context_getsocket_args,		ZEND_ACC_PUBLIC)
	PHP_ME(zmqcontext, ispersistent,	zmq_context_ispersistent_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmqcontext, __clone,			zmq_context_clone_args,			ZEND_ACC_PRIVATE|ZEND_ACC_FINAL)
#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
	PHP_ME(zmqcontext, setOpt,			zmq_context_setopt_args,		ZEND_ACC_PUBLIC)
	PHP_ME(zmqcontext, getOpt,			zmq_context_getopt_args,		ZEND_ACC_PUBLIC)
#endif
	{NULL, NULL, NULL}
};

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_construct_args, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, ZMQContext, ZMQContext, 0)
	ZEND_ARG_INFO(0, type)
	ZEND_ARG_INFO(0, persistent_id)
	ZEND_ARG_INFO(0, on_new_socket)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_bind_args, 0, 0, 1)
	ZEND_ARG_INFO(0, dsn)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_connect_args, 0, 0, 1)
	ZEND_ARG_INFO(0, dsn)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
ZEND_BEGIN_ARG_INFO_EX(zmq_socket_unbind_args, 0, 0, 1)
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_disconnect_args, 0, 0, 1)
	ZEND_ARG_INFO(0, dsn)
ZEND_END_ARG_INFO()
#endif

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_setsockopt_args, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_getendpoints_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_getsockettype_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_send_args, 0, 0, 1)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_recv_args, 0, 0, 0)
	ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_getpersistentid_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_getsockopt_args, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_ispersistent_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_socket_clone_args, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_zmq_socket_class_methods[] = {
	PHP_ME(zmqsocket, __construct,			zmq_socket_construct_args,			ZEND_ACC_PUBLIC|ZEND_ACC_CTOR|ZEND_ACC_FINAL)
	PHP_ME(zmqsocket, send,					zmq_socket_send_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmqsocket, recv,					zmq_socket_recv_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmqsocket, sendmulti,			zmq_socket_send_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmqsocket, recvmulti,			zmq_socket_recv_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmqsocket, bind,					zmq_socket_bind_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmqsocket, connect,				zmq_socket_connect_args,			ZEND_ACC_PUBLIC)
#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
	PHP_ME(zmqsocket, unbind,				zmq_socket_unbind_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmqsocket, disconnect,			zmq_socket_disconnect_args,			ZEND_ACC_PUBLIC)
#endif
	PHP_ME(zmqsocket, setsockopt,			zmq_socket_setsockopt_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zmqsocket, getendpoints,			zmq_socket_getendpoints_args,		ZEND_ACC_PUBLIC)
	PHP_ME(zmqsocket, getsockettype,		zmq_socket_getsockettype_args,		ZEND_ACC_PUBLIC)
	PHP_ME(zmqsocket, ispersistent,			zmq_socket_ispersistent_args,		ZEND_ACC_PUBLIC)
	PHP_ME(zmqsocket, getpersistentid,		zmq_socket_getpersistentid_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmqsocket, getsockopt,			zmq_socket_getsockopt_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zmqsocket, __clone,				zmq_socket_clone_args,				ZEND_ACC_PRIVATE|ZEND_ACC_FINAL)
	PHP_MALIAS(zmqsocket,	sendmsg, send,	zmq_socket_send_args, 				ZEND_ACC_PUBLIC)
	PHP_MALIAS(zmqsocket,	recvmsg, recv, 	zmq_socket_recv_args, 				ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

ZEND_BEGIN_ARG_INFO_EX(zmq_poll_add_args, 0, 0, 2)
	ZEND_ARG_INFO(0, entry)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_poll_poll_args, 0, 0, 2)
	ZEND_ARG_INFO(1, readable)
	ZEND_ARG_INFO(1, writable)
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

ZEND_BEGIN_ARG_INFO_EX(zmq_poll_clone_args, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_zmq_poll_class_methods[] = {
	PHP_ME(zmqpoll, add,			zmq_poll_add_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmqpoll, poll,			zmq_poll_poll_args,				ZEND_ACC_PUBLIC)
	PHP_ME(zmqpoll, getlasterrors,	zmq_poll_getlasterrors_args,	ZEND_ACC_PUBLIC)
	PHP_ME(zmqpoll, remove,			zmq_poll_remove_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zmqpoll, count,			zmq_poll_count_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zmqpoll, clear,			zmq_poll_clear_args,			ZEND_ACC_PUBLIC)
	PHP_ME(zmqpoll, __clone,		zmq_poll_clone_args,			ZEND_ACC_PRIVATE|ZEND_ACC_FINAL)
	{NULL, NULL, NULL}
};

ZEND_BEGIN_ARG_INFO_EX(zmq_device_construct_args, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, frontend, ZMQSocket, 0)
	ZEND_ARG_OBJ_INFO(0, backend, ZMQSocket, 0)
	ZEND_ARG_OBJ_INFO(0, capture, ZMQSocket, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_device_run_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_device_setidlecallback_args, 0, 0, 2)
	ZEND_ARG_INFO(0, idle_callback)
	ZEND_ARG_INFO(0, timeout)
	ZEND_ARG_INFO(0, user_data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_device_settimercallback_args, 0, 0, 2)
	ZEND_ARG_INFO(0, idle_callback)
	ZEND_ARG_INFO(0, timeout)
	ZEND_ARG_INFO(0, user_data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_device_setidletimeout_args, 0, 0, 1)
	ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_device_settimertimeout_args, 0, 0, 1)
	ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_device_getidletimeout_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_device_gettimertimeout_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(zmq_device_clone_args, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_zmq_device_class_methods[] = {
	PHP_ME(zmqdevice, __construct,      zmq_device_construct_args,         ZEND_ACC_PUBLIC|ZEND_ACC_CTOR|ZEND_ACC_FINAL)
	PHP_ME(zmqdevice, run,              zmq_device_run_args,               ZEND_ACC_PUBLIC)
	PHP_ME(zmqdevice, setidlecallback,  zmq_device_setidlecallback_args,   ZEND_ACC_PUBLIC)
	PHP_ME(zmqdevice, setidletimeout,   zmq_device_setidletimeout_args,    ZEND_ACC_PUBLIC)
	PHP_ME(zmqdevice, getidletimeout,   zmq_device_getidletimeout_args,    ZEND_ACC_PUBLIC)
	PHP_ME(zmqdevice, settimercallback, zmq_device_settimercallback_args,  ZEND_ACC_PUBLIC)
	PHP_ME(zmqdevice, settimertimeout,  zmq_device_settimertimeout_args,   ZEND_ACC_PUBLIC)
	PHP_ME(zmqdevice, gettimertimeout,  zmq_device_gettimertimeout_args,   ZEND_ACC_PUBLIC)
	PHP_ME(zmqdevice, __clone,          zmq_device_clone_args,             ZEND_ACC_PRIVATE|ZEND_ACC_FINAL)
	{NULL, NULL, NULL}
};

zend_function_entry zmq_functions[] = {
	{NULL, NULL, NULL}
};

static void php_zmq_context_object_free_storage(void *object TSRMLS_DC)
{
	php_zmq_context_object *intern = (php_zmq_context_object *)object;

	if (!intern) {
		return;
	}

	if (intern->context) {
		if (!intern->context->is_persistent) {
			php_zmq_context_destroy(intern->context);
		}
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}

static void php_zmq_socket_object_free_storage(void *object TSRMLS_DC)
{
	php_zmq_socket_object *intern = (php_zmq_socket_object *)object;

	if (!intern) {
		return;
	}

	if (intern->socket) {
		if (intern->socket->is_persistent && intern->persistent_id) {
			efree(intern->persistent_id);
		}

		if (!intern->socket->is_persistent) {
			php_zmq_socket_destroy(intern->socket);
		}
	}

	if (intern->context_obj) {
		zend_objects_store_del_ref(intern->context_obj TSRMLS_CC);
		Z_DELREF_P(intern->context_obj);
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

	php_zmq_pollset_deinit(&(intern->set) TSRMLS_CC);
	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}

static void php_zmq_device_object_free_storage(void *object TSRMLS_DC)
{
	php_zmq_device_object *intern = (php_zmq_device_object *)object;

	if (!intern) {
		return;
	}

	s_clear_device_callback (&intern->idle_cb);
	s_clear_device_callback (&intern->timer_cb);

	if (intern->front) {
		zend_objects_store_del_ref(intern->front TSRMLS_CC);
		zval_ptr_dtor (&intern->front);
	}

	if (intern->back) {
		zend_objects_store_del_ref(intern->back TSRMLS_CC);
		zval_ptr_dtor (&intern->back);
	}

	if (intern->capture) {
		zend_objects_store_del_ref(intern->capture TSRMLS_CC);
		zval_ptr_dtor (&intern->capture);
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}

static zend_object_value php_zmq_context_object_new_ex(zend_class_entry *class_type, php_zmq_context_object **ptr TSRMLS_DC)
{
	zend_object_value retval;
	php_zmq_context_object *intern;

	/* Allocate memory for it */
	intern = (php_zmq_context_object *) emalloc(sizeof(php_zmq_context_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	/* Context is initialized in the constructor */
	intern->context = NULL;

	if (ptr) {
		*ptr = intern;
	}

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	retval.handle   = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_zmq_context_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &zmq_context_object_handlers;
	return retval;
}

static zend_object_value php_zmq_socket_object_new_ex(zend_class_entry *class_type, php_zmq_socket_object **ptr TSRMLS_DC)
{
	zend_object_value retval;
	php_zmq_socket_object *intern;

	/* Allocate memory for it */
	intern = (php_zmq_socket_object *) emalloc(sizeof(php_zmq_socket_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	intern->socket        = NULL;
	intern->persistent_id = NULL;
	intern->context_obj   = NULL;

	if (ptr) {
		*ptr = intern;
	}

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	retval.handle   = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_zmq_socket_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &zmq_socket_object_handlers;
	return retval;
}

static zend_object_value php_zmq_poll_object_new_ex(zend_class_entry *class_type, php_zmq_poll_object **ptr TSRMLS_DC)
{
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
	object_properties_init(&intern->zo, class_type);

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_zmq_poll_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &zmq_poll_object_handlers;
	return retval;
}

static zend_object_value php_zmq_device_object_new_ex(zend_class_entry *class_type, php_zmq_device_object **ptr TSRMLS_DC)
{
	zend_object_value retval;
	php_zmq_device_object *intern;

	/* Allocate memory for it */
	intern = (php_zmq_device_object *) emalloc(sizeof(php_zmq_device_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	memset (&intern->idle_cb, 0, sizeof (php_zmq_device_cb_t));
	memset (&intern->timer_cb, 0, sizeof (php_zmq_device_cb_t));

	intern->front   = NULL;
	intern->back    = NULL;
	intern->capture = NULL;

	if (ptr) {
		*ptr = intern;
	}

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type);

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_zmq_device_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &zmq_device_object_handlers;
	return retval;
}

static zend_object_value php_zmq_context_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zmq_context_object_new_ex(class_type, NULL TSRMLS_CC);
}

static zend_object_value php_zmq_socket_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zmq_socket_object_new_ex(class_type, NULL TSRMLS_CC);
}

static zend_object_value php_zmq_poll_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zmq_poll_object_new_ex(class_type, NULL TSRMLS_CC);
}

static zend_object_value php_zmq_device_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_zmq_device_object_new_ex(class_type, NULL TSRMLS_CC);
}

ZEND_RSRC_DTOR_FUNC(php_zmq_context_dtor)
{
	if (rsrc->ptr) {
		php_zmq_context *ctx = (php_zmq_context *)rsrc->ptr;
		php_zmq_context_destroy(ctx);
		rsrc->ptr = NULL;
	}
}

ZEND_RSRC_DTOR_FUNC(php_zmq_socket_dtor)
{
	if (rsrc->ptr) {
		php_zmq_socket *zms = (php_zmq_socket *)rsrc->ptr;
		php_zmq_socket_destroy(zms);
		rsrc->ptr = NULL;
	}
}

static
void php_zmq_init_globals (zend_php_zmq_globals *zmq_globals)
{
	zmq_globals->clock_ctx = NULL;
}

PHP_MINIT_FUNCTION(zmq)
{
	char version[PHP_ZMQ_VERSION_LEN];
	zend_class_entry ce, ce_context, ce_socket, ce_poll, ce_device;
	zend_class_entry ce_exception, ce_context_exception, ce_socket_exception, ce_poll_exception, ce_device_exception;

#ifdef HAVE_CZMQ_2
	zend_class_entry ce_cert, ce_cert_exception, ce_auth, ce_auth_exception;
#endif

	le_zmq_context = zend_register_list_destructors_ex(NULL, php_zmq_context_dtor, "ZMQ persistent context", module_number);
	le_zmq_socket  = zend_register_list_destructors_ex(NULL, php_zmq_socket_dtor, "ZMQ persistent socket", module_number);

	memcpy(&zmq_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&zmq_context_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&zmq_socket_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&zmq_poll_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&zmq_device_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

#ifdef HAVE_CZMQ_2
	memcpy(&zmq_cert_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&zmq_auth_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
#endif

	INIT_CLASS_ENTRY(ce, "ZMQ", php_zmq_class_methods);
	ce.create_object = NULL;
	zmq_object_handlers.clone_obj = NULL;
	php_zmq_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);

	INIT_CLASS_ENTRY(ce_context, "ZMQContext", php_zmq_context_class_methods);
	ce_context.create_object = php_zmq_context_object_new;
	zmq_context_object_handlers.clone_obj = NULL;
	php_zmq_context_sc_entry = zend_register_internal_class(&ce_context TSRMLS_CC);

	INIT_CLASS_ENTRY(ce_socket, "ZMQSocket", php_zmq_socket_class_methods);
	ce_socket.create_object = php_zmq_socket_object_new;
	zmq_socket_object_handlers.clone_obj = NULL;
	php_zmq_socket_sc_entry = zend_register_internal_class(&ce_socket TSRMLS_CC);

	INIT_CLASS_ENTRY(ce_poll, "ZMQPoll", php_zmq_poll_class_methods);
	ce_poll.create_object = php_zmq_poll_object_new;
	zmq_poll_object_handlers.clone_obj = NULL;
	php_zmq_poll_sc_entry = zend_register_internal_class(&ce_poll TSRMLS_CC);

	INIT_CLASS_ENTRY(ce_device, "ZMQDevice", php_zmq_device_class_methods);
	ce_device.create_object = php_zmq_device_object_new;
	zmq_device_object_handlers.clone_obj = NULL;
	php_zmq_device_sc_entry = zend_register_internal_class(&ce_device TSRMLS_CC);

#ifdef HAVE_CZMQ_2
	INIT_CLASS_ENTRY(ce_cert, "ZMQCert", php_zmq_cert_class_methods);
	ce_cert.create_object = php_zmq_cert_new;
	zmq_cert_object_handlers.clone_obj = php_zmq_cert_clone;
	php_zmq_cert_sc_entry = zend_register_internal_class(&ce_cert TSRMLS_CC);

	INIT_CLASS_ENTRY(ce_auth, "ZMQAuth", php_zmq_auth_class_methods);
	ce_auth.create_object = php_zmq_auth_new;
	zmq_auth_object_handlers.clone_obj = NULL;
	php_zmq_auth_sc_entry = zend_register_internal_class(&ce_auth TSRMLS_CC);
#endif

	INIT_CLASS_ENTRY(ce_exception, "ZMQException", NULL);
	php_zmq_exception_sc_entry = zend_register_internal_class_ex(&ce_exception, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);
	php_zmq_exception_sc_entry->ce_flags &= ~ZEND_ACC_FINAL_CLASS;

	INIT_CLASS_ENTRY(ce_context_exception, "ZMQContextException", NULL);
	php_zmq_context_exception_sc_entry = zend_register_internal_class_ex(&ce_context_exception, php_zmq_exception_sc_entry, "ZMQException" TSRMLS_CC);
	php_zmq_context_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL_CLASS;

	INIT_CLASS_ENTRY(ce_socket_exception, "ZMQSocketException", NULL);
	php_zmq_socket_exception_sc_entry = zend_register_internal_class_ex(&ce_socket_exception, php_zmq_exception_sc_entry, "ZMQException" TSRMLS_CC);
	php_zmq_socket_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL_CLASS;

	INIT_CLASS_ENTRY(ce_poll_exception, "ZMQPollException", NULL);
	php_zmq_poll_exception_sc_entry = zend_register_internal_class_ex(&ce_poll_exception, php_zmq_exception_sc_entry, "ZMQException" TSRMLS_CC);
	php_zmq_poll_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL_CLASS;

	INIT_CLASS_ENTRY(ce_device_exception, "ZMQDeviceException", NULL);
	php_zmq_device_exception_sc_entry = zend_register_internal_class_ex(&ce_device_exception, php_zmq_exception_sc_entry, "ZMQException" TSRMLS_CC);
	php_zmq_device_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL_CLASS;

#ifdef HAVE_CZMQ_2
	INIT_CLASS_ENTRY(ce_cert_exception, "ZMQCertException", NULL);
	php_zmq_cert_exception_sc_entry = zend_register_internal_class_ex(&ce_cert_exception, php_zmq_exception_sc_entry, "ZMQException" TSRMLS_CC);
	php_zmq_cert_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL_CLASS;

	INIT_CLASS_ENTRY(ce_auth_exception, "ZMQAuthException", NULL);
	php_zmq_auth_exception_sc_entry = zend_register_internal_class_ex(&ce_auth_exception, php_zmq_exception_sc_entry, "ZMQException" TSRMLS_CC);
	php_zmq_auth_exception_sc_entry->ce_flags |= ZEND_ACC_FINAL_CLASS;
#endif

	ZEND_INIT_MODULE_GLOBALS(php_zmq, php_zmq_init_globals, NULL);

	ZMQ_G(clock_ctx) = php_zmq_clock_init ();

	if (!ZMQ_G(clock_ctx)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed to initialise clock");
		return FAILURE;
	}

#define PHP_ZMQ_REGISTER_CONST_LONG(const_name, value) \
	zend_declare_class_constant_long(php_zmq_sc_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);
#define PHP_ZMQ_REGISTER_CONST_STRING(const_name, value) \
	zend_declare_class_constant_string (php_zmq_sc_entry, const_name, sizeof(const_name)-1, value TSRMLS_CC);

	/* Socket constants */
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_PAIR", ZMQ_PAIR);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_PUB", ZMQ_PUB);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_SUB", ZMQ_SUB);
#if ZMQ_VERSION_MAJOR >= 3
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_XSUB", ZMQ_XSUB);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_XPUB", ZMQ_XPUB);
#endif
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_REQ", ZMQ_REQ);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_REP", ZMQ_REP);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_XREQ", ZMQ_XREQ);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_XREP", ZMQ_XREP);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_PUSH", ZMQ_PUSH);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_PULL", ZMQ_PULL);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_DEALER", ZMQ_DEALER);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_ROUTER", ZMQ_ROUTER);
#if ZMQ_VERSION_MAJOR >= 4
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_STREAM", ZMQ_STREAM);
#endif

	/* 2.0? */
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_UPSTREAM", ZMQ_PULL);
	PHP_ZMQ_REGISTER_CONST_LONG("SOCKET_DOWNSTREAM", ZMQ_PUSH);

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0
	PHP_ZMQ_REGISTER_CONST_LONG("MODE_SNDLABEL", ZMQ_SNDLABEL);
#endif

	PHP_ZMQ_REGISTER_CONST_LONG("POLL_IN", ZMQ_POLLIN);
	PHP_ZMQ_REGISTER_CONST_LONG("POLL_OUT", ZMQ_POLLOUT);

	PHP_ZMQ_REGISTER_CONST_LONG("MODE_SNDMORE", ZMQ_SNDMORE);
	PHP_ZMQ_REGISTER_CONST_LONG("MODE_NOBLOCK", ZMQ_DONTWAIT);
	PHP_ZMQ_REGISTER_CONST_LONG("MODE_DONTWAIT", ZMQ_DONTWAIT);

	PHP_ZMQ_REGISTER_CONST_LONG("DEVICE_FORWARDER", ZMQ_FORWARDER);
	PHP_ZMQ_REGISTER_CONST_LONG("DEVICE_QUEUE", ZMQ_QUEUE);
	PHP_ZMQ_REGISTER_CONST_LONG("DEVICE_STREAMER", ZMQ_STREAMER);

	PHP_ZMQ_REGISTER_CONST_LONG("ERR_INTERNAL", PHP_ZMQ_INTERNAL_ERROR);
	PHP_ZMQ_REGISTER_CONST_LONG("ERR_EAGAIN", EAGAIN);
	PHP_ZMQ_REGISTER_CONST_LONG("ERR_ENOTSUP", ENOTSUP);
	PHP_ZMQ_REGISTER_CONST_LONG("ERR_EFSM", EFSM);
	PHP_ZMQ_REGISTER_CONST_LONG("ERR_ETERM", ETERM);

	php_zmq_get_lib_version(version);
	PHP_ZMQ_REGISTER_CONST_STRING("LIBZMQ_VER", version);

	php_zmq_register_sockopt_constants (php_zmq_sc_entry TSRMLS_CC);

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR >= 2) || ZMQ_VERSION_MAJOR > 3
	PHP_ZMQ_REGISTER_CONST_LONG("CTXOPT_MAX_SOCKETS", ZMQ_MAX_SOCKETS);
	PHP_ZMQ_REGISTER_CONST_LONG("CTXOPT_MAX_SOCKETS_DEFAULT", ZMQ_MAX_SOCKETS_DFLT);
#endif

#ifdef HAVE_CZMQ_2
	PHP_ZMQ_REGISTER_CONST_STRING("CURVE_ALLOW_ANY", CURVE_ALLOW_ANY);

	zend_declare_class_constant_long(php_zmq_auth_sc_entry, "AUTH_TYPE_PLAIN", 15, (long)PHP_ZMQ_AUTH_TYPE_PLAIN TSRMLS_CC);
	zend_declare_class_constant_long(php_zmq_auth_sc_entry, "AUTH_TYPE_CURVE", 15, (long)PHP_ZMQ_AUTH_TYPE_CURVE TSRMLS_CC);
#endif

#undef PHP_ZMQ_REGISTER_CONST_LONG
#undef PHP_ZMQ_REGISTER_CONST_STRING

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(zmq)
{
#ifdef PHP_ZMQ_PTHREADS
	if (php_zmq_global_context) {
		zmq_term (php_zmq_global_context);
		php_zmq_global_context = NULL;
	}
#endif
	php_zmq_clock_destroy (&ZMQ_G (clock_ctx));
	return SUCCESS;
}

PHP_MINFO_FUNCTION(zmq)
{
	char version[PHP_ZMQ_VERSION_LEN];
	php_zmq_get_lib_version(version);

	php_info_print_table_start();

		php_info_print_table_header(2, "ZMQ extension", "enabled");
		php_info_print_table_row(2, "ZMQ extension version", PHP_ZMQ_VERSION);
		php_info_print_table_row(2, "libzmq version", version);

	php_info_print_table_end();
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
	PHP_ZMQ_VERSION,		/* version */
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ZMQ
ZEND_GET_MODULE(zmq)
#endif /* COMPILE_DL_ZMQ */
