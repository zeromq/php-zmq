
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
	
#if ZMQ_VERSION_MAJOR == 2

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
	

		case ZMQ_IDENTITY:
		{
			unsigned char value[PHP_ZMQ_IDENTITY_LEN];

			value_len = PHP_ZMQ_IDENTITY_LEN;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IDENTITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL((char *) value, value_len, 1);
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

	

#endif
		
#if ZMQ_VERSION_MAJOR == 3

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
	

		case ZMQ_IDENTITY:
		{
			unsigned char value[PHP_ZMQ_IDENTITY_LEN];

			value_len = PHP_ZMQ_IDENTITY_LEN;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option ZMQ::SOCKOPT_IDENTITY value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_STRINGL((char *) value, value_len, 1);
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

	

#endif
		