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

static
inline php_zmq_context_object *php_zmq_context_fetch_object(zend_object *obj) {
	return (php_zmq_context_object *)((char *)obj - XtOffsetOf(php_zmq_context_object, zo));
}

static
inline php_zmq_socket_object *php_zmq_socket_fetch_object(zend_object *obj) {
	return (php_zmq_socket_object *)((char *)obj - XtOffsetOf(php_zmq_socket_object, zo));
}

static
inline php_zmq_poll_object *php_zmq_poll_fetch_object(zend_object *obj) {
	return (php_zmq_poll_object *)((char *)obj - XtOffsetOf(php_zmq_poll_object, zo));
}

static
inline php_zmq_device_object *php_zmq_device_fetch_object(zend_object *obj) {
	return (php_zmq_device_object *)((char *)obj - XtOffsetOf(php_zmq_device_object, zo));
}

#define PHP_ZMQ_CONTEXT_OBJECT php_zmq_context_fetch_object(Z_OBJ_P(getThis()));
#define PHP_ZMQ_SOCKET_OBJECT  php_zmq_socket_fetch_object(Z_OBJ_P(getThis()));
#define PHP_ZMQ_POLL_OBJECT    php_zmq_poll_fetch_object(Z_OBJ_P(getThis()));
#define PHP_ZMQ_DEVICE_OBJECT  php_zmq_device_fetch_object(Z_OBJ_P(getThis()));

#ifdef HAVE_CZMQ_2

static
inline php_zmq_cert_object *php_zmq_cert_fetch_object(zend_object *obj) {
	return (php_zmq_cert_object *)((char *)obj - XtOffsetOf(php_zmq_cert_object, zo));
}

static
inline php_zmq_auth_object *php_zmq_auth_fetch_object(zend_object *obj) {
	return (php_zmq_auth_object *)((char *)obj - XtOffsetOf(php_zmq_auth_object, zo));
}

#define PHP_ZMQ_CERT_OBJECT php_zmq_cert_fetch_object(Z_OBJ_P(getThis()));
#define PHP_ZMQ_AUTH_OBJECT php_zmq_auth_fetch_object(Z_OBJ_P(getThis()));

#endif