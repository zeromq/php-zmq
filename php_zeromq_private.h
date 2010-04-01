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

#ifndef _PHP_ZEROMQ_PRIVATE_H_
# define _PHP_ZEROMQ_PRIVATE_H_

#include "ext/standard/info.h"
#include "Zend/zend_exceptions.h"

#include <stdint.h>
#include <zmq.h>


/* {{{ typedef struct _php_zeromq_socket */
typedef struct _php_zeromq_socket  {
	void *socket;
	void *context;
	zend_bool is_persistent;
	
	HashTable connect;
	HashTable bind;
} php_zeromq_socket;
/* }}} */

/* {{{ typedef struct _php_zeromq_object */
typedef struct _php_zeromq_object  {
	zend_object zo;
	zval *sock_obj;
} php_zeromq_object;
/* }}} */

/* {{{ typedef struct _php_zeromq_message_object */
typedef struct _php_zeromq_message_object  {
	zend_object zo;
	zmq_msg_t *message;
} php_zeromq_message_object;
/* }}} */

/* {{{ typedef struct _php_zeromq_socket_object */
typedef struct _php_zeromq_socket_object  {
	zend_object zo;
	php_zeromq_socket *zms;
} php_zeromq_socket_object;
/* }}} */

ZEND_BEGIN_MODULE_GLOBALS(zeromq)
	HashTable sockets;
ZEND_END_MODULE_GLOBALS(zeromq)

ZEND_EXTERN_MODULE_GLOBALS(zeromq);

#ifdef ZTS
# define ZEROMQ_G(v) TSRMG(zeromq_globals_id, zend_zeromq_globals *, v)
#else
# define ZEROMQ_G(v) (zeromq_globals.v)
#endif

#define PHP_ZEROMQ_OBJECT (php_zeromq_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

#define PHP_ZEROMQ_MESSAGE_OBJECT (php_zeromq_message_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

#define PHP_ZEROMQ_SOCKET_OBJECT (php_zeromq_socket_object *)zend_object_store_get_object(getThis() TSRMLS_CC);


#define ZEROMQ_RETURN_THIS RETURN_ZVAL(getThis(), 1, 0);

#endif /* _PHP_ZEROMQ_PRIVATE_H_ */