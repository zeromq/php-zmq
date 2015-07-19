
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
	
#if ZMQ_VERSION_MAJOR == 2 && ZMQ_VERSION_MINOR < 2

/* {{{ proto mixed ZMQSocket::getSockOpt()
	Get a socket option
*/
PHP_METHOD(zmqsocket, getsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	size_t value_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &key) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

		
		case ZMQ_HWM:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_HWM value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SWAP:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SWAP value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_AFFINITY:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_AFFINITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_IDENTITY:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IDENTITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
		
		case ZMQ_RATE:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RATE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECOVERY_IVL:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECOVERY_IVL_MSEC:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL_MSEC value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_MCAST_LOOP:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_MCAST_LOOP value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDBUF:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVBUF:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_LINGER:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_LINGER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_BACKLOG:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_BACKLOG value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_SUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_UNSUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
		
		case ZMQ_TYPE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TYPE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVMORE:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVMORE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_EVENTS:
		{
			uint32_t value;

			value_len = sizeof(uint32_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_EVENTS value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	

		case ZMQ_FD:
		{
			php_stream *stm = php_zmq_create_zmq_fd(getThis() TSRMLS_CC);
			if (stm) {
				php_stream_to_zval(stm, return_value);
				return;
			}
			RETURN_FALSE;
		}
		break;

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
	}
}

	

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
	Set a socket option
*/
PHP_METHOD(zmqsocket, setsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	zval *pz_value;
	int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz/", &key, &pz_value) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

	

		case ZMQ_HWM:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_HWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SWAP:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SWAP option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_AFFINITY:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_AFFINITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_IDENTITY:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_IDENTITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RATE:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RATE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECOVERY_IVL:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECOVERY_IVL_MSEC:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL_MSEC option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_MCAST_LOOP:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_MCAST_LOOP option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SNDBUF:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVBUF:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_LINGER:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_LINGER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_BACKLOG:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_BACKLOG option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_UNSUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		case ZMQ_TYPE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_RCVMORE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	}
	ZMQ_RETURN_THIS;
}

	

void php_zmq_register_sockopt_constants (zend_class_entry *php_zmq_sc_entry TSRMLS_DC)
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
	zend_declare_class_constant_long(php_zmq_sc_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HWM", ZMQ_HWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SWAP", ZMQ_SWAP);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_AFFINITY", ZMQ_AFFINITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IDENTITY", ZMQ_IDENTITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RATE", ZMQ_RATE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL_MSEC", ZMQ_RECOVERY_IVL_MSEC);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MCAST_LOOP", ZMQ_MCAST_LOOP);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDBUF", ZMQ_SNDBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVBUF", ZMQ_RCVBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LINGER", ZMQ_LINGER);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL", ZMQ_RECONNECT_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL_MAX", ZMQ_RECONNECT_IVL_MAX);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_BACKLOG", ZMQ_BACKLOG);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SUBSCRIBE", ZMQ_SUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TYPE", ZMQ_TYPE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVMORE", ZMQ_RCVMORE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_FD", ZMQ_FD);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_EVENTS", ZMQ_EVENTS);
			
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
			
#endif

#if ZMQ_VERSION_MAJOR == 2 && ZMQ_VERSION_MINOR >= 2

/* {{{ proto mixed ZMQSocket::getSockOpt()
	Get a socket option
*/
PHP_METHOD(zmqsocket, getsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	size_t value_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &key) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

		
		case ZMQ_HWM:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_HWM value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SWAP:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SWAP value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_AFFINITY:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_AFFINITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_IDENTITY:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IDENTITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
		
		case ZMQ_RATE:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RATE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECOVERY_IVL:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECOVERY_IVL_MSEC:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL_MSEC value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_MCAST_LOOP:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_MCAST_LOOP value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDBUF:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVBUF:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_LINGER:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_LINGER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_BACKLOG:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_BACKLOG value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_SUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_UNSUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
		
		case ZMQ_TYPE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TYPE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVMORE:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVMORE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_EVENTS:
		{
			uint32_t value;

			value_len = sizeof(uint32_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_EVENTS value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDTIMEO:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVTIMEO:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	

		case ZMQ_FD:
		{
			php_stream *stm = php_zmq_create_zmq_fd(getThis() TSRMLS_CC);
			if (stm) {
				php_stream_to_zval(stm, return_value);
				return;
			}
			RETURN_FALSE;
		}
		break;

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
	}
}

	

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
	Set a socket option
