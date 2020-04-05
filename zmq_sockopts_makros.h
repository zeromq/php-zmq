/*
+-----------------------------------------------------------------------------------+
|  ZMQ extension for PHP                                                            |
|  Copyright (c) 2010-2020, Mikko Koppanen <mkoppanen@php.net>                      |
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

#define SOCKOPTS_GET_INT(NAME, TYPE) \
{ \
  TYPE value; \
  value_len = sizeof(TYPE); \
  if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) { \
    zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, \
            "Failed to get the option ZMQ::SOCKOPT_" #NAME" value: %s", zmq_strerror(errno)); \
    return; \
  } \
  RETURN_LONG(value); \
}

#define SOCKOPTS_GET_STRING(NAME, LEN, BINARY) \
{ \
  char value[LEN]; \
  value_len = LEN; \
  if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) { \
    zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, \
            "Failed to get the option ZMQ::SOCKOPT_" #NAME " value: %s", zmq_strerror(errno)); \
    return; \
  } \
  if(BINARY == 1){ \
    RETURN_STRINGL(value, value_len); \
  } \
  else { \
    RETURN_STRINGL(value, value_len - 1); \
  } \
}

#define SOCKOPTS_SET_INT(NAME, TYPE) \
{ \
  TYPE value = (TYPE) zval_get_long(zv); \
  if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(TYPE)) != 0) { \
    zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, \
            "Failed to set socket ZMQ::" #NAME " option: %s", zmq_strerror(errno)); \
  } \
  return; \
}

#define SOCKOPTS_SET_STRING(NAME) \
{ \
  int rc; \
  zend_string *str = zval_get_string(zv); \
  rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len); \
  zend_string_release(str); \
  if (rc != 0) { \
    zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, \
            "Failed to set socket ZMQ::SOCKOPT_" #NAME " option: %s", zmq_strerror(errno)); \
  } \
  return; \
}
