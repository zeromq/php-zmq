<?php

echo <<<EOL
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

EOL;

$xml = simplexml_load_file ('sockopts.xml');

echo '#include "php_zmq.h"' . PHP_EOL;
echo '#include "php_zmq_private.h"' . PHP_EOL;

foreach ($xml->version as $node)
{
    printf ('#if ZMQ_VERSION_MAJOR == %d' . PHP_EOL . PHP_EOL, $node ['major']);
    
    echo <<<EOL
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

EOL;
    
	$ignored = array ();
    
    foreach ($node->option as $option)
    {
		$raw_name = strtoupper ($option ['name']);
		$name = 'ZMQ_' . $raw_name;
		$type = (string) $option ['type'];
		
		if ($name === 'ZMQ_FD' || $name === 'ZMQ_IDENTITY')
		{
			$ignored [] = $name;
			continue;
		}
		
		if ((string) $option ['mode'] === 'rw' || (string) $option ['mode'] === 'r' ):


			echo <<<EOL

		case ${name}:
		{
			${type} value;

			value_len = sizeof(${type});
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option value: %s", zmq_strerror(errno));
				return;
			}
			RETURN_LONG(value);
		}
		break;

EOL;

		else:

			echo <<<EOL

		case ${name}:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Retrieving SOCKOPT_{$raw_name} is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;

EOL;
		endif;
	}	

echo <<<EOL
	
		case ZMQ_IDENTITY:
		{
			unsigned char value[PHP_ZMQ_IDENTITY_LEN];

			value_len = PHP_ZMQ_IDENTITY_LEN;
			if (zmq_getsockopt(intern->socket->z_socket, (int) key, value, &value_len) != 0) {
				zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to get the option value: %s", zmq_strerror(errno));
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
		break;
	}
}
#endif

EOL;

}

// set sock opt

foreach ($xml->version as $node)
{
    printf ('#if ZMQ_VERSION_MAJOR == %d' . PHP_EOL . PHP_EOL, $node ['major']);
    
    echo <<<EOL
/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer \$SOCKOPT, mixed \$value)
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

EOL;
    
	$ignored = array ();
    
    foreach ($node->option as $option)
    {
		$raw_name = strtoupper ($option ['name']);
		$name = 'ZMQ_' . $raw_name;
		$type = (string) $option ['type'];
		
		if ($name === 'ZMQ_FD')
		{
			$ignored [] = $name;
			continue;
		}
		
		if ((string) $option ['mode'] === 'rw' || (string) $option ['mode'] === 'w'):

			if ($type !== 'blob'):

			echo <<<EOL

		case ${name}:
		{
			${type} value;
			convert_to_long(pz_value);

EOL;
			if ($type == 'uint64_t'):
echo <<<EOL
			if (Z_LVAL_P(pz_value) < 0) {
				zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The option value must be zero or larger", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
				return;
			}
EOL;
			endif;
echo <<<EOL
			
			value  = (${type}) Z_LVAL_P(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(${type}));
		}
		break;

EOL;

			else:
			
			echo <<<EOL

		case ${name}:
		{
			convert_to_string(pz_value);
			status = zmq_setsockopt(intern->socket->z_socket, key, Z_STRVAL_P(pz_value), Z_STRLEN_P(pz_value));
		}
		break;

EOL;
			
			
			endif;


		else:

			echo <<<EOL

		case ${name}:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting SOCKOPT_{$raw_name} is not supported", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;

EOL;
		endif;
	}
	
	if ((int) $node ['major'] === 3)
	{
echo <<<EOL

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
			
			if (status == 0)
			{
				status = zmq_setsockopt(intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof(int));
			}
		}
		break;

EOL;
	}

echo <<<EOL
	
		default:
		{
			zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Unknown option key", PHP_ZMQ_INTERNAL_ERROR TSRMLS_CC);
			return;
		}
		break;
	}
	
	if (status != 0) {
		zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno TSRMLS_CC, "Failed to set socket option: %s", zmq_strerror(errno));
		return;
	}
	ZMQ_RETURN_THIS;
	
}
#endif

EOL;

}