*/
PHP_METHOD(zmqsocket, setsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	zval *pz_value;
	int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz/", &key, &pz_value) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

	

		case ZMQ_HWM:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_HWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SWAP:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SWAP option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_AFFINITY:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_AFFINITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_IDENTITY:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_IDENTITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RATE:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RATE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECOVERY_IVL:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECOVERY_IVL_MSEC:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL_MSEC option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_MCAST_LOOP:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_MCAST_LOOP option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SNDBUF:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVBUF:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_LINGER:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_LINGER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_BACKLOG:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_BACKLOG option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_UNSUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		case ZMQ_TYPE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_RCVMORE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	

		case ZMQ_SNDTIMEO:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVTIMEO:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	}
	ZMQ_RETURN_THIS;
}

	

void php_zmq_register_sockopt_constants (zend_class_entry *php_zmq_sc_entry TSRMLS_DC)
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
	zend_declare_class_constant_long(php_zmq_sc_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HWM", ZMQ_HWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SWAP", ZMQ_SWAP);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_AFFINITY", ZMQ_AFFINITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IDENTITY", ZMQ_IDENTITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RATE", ZMQ_RATE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL_MSEC", ZMQ_RECOVERY_IVL_MSEC);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MCAST_LOOP", ZMQ_MCAST_LOOP);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDBUF", ZMQ_SNDBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVBUF", ZMQ_RCVBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LINGER", ZMQ_LINGER);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL", ZMQ_RECONNECT_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL_MAX", ZMQ_RECONNECT_IVL_MAX);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_BACKLOG", ZMQ_BACKLOG);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SUBSCRIBE", ZMQ_SUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TYPE", ZMQ_TYPE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVMORE", ZMQ_RCVMORE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_FD", ZMQ_FD);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_EVENTS", ZMQ_EVENTS);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDTIMEO", ZMQ_SNDTIMEO);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVTIMEO", ZMQ_RCVTIMEO);
			
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
			
#endif

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0

/* {{{ proto mixed ZMQSocket::getSockOpt()
	Get a socket option
*/
PHP_METHOD(zmqsocket, getsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	size_t value_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &key) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

		
		case ZMQ_SNDHWM:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDHWM value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVHWM:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVHWM value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_AFFINITY:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_AFFINITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_IDENTITY:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IDENTITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
		
		case ZMQ_RATE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RATE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECOVERY_IVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDBUF:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVBUF:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_LINGER:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_LINGER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_BACKLOG:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_BACKLOG value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_MAXMSGSIZE:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_SUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_UNSUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
		
		case ZMQ_TYPE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TYPE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVMORE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVMORE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_EVENTS:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_EVENTS value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDTIMEO:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVTIMEO:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVLABEL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVLABEL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	

		case ZMQ_FD:
		{
			php_stream *stm = php_zmq_create_zmq_fd(getThis() TSRMLS_CC);
			if (stm) {
				php_stream_to_zval(stm, return_value);
				return;
			}
			RETURN_FALSE;
		}
		break;

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
	}
}

	

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
	Set a socket option
*/
PHP_METHOD(zmqsocket, setsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	zval *pz_value;
	int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz/", &key, &pz_value) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

	

		case ZMQ_SNDHWM:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDHWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVHWM:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVHWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_AFFINITY:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_AFFINITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_IDENTITY:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_IDENTITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RATE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RATE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECOVERY_IVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SNDBUF:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVBUF:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_LINGER:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_LINGER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_BACKLOG:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_BACKLOG option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_MAXMSGSIZE:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_UNSUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		case ZMQ_TYPE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_RCVMORE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	

		case ZMQ_SNDTIMEO:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVTIMEO:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		case ZMQ_RCVLABEL:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_RCVLABEL is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		
		case ZMQ_HWM:
		{
			int value;
			convert_to_long(pz_value);

			if (Z_LVAL_P(pz_value) < 0) {
				zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The option value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
				return;
			}
			value = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

			if (status == 0) {
				status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
			}
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_HWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;
	

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	}
	ZMQ_RETURN_THIS;
}

	

void php_zmq_register_sockopt_constants (zend_class_entry *php_zmq_sc_entry TSRMLS_DC)
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
	zend_declare_class_constant_long(php_zmq_sc_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HWM", ZMQ_HWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDHWM", ZMQ_SNDHWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVHWM", ZMQ_RCVHWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_AFFINITY", ZMQ_AFFINITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IDENTITY", ZMQ_IDENTITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RATE", ZMQ_RATE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDBUF", ZMQ_SNDBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVBUF", ZMQ_RCVBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LINGER", ZMQ_LINGER);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL", ZMQ_RECONNECT_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL_MAX", ZMQ_RECONNECT_IVL_MAX);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_BACKLOG", ZMQ_BACKLOG);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MAXMSGSIZE", ZMQ_MAXMSGSIZE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SUBSCRIBE", ZMQ_SUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TYPE", ZMQ_TYPE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVMORE", ZMQ_RCVMORE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_FD", ZMQ_FD);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_EVENTS", ZMQ_EVENTS);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDTIMEO", ZMQ_SNDTIMEO);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVTIMEO", ZMQ_RCVTIMEO);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVLABEL", ZMQ_RCVLABEL);
			
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
			
#endif

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 1

/* {{{ proto mixed ZMQSocket::getSockOpt()
	Get a socket option
*/
PHP_METHOD(zmqsocket, getsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	size_t value_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &key) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

		
		case ZMQ_SNDHWM:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDHWM value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVHWM:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVHWM value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_AFFINITY:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_AFFINITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_IDENTITY:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IDENTITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
		
		case ZMQ_RATE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RATE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECOVERY_IVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDBUF:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVBUF:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_LINGER:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_LINGER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_BACKLOG:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_BACKLOG value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_MAXMSGSIZE:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_SUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_UNSUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
		
		case ZMQ_TYPE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TYPE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVMORE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVMORE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_EVENTS:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_EVENTS value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDTIMEO:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVTIMEO:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	

		case ZMQ_FD:
		{
			php_stream *stm = php_zmq_create_zmq_fd(getThis() TSRMLS_CC);
			if (stm) {
				php_stream_to_zval(stm, return_value);
				return;
			}
			RETURN_FALSE;
		}
		break;

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
	}
}

	

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
	Set a socket option
*/
PHP_METHOD(zmqsocket, setsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	zval *pz_value;
	int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz/", &key, &pz_value) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

	

		case ZMQ_SNDHWM:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDHWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVHWM:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVHWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_AFFINITY:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_AFFINITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_IDENTITY:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_IDENTITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RATE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RATE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECOVERY_IVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SNDBUF:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVBUF:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_LINGER:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_LINGER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_BACKLOG:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_BACKLOG option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_MAXMSGSIZE:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_UNSUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		case ZMQ_TYPE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_RCVMORE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	

		case ZMQ_SNDTIMEO:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVTIMEO:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		
		case ZMQ_HWM:
		{
			int value;
			convert_to_long(pz_value);

			if (Z_LVAL_P(pz_value) < 0) {
				zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The option value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
				return;
			}
			value = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

			if (status == 0) {
				status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
			}
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_HWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;
	

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	}
	ZMQ_RETURN_THIS;
}

	

void php_zmq_register_sockopt_constants (zend_class_entry *php_zmq_sc_entry TSRMLS_DC)
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
	zend_declare_class_constant_long(php_zmq_sc_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HWM", ZMQ_HWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDHWM", ZMQ_SNDHWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVHWM", ZMQ_RCVHWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_AFFINITY", ZMQ_AFFINITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IDENTITY", ZMQ_IDENTITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RATE", ZMQ_RATE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDBUF", ZMQ_SNDBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVBUF", ZMQ_RCVBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LINGER", ZMQ_LINGER);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL", ZMQ_RECONNECT_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL_MAX", ZMQ_RECONNECT_IVL_MAX);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_BACKLOG", ZMQ_BACKLOG);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MAXMSGSIZE", ZMQ_MAXMSGSIZE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SUBSCRIBE", ZMQ_SUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TYPE", ZMQ_TYPE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVMORE", ZMQ_RCVMORE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_FD", ZMQ_FD);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_EVENTS", ZMQ_EVENTS);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDTIMEO", ZMQ_SNDTIMEO);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVTIMEO", ZMQ_RCVTIMEO);
			
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
			
#endif

#if (ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 2 && ZMQ_VERSION_PATCH == 0)

/* {{{ proto mixed ZMQSocket::getSockOpt()
	Get a socket option
*/
PHP_METHOD(zmqsocket, getsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	size_t value_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &key) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

		
		case ZMQ_SNDHWM:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDHWM value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVHWM:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVHWM value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_AFFINITY:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_AFFINITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_IDENTITY:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IDENTITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
		
		case ZMQ_RATE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RATE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECOVERY_IVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDBUF:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVBUF:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_LINGER:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_LINGER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_BACKLOG:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_BACKLOG value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_MAXMSGSIZE:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_SUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_UNSUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
		
		case ZMQ_TYPE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TYPE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVMORE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVMORE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_EVENTS:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_EVENTS value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDTIMEO:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVTIMEO:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_IPV4ONLY:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IPV4ONLY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_LAST_ENDPOINT:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_LAST_ENDPOINT value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len - 1, 1);
		}
		break;
		
		case ZMQ_TCP_KEEPALIVE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_TCP_KEEPALIVE_IDLE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_TCP_KEEPALIVE_CNT:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_TCP_KEEPALIVE_INTVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_TCP_ACCEPT_FILTER:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_ACCEPT_FILTER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
	

		case ZMQ_FD:
		{
			php_stream *stm = php_zmq_create_zmq_fd(getThis() TSRMLS_CC);
			if (stm) {
				php_stream_to_zval(stm, return_value);
				return;
			}
			RETURN_FALSE;
		}
		break;

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
	}
}

	

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
	Set a socket option
*/
PHP_METHOD(zmqsocket, setsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	zval *pz_value;
	int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz/", &key, &pz_value) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

	

		case ZMQ_SNDHWM:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDHWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVHWM:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVHWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_AFFINITY:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_AFFINITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_IDENTITY:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_IDENTITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RATE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RATE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECOVERY_IVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SNDBUF:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVBUF:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_LINGER:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_LINGER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_BACKLOG:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_BACKLOG option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_MAXMSGSIZE:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_UNSUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		case ZMQ_TYPE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_RCVMORE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	

		case ZMQ_SNDTIMEO:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVTIMEO:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_IPV4ONLY:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_IPV4ONLY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		case ZMQ_LAST_ENDPOINT:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_LAST_ENDPOINT is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	

		case ZMQ_TCP_KEEPALIVE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_TCP_KEEPALIVE_IDLE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_TCP_KEEPALIVE_CNT:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_TCP_KEEPALIVE_INTVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_TCP_ACCEPT_FILTER:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_ACCEPT_FILTER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		
		case ZMQ_HWM:
		{
			int value;
			convert_to_long(pz_value);

			if (Z_LVAL_P(pz_value) < 0) {
				zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The option value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
				return;
			}
			value = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

			if (status == 0) {
				status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
			}
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_HWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;
	

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	}
	ZMQ_RETURN_THIS;
}

	

void php_zmq_register_sockopt_constants (zend_class_entry *php_zmq_sc_entry TSRMLS_DC)
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
	zend_declare_class_constant_long(php_zmq_sc_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HWM", ZMQ_HWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDHWM", ZMQ_SNDHWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVHWM", ZMQ_RCVHWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_AFFINITY", ZMQ_AFFINITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IDENTITY", ZMQ_IDENTITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RATE", ZMQ_RATE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDBUF", ZMQ_SNDBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVBUF", ZMQ_RCVBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LINGER", ZMQ_LINGER);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL", ZMQ_RECONNECT_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL_MAX", ZMQ_RECONNECT_IVL_MAX);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_BACKLOG", ZMQ_BACKLOG);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MAXMSGSIZE", ZMQ_MAXMSGSIZE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SUBSCRIBE", ZMQ_SUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TYPE", ZMQ_TYPE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVMORE", ZMQ_RCVMORE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_FD", ZMQ_FD);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_EVENTS", ZMQ_EVENTS);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDTIMEO", ZMQ_SNDTIMEO);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVTIMEO", ZMQ_RCVTIMEO);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IPV4ONLY", ZMQ_IPV4ONLY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LAST_ENDPOINT", ZMQ_LAST_ENDPOINT);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE", ZMQ_TCP_KEEPALIVE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_IDLE", ZMQ_TCP_KEEPALIVE_IDLE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_CNT", ZMQ_TCP_KEEPALIVE_CNT);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_INTVL", ZMQ_TCP_KEEPALIVE_INTVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_ACCEPT_FILTER", ZMQ_TCP_ACCEPT_FILTER);
			
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
			
#endif

#if (ZMQ_VERSION_MAJOR == 3 && ((ZMQ_VERSION_MINOR == 2 && ZMQ_VERSION_PATCH > 0) || (ZMQ_VERSION_MINOR > 2)))

/* {{{ proto mixed ZMQSocket::getSockOpt()
	Get a socket option
*/
PHP_METHOD(zmqsocket, getsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	size_t value_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &key) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

		
		case ZMQ_SNDHWM:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDHWM value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVHWM:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVHWM value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_AFFINITY:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_AFFINITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_IDENTITY:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IDENTITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
		
		case ZMQ_RATE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RATE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECOVERY_IVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDBUF:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVBUF:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_LINGER:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_LINGER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_BACKLOG:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_BACKLOG value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_MAXMSGSIZE:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_SUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_UNSUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
		
		case ZMQ_TYPE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TYPE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVMORE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVMORE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_EVENTS:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_EVENTS value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDTIMEO:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVTIMEO:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_IPV4ONLY:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IPV4ONLY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_LAST_ENDPOINT:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_LAST_ENDPOINT value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len - 1, 1);
		}
		break;
		
		case ZMQ_TCP_KEEPALIVE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_TCP_KEEPALIVE_IDLE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_TCP_KEEPALIVE_CNT:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_TCP_KEEPALIVE_INTVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_TCP_ACCEPT_FILTER:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_ACCEPT_FILTER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
		
		case ZMQ_DELAY_ATTACH_ON_CONNECT:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_DELAY_ATTACH_ON_CONNECT value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_XPUB_VERBOSE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_XPUB_VERBOSE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_ROUTER_MANDATORY:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_ROUTER_MANDATORY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	

		case ZMQ_FD:
		{
			php_stream *stm = php_zmq_create_zmq_fd(getThis() TSRMLS_CC);
			if (stm) {
				php_stream_to_zval(stm, return_value);
				return;
			}
			RETURN_FALSE;
		}
		break;

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
	}
}

	

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
	Set a socket option
*/
PHP_METHOD(zmqsocket, setsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	zval *pz_value;
	int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz/", &key, &pz_value) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

	

		case ZMQ_SNDHWM:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDHWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVHWM:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVHWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_AFFINITY:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_AFFINITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_IDENTITY:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_IDENTITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RATE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RATE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECOVERY_IVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SNDBUF:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVBUF:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_LINGER:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_LINGER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_BACKLOG:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_BACKLOG option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_MAXMSGSIZE:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_UNSUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		case ZMQ_TYPE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_RCVMORE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	

		case ZMQ_SNDTIMEO:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVTIMEO:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_IPV4ONLY:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_IPV4ONLY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		case ZMQ_LAST_ENDPOINT:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_LAST_ENDPOINT is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	

		case ZMQ_TCP_KEEPALIVE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_TCP_KEEPALIVE_IDLE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_TCP_KEEPALIVE_CNT:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_TCP_KEEPALIVE_INTVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_TCP_ACCEPT_FILTER:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_ACCEPT_FILTER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_DELAY_ATTACH_ON_CONNECT:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_DELAY_ATTACH_ON_CONNECT option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_XPUB_VERBOSE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_XPUB_VERBOSE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_ROUTER_MANDATORY:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_ROUTER_MANDATORY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		
		case ZMQ_HWM:
		{
			int value;
			convert_to_long(pz_value);

			if (Z_LVAL_P(pz_value) < 0) {
				zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The option value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
				return;
			}
			value = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

			if (status == 0) {
				status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
			}
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_HWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;
	

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	}
	ZMQ_RETURN_THIS;
}

	

void php_zmq_register_sockopt_constants (zend_class_entry *php_zmq_sc_entry TSRMLS_DC)
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
	zend_declare_class_constant_long(php_zmq_sc_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HWM", ZMQ_HWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDHWM", ZMQ_SNDHWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVHWM", ZMQ_RCVHWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_AFFINITY", ZMQ_AFFINITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IDENTITY", ZMQ_IDENTITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RATE", ZMQ_RATE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDBUF", ZMQ_SNDBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVBUF", ZMQ_RCVBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LINGER", ZMQ_LINGER);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL", ZMQ_RECONNECT_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL_MAX", ZMQ_RECONNECT_IVL_MAX);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_BACKLOG", ZMQ_BACKLOG);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MAXMSGSIZE", ZMQ_MAXMSGSIZE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SUBSCRIBE", ZMQ_SUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TYPE", ZMQ_TYPE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVMORE", ZMQ_RCVMORE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_FD", ZMQ_FD);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_EVENTS", ZMQ_EVENTS);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDTIMEO", ZMQ_SNDTIMEO);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVTIMEO", ZMQ_RCVTIMEO);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IPV4ONLY", ZMQ_IPV4ONLY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LAST_ENDPOINT", ZMQ_LAST_ENDPOINT);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE", ZMQ_TCP_KEEPALIVE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_IDLE", ZMQ_TCP_KEEPALIVE_IDLE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_CNT", ZMQ_TCP_KEEPALIVE_CNT);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_INTVL", ZMQ_TCP_KEEPALIVE_INTVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_ACCEPT_FILTER", ZMQ_TCP_ACCEPT_FILTER);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_DELAY_ATTACH_ON_CONNECT", ZMQ_DELAY_ATTACH_ON_CONNECT);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_XPUB_VERBOSE", ZMQ_XPUB_VERBOSE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ROUTER_MANDATORY", ZMQ_ROUTER_MANDATORY);
			
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
			
#endif

#if ZMQ_VERSION_MAJOR >= 4

/* {{{ proto mixed ZMQSocket::getSockOpt()
	Get a socket option
*/
PHP_METHOD(zmqsocket, getsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	size_t value_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &key) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

		
		case ZMQ_SNDHWM:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDHWM value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVHWM:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVHWM value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_AFFINITY:
		{
			uint64_t value;

			value_len = sizeof(uint64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_AFFINITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_IDENTITY:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IDENTITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
		
		case ZMQ_RATE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RATE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECOVERY_IVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDBUF:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVBUF:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVBUF value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_LINGER:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_LINGER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_BACKLOG:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_BACKLOG value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_MAXMSGSIZE:
		{
			int64_t value;

			value_len = sizeof(int64_t);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_SUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_UNSUBSCRIBE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
		
		case ZMQ_TYPE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TYPE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVMORE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVMORE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_EVENTS:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_EVENTS value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_SNDTIMEO:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_RCVTIMEO:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_IPV4ONLY:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IPV4ONLY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_LAST_ENDPOINT:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_LAST_ENDPOINT value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len - 1, 1);
		}
		break;
		
		case ZMQ_TCP_KEEPALIVE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_TCP_KEEPALIVE_IDLE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_TCP_KEEPALIVE_CNT:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_TCP_KEEPALIVE_INTVL:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_TCP_ACCEPT_FILTER:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_TCP_ACCEPT_FILTER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
		
		case ZMQ_DELAY_ATTACH_ON_CONNECT:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_DELAY_ATTACH_ON_CONNECT value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_XPUB_VERBOSE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_XPUB_VERBOSE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_ROUTER_MANDATORY:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_ROUTER_MANDATORY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_ROUTER_RAW:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_ROUTER_RAW value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_IPV6:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IPV6 value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_PLAIN_SERVER:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_PLAIN_SERVER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_PLAIN_USERNAME:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_PLAIN_USERNAME value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
	
		case ZMQ_PLAIN_PASSWORD:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_PLAIN_PASSWORD value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
		
		case ZMQ_CURVE_SERVER:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_CURVE_SERVER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_CURVE_PUBLICKEY:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_CURVE_PUBLICKEY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
	
		case ZMQ_CURVE_SECRETKEY:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_CURVE_SECRETKEY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
	
		case ZMQ_CURVE_SERVERKEY:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_CURVE_SERVERKEY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
		
		case ZMQ_PROBE_ROUTER:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_PROBE_ROUTER value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_REQ_CORRELATE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_REQ_CORRELATE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_REQ_RELAXED:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_REQ_RELAXED value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
		
		case ZMQ_CONFLATE:
		{
			int value;

			value_len = sizeof(int);
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_CONFLATE value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;
	
		case ZMQ_ZAP_DOMAIN:
		{
			char value[255];

			value_len = 255;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_ZAP_DOMAIN value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL(value, value_len, 1);
		}
		break;
	

		case ZMQ_FD:
		{
			php_stream *stm = php_zmq_create_zmq_fd(getThis() TSRMLS_CC);
			if (stm) {
				php_stream_to_zval(stm, return_value);
				return;
			}
			RETURN_FALSE;
		}
		break;

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
	}
}

	

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
	Set a socket option
*/
PHP_METHOD(zmqsocket, setsockopt)
{
	php_zmq_socket_object *intern;
	long key;
	zval *pz_value;
	int status;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz/", &key, &pz_value) == FAILURE) {
		return;
	}

	intern = PHP_ZMQ_SOCKET_OBJECT;

	if (!intern->socket) {
		zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket has not been initialized yet", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
		return;
	}

	switch (key) {

	

		case ZMQ_SNDHWM:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDHWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVHWM:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVHWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_AFFINITY:
		{
			uint64_t value;
			convert_to_long(pz_value);
			
			value  = (uint64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_AFFINITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_IDENTITY:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_IDENTITY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RATE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RATE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECOVERY_IVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SNDBUF:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVBUF:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVBUF option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_LINGER:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_LINGER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RECONNECT_IVL_MAX:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_BACKLOG:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_BACKLOG option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_MAXMSGSIZE:
		{
			int64_t value;
			convert_to_long(pz_value);
			
			value  = (int64_t) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_SUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_UNSUBSCRIBE:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		case ZMQ_TYPE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	
		case ZMQ_RCVMORE:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	

		case ZMQ_SNDTIMEO:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_RCVTIMEO:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_IPV4ONLY:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_IPV4ONLY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		case ZMQ_LAST_ENDPOINT:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_LAST_ENDPOINT is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	

		case ZMQ_TCP_KEEPALIVE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_TCP_KEEPALIVE_IDLE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_TCP_KEEPALIVE_CNT:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_TCP_KEEPALIVE_INTVL:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_TCP_ACCEPT_FILTER:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_TCP_ACCEPT_FILTER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_DELAY_ATTACH_ON_CONNECT:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_DELAY_ATTACH_ON_CONNECT option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_XPUB_VERBOSE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_XPUB_VERBOSE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_ROUTER_MANDATORY:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_ROUTER_MANDATORY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_ROUTER_RAW:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_ROUTER_RAW option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_IPV6:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_IPV6 option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_PLAIN_SERVER:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_PLAIN_SERVER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_PLAIN_USERNAME:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_PLAIN_USERNAME option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_PLAIN_PASSWORD:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_PLAIN_PASSWORD option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_CURVE_SERVER:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_CURVE_SERVER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_CURVE_PUBLICKEY:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_CURVE_PUBLICKEY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_CURVE_SECRETKEY:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_CURVE_SECRETKEY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_CURVE_SERVERKEY:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_CURVE_SERVERKEY option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_PROBE_ROUTER:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_PROBE_ROUTER option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_REQ_CORRELATE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_REQ_CORRELATE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_REQ_RELAXED:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_REQ_RELAXED option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_CONFLATE:
		{
			int value;
			convert_to_long(pz_value);
			
			value  = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int));
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_CONFLATE option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	

		case ZMQ_ZAP_DOMAIN:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));

			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_ZAP_DOMAIN option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;

	
		
		case ZMQ_HWM:
		{
			int value;
			convert_to_long(pz_value);

			if (Z_LVAL_P(pz_value) < 0) {
				zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The option value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
				return;
			}
			value = (int) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof(int));

			if (status == 0) {
				status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
			}
			
			if (status != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket ZMQ::SOCKOPT_HWM option: %s", zmq_strerror(errno));
				return;
			}
		}
		break;
	

		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	}
	ZMQ_RETURN_THIS;
}

	

void php_zmq_register_sockopt_constants (zend_class_entry *php_zmq_sc_entry TSRMLS_DC)
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) \
	zend_declare_class_constant_long(php_zmq_sc_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HWM", ZMQ_HWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDHWM", ZMQ_SNDHWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVHWM", ZMQ_RCVHWM);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_AFFINITY", ZMQ_AFFINITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IDENTITY", ZMQ_IDENTITY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RATE", ZMQ_RATE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDBUF", ZMQ_SNDBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVBUF", ZMQ_RCVBUF);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LINGER", ZMQ_LINGER);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL", ZMQ_RECONNECT_IVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL_MAX", ZMQ_RECONNECT_IVL_MAX);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_BACKLOG", ZMQ_BACKLOG);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MAXMSGSIZE", ZMQ_MAXMSGSIZE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SUBSCRIBE", ZMQ_SUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TYPE", ZMQ_TYPE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVMORE", ZMQ_RCVMORE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_FD", ZMQ_FD);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_EVENTS", ZMQ_EVENTS);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDTIMEO", ZMQ_SNDTIMEO);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVTIMEO", ZMQ_RCVTIMEO);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IPV4ONLY", ZMQ_IPV4ONLY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LAST_ENDPOINT", ZMQ_LAST_ENDPOINT);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE", ZMQ_TCP_KEEPALIVE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_IDLE", ZMQ_TCP_KEEPALIVE_IDLE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_CNT", ZMQ_TCP_KEEPALIVE_CNT);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_INTVL", ZMQ_TCP_KEEPALIVE_INTVL);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_ACCEPT_FILTER", ZMQ_TCP_ACCEPT_FILTER);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_DELAY_ATTACH_ON_CONNECT", ZMQ_DELAY_ATTACH_ON_CONNECT);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_XPUB_VERBOSE", ZMQ_XPUB_VERBOSE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ROUTER_MANDATORY", ZMQ_ROUTER_MANDATORY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ROUTER_RAW", ZMQ_ROUTER_RAW);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IPV6", ZMQ_IPV6);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_PLAIN_SERVER", ZMQ_PLAIN_SERVER);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_PLAIN_USERNAME", ZMQ_PLAIN_USERNAME);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_PLAIN_PASSWORD", ZMQ_PLAIN_PASSWORD);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_CURVE_SERVER", ZMQ_CURVE_SERVER);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_CURVE_PUBLICKEY", ZMQ_CURVE_PUBLICKEY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_CURVE_SECRETKEY", ZMQ_CURVE_SECRETKEY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_CURVE_SERVERKEY", ZMQ_CURVE_SERVERKEY);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_PROBE_ROUTER", ZMQ_PROBE_ROUTER);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_REQ_CORRELATE", ZMQ_REQ_CORRELATE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_REQ_RELAXED", ZMQ_REQ_RELAXED);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_CONFLATE", ZMQ_CONFLATE);
			
	PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ZAP_DOMAIN", ZMQ_ZAP_DOMAIN);
			
#undef PHP_ZMQ_REGISTER_SOCKOPT
}
			
#endif
