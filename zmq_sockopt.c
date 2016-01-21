

/*
+-----------------------------------------------------------------------------------+
|  ZMQ extension for PHP                                                            |
|  Copyright (c) 2010-2016, Mikko Koppanen <mkoppanen@php.net>                      |
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

/*
    WARNING! WARNING!

    This file is generated code. See README for editing
*/

#include "php_zmq.h"
#include "php_zmq_private.h"
#include "zmq_object_access.c"



/*
    sockopts_register.gsl
*/
void php_zmq_register_sockopt_constants (zend_class_entry *php_zmq_sc_entry)
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) zend_declare_class_constant_long(php_zmq_sc_entry, const_name, sizeof(const_name) - 1, value);

#if ZMQ_VERSION_MAJOR == 4
# ifdef ZMQ_HEARTBEAT_IVL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HEARTBEAT_IVL", ZMQ_HEARTBEAT_IVL);
# endif
# ifdef ZMQ_HEARTBEAT_TTL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HEARTBEAT_TTL", ZMQ_HEARTBEAT_TTL);
# endif
# ifdef ZMQ_HEARTBEAT_TIMEOUT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HEARTBEAT_TIMEOUT", ZMQ_HEARTBEAT_TIMEOUT);
# endif
# ifdef ZMQ_TOS
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TOS", ZMQ_TOS);
# endif
# ifdef ZMQ_ROUTER_HANDOVER
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ROUTER_HANDOVER", ZMQ_ROUTER_HANDOVER);
# endif
# ifdef ZMQ_ROUTER_MANDATORY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ROUTER_MANDATORY", ZMQ_ROUTER_MANDATORY);
# endif
# ifdef ZMQ_PROBE_ROUTER
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_PROBE_ROUTER", ZMQ_PROBE_ROUTER);
# endif
# ifdef ZMQ_REQ_RELAXED
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_REQ_RELAXED", ZMQ_REQ_RELAXED);
# endif
# ifdef ZMQ_REQ_CORRELATE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_REQ_CORRELATE", ZMQ_REQ_CORRELATE);
# endif
# ifdef ZMQ_CONFLATE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_CONFLATE", ZMQ_CONFLATE);
# endif
# ifdef ZMQ_ZAP_DOMAIN
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ZAP_DOMAIN", ZMQ_ZAP_DOMAIN);
# endif
# ifdef ZMQ_MECHANISM
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MECHANISM", ZMQ_MECHANISM);
# endif
# ifdef ZMQ_PLAIN_SERVER
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_PLAIN_SERVER", ZMQ_PLAIN_SERVER);
# endif
# ifdef ZMQ_PLAIN_USERNAME
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_PLAIN_USERNAME", ZMQ_PLAIN_USERNAME);
# endif
# ifdef ZMQ_PLAIN_PASSWORD
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_PLAIN_PASSWORD", ZMQ_PLAIN_PASSWORD);
# endif
# ifdef ZMQ_CURVE_SERVER
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_CURVE_SERVER", ZMQ_CURVE_SERVER);
# endif
# ifdef ZMQ_CURVE_PUBLICKEY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_CURVE_PUBLICKEY", ZMQ_CURVE_PUBLICKEY);
# endif
# ifdef ZMQ_CURVE_SECRETKEY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_CURVE_SECRETKEY", ZMQ_CURVE_SECRETKEY);
# endif
# ifdef ZMQ_CURVE_SERVERKEY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_CURVE_SERVERKEY", ZMQ_CURVE_SERVERKEY);
# endif
# ifdef ZMQ_GSSAPI_SERVER
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_GSSAPI_SERVER", ZMQ_GSSAPI_SERVER);
# endif
# ifdef ZMQ_GSSAPI_PLAINTEXT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_GSSAPI_PLAINTEXT", ZMQ_GSSAPI_PLAINTEXT);
# endif
# ifdef ZMQ_GSSAPI_PRINCIPAL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_GSSAPI_PRINCIPAL", ZMQ_GSSAPI_PRINCIPAL);
# endif
# ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_GSSAPI_SERVICE_PRINCIPAL", ZMQ_GSSAPI_SERVICE_PRINCIPAL);
# endif
# ifdef ZMQ_IPV6
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IPV6", ZMQ_IPV6);
# endif
# ifdef ZMQ_IMMEDIATE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IMMEDIATE", ZMQ_IMMEDIATE);
# endif
# ifdef ZMQ_ROUTER_RAW
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ROUTER_RAW", ZMQ_ROUTER_RAW);
# endif
# ifdef ZMQ_IPV4ONLY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IPV4ONLY", ZMQ_IPV4ONLY);
# endif
# ifdef ZMQ_DELAY_ATTACH_ON_CONNECT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_DELAY_ATTACH_ON_CONNECT", ZMQ_DELAY_ATTACH_ON_CONNECT);
# endif
# ifdef ZMQ_TYPE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TYPE", ZMQ_TYPE);
# endif
# ifdef ZMQ_SNDHWM
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDHWM", ZMQ_SNDHWM);
# endif
# ifdef ZMQ_RCVHWM
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVHWM", ZMQ_RCVHWM);
# endif
# ifdef ZMQ_AFFINITY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_AFFINITY", ZMQ_AFFINITY);
# endif
# ifdef ZMQ_SUBSCRIBE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SUBSCRIBE", ZMQ_SUBSCRIBE);
# endif
# ifdef ZMQ_UNSUBSCRIBE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
# endif
# ifdef ZMQ_IDENTITY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IDENTITY", ZMQ_IDENTITY);
# endif
# ifdef ZMQ_RATE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RATE", ZMQ_RATE);
# endif
# ifdef ZMQ_RECOVERY_IVL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
# endif
# ifdef ZMQ_SNDBUF
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDBUF", ZMQ_SNDBUF);
# endif
# ifdef ZMQ_RCVBUF
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVBUF", ZMQ_RCVBUF);
# endif
# ifdef ZMQ_LINGER
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LINGER", ZMQ_LINGER);
# endif
# ifdef ZMQ_RECONNECT_IVL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL", ZMQ_RECONNECT_IVL);
# endif
# ifdef ZMQ_RECONNECT_IVL_MAX
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL_MAX", ZMQ_RECONNECT_IVL_MAX);
# endif
# ifdef ZMQ_BACKLOG
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_BACKLOG", ZMQ_BACKLOG);
# endif
# ifdef ZMQ_MAXMSGSIZE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MAXMSGSIZE", ZMQ_MAXMSGSIZE);
# endif
# ifdef ZMQ_MULTICAST_HOPS
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MULTICAST_HOPS", ZMQ_MULTICAST_HOPS);
# endif
# ifdef ZMQ_RCVTIMEO
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVTIMEO", ZMQ_RCVTIMEO);
# endif
# ifdef ZMQ_SNDTIMEO
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDTIMEO", ZMQ_SNDTIMEO);
# endif
# ifdef ZMQ_XPUB_VERBOSE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_XPUB_VERBOSE", ZMQ_XPUB_VERBOSE);
# endif
# ifdef ZMQ_TCP_KEEPALIVE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE", ZMQ_TCP_KEEPALIVE);
# endif
# ifdef ZMQ_TCP_KEEPALIVE_IDLE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_IDLE", ZMQ_TCP_KEEPALIVE_IDLE);
# endif
# ifdef ZMQ_TCP_KEEPALIVE_CNT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_CNT", ZMQ_TCP_KEEPALIVE_CNT);
# endif
# ifdef ZMQ_TCP_KEEPALIVE_INTVL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_INTVL", ZMQ_TCP_KEEPALIVE_INTVL);
# endif
# ifdef ZMQ_TCP_ACCEPT_FILTER
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_ACCEPT_FILTER", ZMQ_TCP_ACCEPT_FILTER);
# endif
# ifdef ZMQ_RCVMORE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVMORE", ZMQ_RCVMORE);
# endif
# ifdef ZMQ_FD
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_FD", ZMQ_FD);
# endif
# ifdef ZMQ_EVENTS
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_EVENTS", ZMQ_EVENTS);
# endif
# ifdef ZMQ_LAST_ENDPOINT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LAST_ENDPOINT", ZMQ_LAST_ENDPOINT);
# endif
#endif /* ZMQ_MAJOR_VERSION == 4 */
#if ZMQ_VERSION_MAJOR == 3
# ifdef ZMQ_ROUTER_RAW
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ROUTER_RAW", ZMQ_ROUTER_RAW);
# endif
# ifdef ZMQ_IPV4ONLY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IPV4ONLY", ZMQ_IPV4ONLY);
# endif
# ifdef ZMQ_DELAY_ATTACH_ON_CONNECT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_DELAY_ATTACH_ON_CONNECT", ZMQ_DELAY_ATTACH_ON_CONNECT);
# endif
# ifdef ZMQ_TYPE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TYPE", ZMQ_TYPE);
# endif
# ifdef ZMQ_SNDHWM
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDHWM", ZMQ_SNDHWM);
# endif
# ifdef ZMQ_RCVHWM
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVHWM", ZMQ_RCVHWM);
# endif
# ifdef ZMQ_AFFINITY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_AFFINITY", ZMQ_AFFINITY);
# endif
# ifdef ZMQ_SUBSCRIBE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SUBSCRIBE", ZMQ_SUBSCRIBE);
# endif
# ifdef ZMQ_UNSUBSCRIBE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
# endif
# ifdef ZMQ_IDENTITY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IDENTITY", ZMQ_IDENTITY);
# endif
# ifdef ZMQ_RATE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RATE", ZMQ_RATE);
# endif
# ifdef ZMQ_RECOVERY_IVL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
# endif
# ifdef ZMQ_SNDBUF
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDBUF", ZMQ_SNDBUF);
# endif
# ifdef ZMQ_RCVBUF
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVBUF", ZMQ_RCVBUF);
# endif
# ifdef ZMQ_LINGER
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LINGER", ZMQ_LINGER);
# endif
# ifdef ZMQ_RECONNECT_IVL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL", ZMQ_RECONNECT_IVL);
# endif
# ifdef ZMQ_RECONNECT_IVL_MAX
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL_MAX", ZMQ_RECONNECT_IVL_MAX);
# endif
# ifdef ZMQ_BACKLOG
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_BACKLOG", ZMQ_BACKLOG);
# endif
# ifdef ZMQ_MAXMSGSIZE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MAXMSGSIZE", ZMQ_MAXMSGSIZE);
# endif
# ifdef ZMQ_MULTICAST_HOPS
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MULTICAST_HOPS", ZMQ_MULTICAST_HOPS);
# endif
# ifdef ZMQ_RCVTIMEO
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVTIMEO", ZMQ_RCVTIMEO);
# endif
# ifdef ZMQ_SNDTIMEO
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDTIMEO", ZMQ_SNDTIMEO);
# endif
# ifdef ZMQ_XPUB_VERBOSE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_XPUB_VERBOSE", ZMQ_XPUB_VERBOSE);
# endif
# ifdef ZMQ_TCP_KEEPALIVE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE", ZMQ_TCP_KEEPALIVE);
# endif
# ifdef ZMQ_TCP_KEEPALIVE_IDLE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_IDLE", ZMQ_TCP_KEEPALIVE_IDLE);
# endif
# ifdef ZMQ_TCP_KEEPALIVE_CNT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_CNT", ZMQ_TCP_KEEPALIVE_CNT);
# endif
# ifdef ZMQ_TCP_KEEPALIVE_INTVL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_KEEPALIVE_INTVL", ZMQ_TCP_KEEPALIVE_INTVL);
# endif
# ifdef ZMQ_TCP_ACCEPT_FILTER
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_ACCEPT_FILTER", ZMQ_TCP_ACCEPT_FILTER);
# endif
# ifdef ZMQ_RCVMORE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVMORE", ZMQ_RCVMORE);
# endif
# ifdef ZMQ_FD
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_FD", ZMQ_FD);
# endif
# ifdef ZMQ_EVENTS
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_EVENTS", ZMQ_EVENTS);
# endif
# ifdef ZMQ_LAST_ENDPOINT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LAST_ENDPOINT", ZMQ_LAST_ENDPOINT);
# endif
#endif /* ZMQ_MAJOR_VERSION == 3 */
#if ZMQ_VERSION_MAJOR == 2
# ifdef ZMQ_HWM
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HWM", ZMQ_HWM);
# endif
# ifdef ZMQ_SWAP
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SWAP", ZMQ_SWAP);
# endif
# ifdef ZMQ_AFFINITY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_AFFINITY", ZMQ_AFFINITY);
# endif
# ifdef ZMQ_IDENTITY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IDENTITY", ZMQ_IDENTITY);
# endif
# ifdef ZMQ_RATE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RATE", ZMQ_RATE);
# endif
# ifdef ZMQ_RECOVERY_IVL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL", ZMQ_RECOVERY_IVL);
# endif
# ifdef ZMQ_RECOVERY_IVL_MSEC
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECOVERY_IVL_MSEC", ZMQ_RECOVERY_IVL_MSEC);
# endif
# ifdef ZMQ_MCAST_LOOP
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MCAST_LOOP", ZMQ_MCAST_LOOP);
# endif
# ifdef ZMQ_RCVTIMEO
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVTIMEO", ZMQ_RCVTIMEO);
# endif
# ifdef ZMQ_SNDTIMEO
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDTIMEO", ZMQ_SNDTIMEO);
# endif
# ifdef ZMQ_SNDBUF
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDBUF", ZMQ_SNDBUF);
# endif
# ifdef ZMQ_RCVBUF
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVBUF", ZMQ_RCVBUF);
# endif
# ifdef ZMQ_LINGER
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LINGER", ZMQ_LINGER);
# endif
# ifdef ZMQ_RECONNECT_IVL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL", ZMQ_RECONNECT_IVL);
# endif
# ifdef ZMQ_RECONNECT_IVL_MAX
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RECONNECT_IVL_MAX", ZMQ_RECONNECT_IVL_MAX);
# endif
# ifdef ZMQ_BACKLOG
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_BACKLOG", ZMQ_BACKLOG);
# endif
# ifdef ZMQ_SUBSCRIBE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SUBSCRIBE", ZMQ_SUBSCRIBE);
# endif
# ifdef ZMQ_UNSUBSCRIBE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_UNSUBSCRIBE", ZMQ_UNSUBSCRIBE);
# endif
# ifdef ZMQ_TYPE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TYPE", ZMQ_TYPE);
# endif
# ifdef ZMQ_RCVMORE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVMORE", ZMQ_RCVMORE);
# endif
# ifdef ZMQ_FD
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_FD", ZMQ_FD);
# endif
# ifdef ZMQ_EVENTS
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_EVENTS", ZMQ_EVENTS);
# endif
#endif /* ZMQ_MAJOR_VERSION == 2 */

#if ZMQ_VERSION_MAJOR > 2
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HWM", ZMQ_HWM);
#endif

#undef PHP_ZMQ_REGISTER_SOCKOPT
}

/* {{{ proto mixed ZMQSocket::getSockOpt()
    Get a socket option
*/
PHP_METHOD(zmqsocket, getsockopt)
{
    php_zmq_socket_object *intern;
    zend_long key;
    size_t value_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &key) == FAILURE) {
        return;
    }

    intern = PHP_ZMQ_SOCKET_OBJECT;

    if (!intern->socket || !intern->socket->z_socket) {
        zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket is not properly initialised", PHP_ZMQ_INTERNAL_ERROR);
        return;
    }

    if (key > INT_MAX) {
        zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), PHP_ZMQ_INTERNAL_ERROR, "The key must be smaller than or equal to %d", INT_MAX);
        return;
    }

#if ZMQ_VERSION_MAJOR == 4

    switch (key) {
# ifdef ZMQ_HEARTBEAT_IVL

        case ZMQ_HEARTBEAT_IVL:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_HEARTBEAT_IVL value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_HEARTBEAT_IVL */
# ifdef ZMQ_HEARTBEAT_TTL

        case ZMQ_HEARTBEAT_TTL:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_HEARTBEAT_TTL value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_HEARTBEAT_TTL */
# ifdef ZMQ_HEARTBEAT_TIMEOUT

        case ZMQ_HEARTBEAT_TIMEOUT:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_HEARTBEAT_TIMEOUT value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_HEARTBEAT_TIMEOUT */
# ifdef ZMQ_TOS

        case ZMQ_TOS:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_TOS value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_TOS */
# ifdef ZMQ_ROUTER_HANDOVER

        case ZMQ_ROUTER_HANDOVER:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_ROUTER_HANDOVER is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_ROUTER_HANDOVER */
# ifdef ZMQ_ROUTER_MANDATORY

        case ZMQ_ROUTER_MANDATORY:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_ROUTER_MANDATORY is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_ROUTER_MANDATORY */
# ifdef ZMQ_PROBE_ROUTER

        case ZMQ_PROBE_ROUTER:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_PROBE_ROUTER is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_PROBE_ROUTER */
# ifdef ZMQ_REQ_RELAXED

        case ZMQ_REQ_RELAXED:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_REQ_RELAXED is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_REQ_RELAXED */
# ifdef ZMQ_REQ_CORRELATE

        case ZMQ_REQ_CORRELATE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_REQ_CORRELATE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_REQ_CORRELATE */
# ifdef ZMQ_CONFLATE

        case ZMQ_CONFLATE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_CONFLATE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_CONFLATE */
# ifdef ZMQ_ZAP_DOMAIN

        case ZMQ_ZAP_DOMAIN:
        {
            char value[255];
            value_len = 255;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_ZAP_DOMAIN value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len - 1);
        }
        break;

# endif /* ZMQ_ZAP_DOMAIN */
# ifdef ZMQ_MECHANISM

        case ZMQ_MECHANISM:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_MECHANISM value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_MECHANISM */
# ifdef ZMQ_PLAIN_SERVER

        case ZMQ_PLAIN_SERVER:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_PLAIN_SERVER value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_PLAIN_SERVER */
# ifdef ZMQ_PLAIN_USERNAME

        case ZMQ_PLAIN_USERNAME:
        {
            char value[255];
            value_len = 255;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_PLAIN_USERNAME value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len - 1);
        }
        break;

# endif /* ZMQ_PLAIN_USERNAME */
# ifdef ZMQ_PLAIN_PASSWORD

        case ZMQ_PLAIN_PASSWORD:
        {
            char value[255];
            value_len = 255;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_PLAIN_PASSWORD value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len - 1);
        }
        break;

# endif /* ZMQ_PLAIN_PASSWORD */
# ifdef ZMQ_CURVE_SERVER

        case ZMQ_CURVE_SERVER:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_CURVE_SERVER value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_CURVE_SERVER */
# ifdef ZMQ_CURVE_PUBLICKEY

        case ZMQ_CURVE_PUBLICKEY:
        {
            char value[32];
            value_len = 32;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_CURVE_PUBLICKEY value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len);
        }
        break;

# endif /* ZMQ_CURVE_PUBLICKEY */
# ifdef ZMQ_CURVE_SECRETKEY

        case ZMQ_CURVE_SECRETKEY:
        {
            char value[32];
            value_len = 32;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_CURVE_SECRETKEY value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len);
        }
        break;

# endif /* ZMQ_CURVE_SECRETKEY */
# ifdef ZMQ_CURVE_SERVERKEY

        case ZMQ_CURVE_SERVERKEY:
        {
            char value[32];
            value_len = 32;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_CURVE_SERVERKEY value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len);
        }
        break;

# endif /* ZMQ_CURVE_SERVERKEY */
# ifdef ZMQ_GSSAPI_SERVER

        case ZMQ_GSSAPI_SERVER:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_GSSAPI_SERVER value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_GSSAPI_SERVER */
# ifdef ZMQ_GSSAPI_PLAINTEXT

        case ZMQ_GSSAPI_PLAINTEXT:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_GSSAPI_PLAINTEXT value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_GSSAPI_PLAINTEXT */
# ifdef ZMQ_GSSAPI_PRINCIPAL

        case ZMQ_GSSAPI_PRINCIPAL:
        {
            char value[255];
            value_len = 255;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_GSSAPI_PRINCIPAL value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len - 1);
        }
        break;

# endif /* ZMQ_GSSAPI_PRINCIPAL */
# ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL

        case ZMQ_GSSAPI_SERVICE_PRINCIPAL:
        {
            char value[255];
            value_len = 255;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_GSSAPI_SERVICE_PRINCIPAL value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len - 1);
        }
        break;

# endif /* ZMQ_GSSAPI_SERVICE_PRINCIPAL */
# ifdef ZMQ_IPV6

        case ZMQ_IPV6:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_IPV6 value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_IPV6 */
# ifdef ZMQ_IMMEDIATE

        case ZMQ_IMMEDIATE:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_IMMEDIATE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_IMMEDIATE */
# ifdef ZMQ_ROUTER_RAW

        case ZMQ_ROUTER_RAW:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_ROUTER_RAW is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_ROUTER_RAW */
# ifdef ZMQ_IPV4ONLY

        case ZMQ_IPV4ONLY:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_IPV4ONLY value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_IPV4ONLY */
# ifdef ZMQ_TYPE

        case ZMQ_TYPE:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_TYPE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_TYPE */
# ifdef ZMQ_SNDHWM

        case ZMQ_SNDHWM:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_SNDHWM value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_SNDHWM */
# ifdef ZMQ_RCVHWM

        case ZMQ_RCVHWM:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RCVHWM value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RCVHWM */
# ifdef ZMQ_AFFINITY

        case ZMQ_AFFINITY:
        {
            uint64_t value;
            value_len = sizeof(uint64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_AFFINITY value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_AFFINITY */
# ifdef ZMQ_SUBSCRIBE

        case ZMQ_SUBSCRIBE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_SUBSCRIBE */
# ifdef ZMQ_UNSUBSCRIBE

        case ZMQ_UNSUBSCRIBE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_UNSUBSCRIBE */
# ifdef ZMQ_IDENTITY

        case ZMQ_IDENTITY:
        {
{
        if (intern->socket->socket_type != ZMQ_REQ &&
            intern->socket->socket_type != ZMQ_REP &&
            intern->socket->socket_type != ZMQ_DEALER &&
            intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_IDENTITY is not valid for this socket type", errno);
            return;
        }
}
            char value[255];
            value_len = 255;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_IDENTITY value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len);
        }
        break;

# endif /* ZMQ_IDENTITY */
# ifdef ZMQ_RATE

        case ZMQ_RATE:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RATE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RATE */
# ifdef ZMQ_RECOVERY_IVL

        case ZMQ_RECOVERY_IVL:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RECOVERY_IVL */
# ifdef ZMQ_SNDBUF

        case ZMQ_SNDBUF:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_SNDBUF value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_SNDBUF */
# ifdef ZMQ_RCVBUF

        case ZMQ_RCVBUF:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RCVBUF value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RCVBUF */
# ifdef ZMQ_LINGER

        case ZMQ_LINGER:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_LINGER value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_LINGER */
# ifdef ZMQ_RECONNECT_IVL

        case ZMQ_RECONNECT_IVL:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RECONNECT_IVL */
# ifdef ZMQ_RECONNECT_IVL_MAX

        case ZMQ_RECONNECT_IVL_MAX:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RECONNECT_IVL_MAX */
# ifdef ZMQ_BACKLOG

        case ZMQ_BACKLOG:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_BACKLOG value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_BACKLOG */
# ifdef ZMQ_MAXMSGSIZE

        case ZMQ_MAXMSGSIZE:
        {
            int64_t value;
            value_len = sizeof(int64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_MAXMSGSIZE */
# ifdef ZMQ_MULTICAST_HOPS

        case ZMQ_MULTICAST_HOPS:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_MULTICAST_HOPS value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_MULTICAST_HOPS */
# ifdef ZMQ_RCVTIMEO

        case ZMQ_RCVTIMEO:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RCVTIMEO */
# ifdef ZMQ_SNDTIMEO

        case ZMQ_SNDTIMEO:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_SNDTIMEO */
# ifdef ZMQ_XPUB_VERBOSE

        case ZMQ_XPUB_VERBOSE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_XPUB_VERBOSE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_XPUB_VERBOSE */
# ifdef ZMQ_TCP_KEEPALIVE

        case ZMQ_TCP_KEEPALIVE:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_TCP_KEEPALIVE */
# ifdef ZMQ_TCP_KEEPALIVE_IDLE

        case ZMQ_TCP_KEEPALIVE_IDLE:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_TCP_KEEPALIVE_IDLE */
# ifdef ZMQ_TCP_KEEPALIVE_CNT

        case ZMQ_TCP_KEEPALIVE_CNT:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_TCP_KEEPALIVE_CNT */
# ifdef ZMQ_TCP_KEEPALIVE_INTVL

        case ZMQ_TCP_KEEPALIVE_INTVL:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_TCP_KEEPALIVE_INTVL */
# ifdef ZMQ_TCP_ACCEPT_FILTER

        case ZMQ_TCP_ACCEPT_FILTER:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_TCP_ACCEPT_FILTER is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_TCP_ACCEPT_FILTER */
# ifdef ZMQ_RCVMORE

        case ZMQ_RCVMORE:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RCVMORE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RCVMORE */
# ifdef ZMQ_FD

        case ZMQ_FD:
        {
            php_stream *stream = php_zmq_create_zmq_fd(getThis());
            if (stream) {
                php_stream_to_zval(stream, return_value);
                return;
            }
            RETURN_FALSE;
        }
        break;

# endif /* ZMQ_FD */
# ifdef ZMQ_EVENTS

        case ZMQ_EVENTS:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_EVENTS value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_EVENTS */
# ifdef ZMQ_LAST_ENDPOINT

        case ZMQ_LAST_ENDPOINT:
        {
            char value[255];
            value_len = 255;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_LAST_ENDPOINT value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len - 1);
        }
        break;

# endif /* ZMQ_LAST_ENDPOINT */

        default:
            zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), PHP_ZMQ_INTERNAL_ERROR, "Unknown option key %ld", key);
            return;
    }

#endif /* ZMQ_VERSION_MAJOR == 4 */
#if ZMQ_VERSION_MAJOR == 3

    switch (key) {
# ifdef ZMQ_ROUTER_RAW

        case ZMQ_ROUTER_RAW:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_ROUTER_RAW is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_ROUTER_RAW */
# ifdef ZMQ_IPV4ONLY

        case ZMQ_IPV4ONLY:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_IPV4ONLY value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_IPV4ONLY */
# ifdef ZMQ_TYPE

        case ZMQ_TYPE:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_TYPE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_TYPE */
# ifdef ZMQ_SNDHWM

        case ZMQ_SNDHWM:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_SNDHWM value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_SNDHWM */
# ifdef ZMQ_RCVHWM

        case ZMQ_RCVHWM:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RCVHWM value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RCVHWM */
# ifdef ZMQ_AFFINITY

        case ZMQ_AFFINITY:
        {
            uint64_t value;
            value_len = sizeof(uint64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_AFFINITY value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_AFFINITY */
# ifdef ZMQ_SUBSCRIBE

        case ZMQ_SUBSCRIBE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_SUBSCRIBE */
# ifdef ZMQ_UNSUBSCRIBE

        case ZMQ_UNSUBSCRIBE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_UNSUBSCRIBE */
# ifdef ZMQ_IDENTITY

        case ZMQ_IDENTITY:
        {
{
        if (intern->socket->socket_type != ZMQ_REQ &&
            intern->socket->socket_type != ZMQ_REP &&
            intern->socket->socket_type != ZMQ_DEALER &&
            intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_IDENTITY is not valid for this socket type", errno);
            return;
        }
}
            char value[255];
            value_len = 255;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_IDENTITY value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len);
        }
        break;

# endif /* ZMQ_IDENTITY */
# ifdef ZMQ_RATE

        case ZMQ_RATE:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RATE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RATE */
# ifdef ZMQ_RECOVERY_IVL

        case ZMQ_RECOVERY_IVL:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RECOVERY_IVL */
# ifdef ZMQ_SNDBUF

        case ZMQ_SNDBUF:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_SNDBUF value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_SNDBUF */
# ifdef ZMQ_RCVBUF

        case ZMQ_RCVBUF:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RCVBUF value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RCVBUF */
# ifdef ZMQ_LINGER

        case ZMQ_LINGER:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_LINGER value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_LINGER */
# ifdef ZMQ_RECONNECT_IVL

        case ZMQ_RECONNECT_IVL:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RECONNECT_IVL */
# ifdef ZMQ_RECONNECT_IVL_MAX

        case ZMQ_RECONNECT_IVL_MAX:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RECONNECT_IVL_MAX */
# ifdef ZMQ_BACKLOG

        case ZMQ_BACKLOG:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_BACKLOG value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_BACKLOG */
# ifdef ZMQ_MAXMSGSIZE

        case ZMQ_MAXMSGSIZE:
        {
            int64_t value;
            value_len = sizeof(int64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_MAXMSGSIZE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_MAXMSGSIZE */
# ifdef ZMQ_MULTICAST_HOPS

        case ZMQ_MULTICAST_HOPS:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_MULTICAST_HOPS value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_MULTICAST_HOPS */
# ifdef ZMQ_RCVTIMEO

        case ZMQ_RCVTIMEO:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RCVTIMEO */
# ifdef ZMQ_SNDTIMEO

        case ZMQ_SNDTIMEO:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_SNDTIMEO */
# ifdef ZMQ_XPUB_VERBOSE

        case ZMQ_XPUB_VERBOSE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_XPUB_VERBOSE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_XPUB_VERBOSE */
# ifdef ZMQ_TCP_KEEPALIVE

        case ZMQ_TCP_KEEPALIVE:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_TCP_KEEPALIVE */
# ifdef ZMQ_TCP_KEEPALIVE_IDLE

        case ZMQ_TCP_KEEPALIVE_IDLE:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_TCP_KEEPALIVE_IDLE */
# ifdef ZMQ_TCP_KEEPALIVE_CNT

        case ZMQ_TCP_KEEPALIVE_CNT:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_TCP_KEEPALIVE_CNT */
# ifdef ZMQ_TCP_KEEPALIVE_INTVL

        case ZMQ_TCP_KEEPALIVE_INTVL:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_TCP_KEEPALIVE_INTVL */
# ifdef ZMQ_TCP_ACCEPT_FILTER

        case ZMQ_TCP_ACCEPT_FILTER:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_TCP_ACCEPT_FILTER is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_TCP_ACCEPT_FILTER */
# ifdef ZMQ_RCVMORE

        case ZMQ_RCVMORE:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RCVMORE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RCVMORE */
# ifdef ZMQ_FD

        case ZMQ_FD:
        {
            php_stream *stream = php_zmq_create_zmq_fd(getThis());
            if (stream) {
                php_stream_to_zval(stream, return_value);
                return;
            }
            RETURN_FALSE;
        }
        break;

# endif /* ZMQ_FD */
# ifdef ZMQ_EVENTS

        case ZMQ_EVENTS:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_EVENTS value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_EVENTS */
# ifdef ZMQ_LAST_ENDPOINT

        case ZMQ_LAST_ENDPOINT:
        {
            char value[255];
            value_len = 255;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_LAST_ENDPOINT value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len - 1);
        }
        break;

# endif /* ZMQ_LAST_ENDPOINT */

        default:
            zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), PHP_ZMQ_INTERNAL_ERROR, "Unknown option key %ld", key);
            return;
    }

#endif /* ZMQ_VERSION_MAJOR == 3 */
#if ZMQ_VERSION_MAJOR == 2

    switch (key) {
# ifdef ZMQ_HWM

        case ZMQ_HWM:
        {
            uint64_t value;
            value_len = sizeof(uint64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_HWM value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_HWM */
# ifdef ZMQ_SWAP

        case ZMQ_SWAP:
        {
            int64_t value;
            value_len = sizeof(int64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_SWAP value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_SWAP */
# ifdef ZMQ_AFFINITY

        case ZMQ_AFFINITY:
        {
            uint64_t value;
            value_len = sizeof(uint64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_AFFINITY value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_AFFINITY */
# ifdef ZMQ_IDENTITY

        case ZMQ_IDENTITY:
        {
            char value[255];
            value_len = 255;

            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_IDENTITY value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_STRINGL(value, value_len);
        }
        break;

# endif /* ZMQ_IDENTITY */
# ifdef ZMQ_RATE

        case ZMQ_RATE:
        {
            int64_t value;
            value_len = sizeof(int64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RATE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RATE */
# ifdef ZMQ_RECOVERY_IVL

        case ZMQ_RECOVERY_IVL:
        {
            int64_t value;
            value_len = sizeof(int64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RECOVERY_IVL */
# ifdef ZMQ_RECOVERY_IVL_MSEC

        case ZMQ_RECOVERY_IVL_MSEC:
        {
            int64_t value;
            value_len = sizeof(int64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RECOVERY_IVL_MSEC value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RECOVERY_IVL_MSEC */
# ifdef ZMQ_MCAST_LOOP

        case ZMQ_MCAST_LOOP:
        {
            int64_t value;
            value_len = sizeof(int64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_MCAST_LOOP value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_MCAST_LOOP */
# ifdef ZMQ_RCVTIMEO

        case ZMQ_RCVTIMEO:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RCVTIMEO value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RCVTIMEO */
# ifdef ZMQ_SNDTIMEO

        case ZMQ_SNDTIMEO:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_SNDTIMEO value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_SNDTIMEO */
# ifdef ZMQ_SNDBUF

        case ZMQ_SNDBUF:
        {
            uint64_t value;
            value_len = sizeof(uint64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_SNDBUF value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_SNDBUF */
# ifdef ZMQ_RCVBUF

        case ZMQ_RCVBUF:
        {
            uint64_t value;
            value_len = sizeof(uint64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RCVBUF value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RCVBUF */
# ifdef ZMQ_LINGER

        case ZMQ_LINGER:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_LINGER value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_LINGER */
# ifdef ZMQ_RECONNECT_IVL

        case ZMQ_RECONNECT_IVL:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RECONNECT_IVL */
# ifdef ZMQ_RECONNECT_IVL_MAX

        case ZMQ_RECONNECT_IVL_MAX:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RECONNECT_IVL_MAX value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RECONNECT_IVL_MAX */
# ifdef ZMQ_BACKLOG

        case ZMQ_BACKLOG:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_BACKLOG value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_BACKLOG */
# ifdef ZMQ_SUBSCRIBE

        case ZMQ_SUBSCRIBE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_SUBSCRIBE */
# ifdef ZMQ_UNSUBSCRIBE

        case ZMQ_UNSUBSCRIBE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ZMQ_UNSUBSCRIBE */
# ifdef ZMQ_TYPE

        case ZMQ_TYPE:
        {
            int value;
            value_len = sizeof(int);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_TYPE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_TYPE */
# ifdef ZMQ_RCVMORE

        case ZMQ_RCVMORE:
        {
            int64_t value;
            value_len = sizeof(int64_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_RCVMORE value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_RCVMORE */
# ifdef ZMQ_FD

        case ZMQ_FD:
        {
            php_stream *stream = php_zmq_create_zmq_fd(getThis());
            if (stream) {
                php_stream_to_zval(stream, return_value);
                return;
            }
            RETURN_FALSE;
        }
        break;

# endif /* ZMQ_FD */
# ifdef ZMQ_EVENTS

        case ZMQ_EVENTS:
        {
            uint32_t value;
            value_len = sizeof(uint32_t);
            if (zmq_getsockopt(intern->socket->z_socket, (int) key, &value, &value_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to get the option ZMQ::SOCKOPT_EVENTS value: %s", zmq_strerror(errno));
                return;
            }
            RETURN_LONG(value);
        }
        break;

# endif /* ZMQ_EVENTS */

        default:
            zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), PHP_ZMQ_INTERNAL_ERROR, "Unknown option key %ld", key);
            return;
    }

#endif /* ZMQ_VERSION_MAJOR == 2 */
}
/* }}} */

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
    Set a socket option
*/
PHP_METHOD(zmqsocket, setsockopt)
{
    php_zmq_socket_object *intern;
    long key;
    zval *zv;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz/", &key, &zv) == FAILURE) {
        return;
    }

    intern = PHP_ZMQ_SOCKET_OBJECT;

    if (!intern->socket || !intern->socket->z_socket) {
        zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "The socket is not properly initialised", PHP_ZMQ_INTERNAL_ERROR);
        return;
    }

    if (key > INT_MAX) {
        zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), PHP_ZMQ_INTERNAL_ERROR, "The key must be smaller than %d", INT_MAX);
        return;
    }

/* Support setting rcvhwm and sndhwm in one call for backwards compatibility */
#if ZMQ_VERSION_MAJOR > 2

        if (key == ZMQ_HWM) {
            int snd_hwm;
            size_t snd_hwm_len = sizeof(int);

            int value = (int) zval_get_long(zv);

            /* Get current value if we need to try to restore */
            if (zmq_getsockopt(intern->socket->z_socket, ZMQ_SNDHWM, &snd_hwm, &snd_hwm_len) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_HWM option: %s", zmq_strerror(errno));
                return;
            }

            /* First set snd hwm */
            if (zmq_setsockopt (intern->socket->z_socket, ZMQ_SNDHWM, &value, sizeof (int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_HWM option: %s", zmq_strerror(errno));
                return;
            }

            /* Next try to set rcv hwm */
            if (zmq_setsockopt (intern->socket->z_socket, ZMQ_RCVHWM, &value, sizeof (int)) != 0) {
                /* Setting rcv failed, try to roll back snd */
                if (zmq_setsockopt (intern->socket->z_socket, ZMQ_SNDHWM, &snd_hwm, sizeof (int)) != 0) {
                    zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_HWM option (ZMQ::SOCKOPT_SNDHWM changed): %s", zmq_strerror(errno));
                    return;
                }
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_HWM option: %s", zmq_strerror(errno));
                return;
            }
            ZMQ_RETURN_THIS;
            return;
        }

#endif

#if ZMQ_VERSION_MAJOR == 4

    switch (key) {

# ifdef ZMQ_HEARTBEAT_IVL
        case ZMQ_HEARTBEAT_IVL:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_HEARTBEAT_IVL option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_HEARTBEAT_IVL */

# ifdef ZMQ_HEARTBEAT_TTL
        case ZMQ_HEARTBEAT_TTL:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_HEARTBEAT_TTL option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_HEARTBEAT_TTL */

# ifdef ZMQ_HEARTBEAT_TIMEOUT
        case ZMQ_HEARTBEAT_TIMEOUT:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_HEARTBEAT_TIMEOUT option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_HEARTBEAT_TIMEOUT */

# ifdef ZMQ_TOS
        case ZMQ_TOS:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_TOS option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_TOS */

# ifdef ZMQ_ROUTER_HANDOVER
        case ZMQ_ROUTER_HANDOVER:
        {
{
        if (intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_ROUTER_HANDOVER is not valid for this socket type", errno);
            return;
        }
}
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_ROUTER_HANDOVER option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_ROUTER_HANDOVER */

# ifdef ZMQ_ROUTER_MANDATORY
        case ZMQ_ROUTER_MANDATORY:
        {
{
        if (intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_ROUTER_MANDATORY is not valid for this socket type", errno);
            return;
        }
}
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_ROUTER_MANDATORY option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_ROUTER_MANDATORY */

# ifdef ZMQ_PROBE_ROUTER
        case ZMQ_PROBE_ROUTER:
        {
{
        if (intern->socket->socket_type != ZMQ_ROUTER &&
            intern->socket->socket_type != ZMQ_DEALER &&
            intern->socket->socket_type != ZMQ_REQ) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_PROBE_ROUTER is not valid for this socket type", errno);
            return;
        }
}
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_PROBE_ROUTER option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_PROBE_ROUTER */

# ifdef ZMQ_REQ_RELAXED
        case ZMQ_REQ_RELAXED:
        {
{
        if (intern->socket->socket_type != ZMQ_REQ) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_REQ_RELAXED is not valid for this socket type", errno);
            return;
        }
}
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_REQ_RELAXED option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_REQ_RELAXED */

# ifdef ZMQ_REQ_CORRELATE
        case ZMQ_REQ_CORRELATE:
        {
{
        if (intern->socket->socket_type != ZMQ_REQ) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_REQ_CORRELATE is not valid for this socket type", errno);
            return;
        }
}
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_REQ_CORRELATE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_REQ_CORRELATE */

# ifdef ZMQ_CONFLATE
        case ZMQ_CONFLATE:
        {
{
        if (intern->socket->socket_type != ZMQ_PUSH &&
            intern->socket->socket_type != ZMQ_PULL &&
            intern->socket->socket_type != ZMQ_PUB &&
            intern->socket->socket_type != ZMQ_SUB &&
            intern->socket->socket_type != ZMQ_DEALER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_CONFLATE is not valid for this socket type", errno);
            return;
        }
}
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_CONFLATE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_CONFLATE */

# ifdef ZMQ_ZAP_DOMAIN
        case ZMQ_ZAP_DOMAIN:
        {
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_ZAP_DOMAIN option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_ZAP_DOMAIN */

# ifdef ZMQ_MECHANISM
        case ZMQ_MECHANISM:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_MECHANISM is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_MECHANISM */

# ifdef ZMQ_PLAIN_SERVER
        case ZMQ_PLAIN_SERVER:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_PLAIN_SERVER option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_PLAIN_SERVER */

# ifdef ZMQ_PLAIN_USERNAME
        case ZMQ_PLAIN_USERNAME:
        {
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_PLAIN_USERNAME option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_PLAIN_USERNAME */

# ifdef ZMQ_PLAIN_PASSWORD
        case ZMQ_PLAIN_PASSWORD:
        {
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_PLAIN_PASSWORD option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_PLAIN_PASSWORD */

# ifdef ZMQ_CURVE_SERVER
        case ZMQ_CURVE_SERVER:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_CURVE_SERVER option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_CURVE_SERVER */

# ifdef ZMQ_CURVE_PUBLICKEY
        case ZMQ_CURVE_PUBLICKEY:
        {
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_CURVE_PUBLICKEY option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_CURVE_PUBLICKEY */

# ifdef ZMQ_CURVE_SECRETKEY
        case ZMQ_CURVE_SECRETKEY:
        {
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_CURVE_SECRETKEY option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_CURVE_SECRETKEY */

# ifdef ZMQ_CURVE_SERVERKEY
        case ZMQ_CURVE_SERVERKEY:
        {
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_CURVE_SERVERKEY option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_CURVE_SERVERKEY */

# ifdef ZMQ_GSSAPI_SERVER
        case ZMQ_GSSAPI_SERVER:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_GSSAPI_SERVER option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_GSSAPI_SERVER */

# ifdef ZMQ_GSSAPI_PLAINTEXT
        case ZMQ_GSSAPI_PLAINTEXT:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_GSSAPI_PLAINTEXT option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_GSSAPI_PLAINTEXT */

# ifdef ZMQ_GSSAPI_PRINCIPAL
        case ZMQ_GSSAPI_PRINCIPAL:
        {
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_GSSAPI_PRINCIPAL option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_GSSAPI_PRINCIPAL */

# ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL
        case ZMQ_GSSAPI_SERVICE_PRINCIPAL:
        {
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_GSSAPI_SERVICE_PRINCIPAL option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL */

# ifdef ZMQ_IPV6
        case ZMQ_IPV6:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_IPV6 option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_IPV6 */

# ifdef ZMQ_IMMEDIATE
        case ZMQ_IMMEDIATE:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_IMMEDIATE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_IMMEDIATE */

# ifdef ZMQ_ROUTER_RAW
        case ZMQ_ROUTER_RAW:
        {
{
        if (intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_ROUTER_RAW is not valid for this socket type", errno);
            return;
        }
}
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_ROUTER_RAW option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_ROUTER_RAW */

# ifdef ZMQ_IPV4ONLY
        case ZMQ_IPV4ONLY:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_IPV4ONLY option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_IPV4ONLY */

# ifdef ZMQ_TYPE
        case ZMQ_TYPE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_TYPE */

# ifdef ZMQ_SNDHWM
        case ZMQ_SNDHWM:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_SNDHWM option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_SNDHWM */

# ifdef ZMQ_RCVHWM
        case ZMQ_RCVHWM:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RCVHWM option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RCVHWM */

# ifdef ZMQ_AFFINITY
        case ZMQ_AFFINITY:
        {
            uint64_t value = (uint64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_AFFINITY option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_AFFINITY */

# ifdef ZMQ_SUBSCRIBE
        case ZMQ_SUBSCRIBE:
        {
{
        if (intern->socket->socket_type != ZMQ_SUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_SUBSCRIBE is not valid for this socket type", errno);
            return;
        }
}
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_SUBSCRIBE */

# ifdef ZMQ_UNSUBSCRIBE
        case ZMQ_UNSUBSCRIBE:
        {
{
        if (intern->socket->socket_type != ZMQ_SUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_UNSUBSCRIBE is not valid for this socket type", errno);
            return;
        }
}
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_UNSUBSCRIBE */

# ifdef ZMQ_IDENTITY
        case ZMQ_IDENTITY:
        {
{
        if (intern->socket->socket_type != ZMQ_REQ &&
            intern->socket->socket_type != ZMQ_REP &&
            intern->socket->socket_type != ZMQ_DEALER &&
            intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_IDENTITY is not valid for this socket type", errno);
            return;
        }
}
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_IDENTITY option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_IDENTITY */

# ifdef ZMQ_RATE
        case ZMQ_RATE:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RATE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RATE */

# ifdef ZMQ_RECOVERY_IVL
        case ZMQ_RECOVERY_IVL:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RECOVERY_IVL */

# ifdef ZMQ_SNDBUF
        case ZMQ_SNDBUF:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_SNDBUF option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_SNDBUF */

# ifdef ZMQ_RCVBUF
        case ZMQ_RCVBUF:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RCVBUF option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RCVBUF */

# ifdef ZMQ_LINGER
        case ZMQ_LINGER:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_LINGER option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_LINGER */

# ifdef ZMQ_RECONNECT_IVL
        case ZMQ_RECONNECT_IVL:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RECONNECT_IVL */

# ifdef ZMQ_RECONNECT_IVL_MAX
        case ZMQ_RECONNECT_IVL_MAX:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RECONNECT_IVL_MAX */

# ifdef ZMQ_BACKLOG
        case ZMQ_BACKLOG:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_BACKLOG option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_BACKLOG */

# ifdef ZMQ_MAXMSGSIZE
        case ZMQ_MAXMSGSIZE:
        {
            int64_t value = (int64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_MAXMSGSIZE */

# ifdef ZMQ_MULTICAST_HOPS
        case ZMQ_MULTICAST_HOPS:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_MULTICAST_HOPS option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_MULTICAST_HOPS */

# ifdef ZMQ_RCVTIMEO
        case ZMQ_RCVTIMEO:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RCVTIMEO */

# ifdef ZMQ_SNDTIMEO
        case ZMQ_SNDTIMEO:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_SNDTIMEO */

# ifdef ZMQ_XPUB_VERBOSE
        case ZMQ_XPUB_VERBOSE:
        {
{
        if (intern->socket->socket_type != ZMQ_XPUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_XPUB_VERBOSE is not valid for this socket type", errno);
            return;
        }
}
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_XPUB_VERBOSE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_XPUB_VERBOSE */

# ifdef ZMQ_TCP_KEEPALIVE
        case ZMQ_TCP_KEEPALIVE:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_TCP_KEEPALIVE */

# ifdef ZMQ_TCP_KEEPALIVE_IDLE
        case ZMQ_TCP_KEEPALIVE_IDLE:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_TCP_KEEPALIVE_IDLE */

# ifdef ZMQ_TCP_KEEPALIVE_CNT
        case ZMQ_TCP_KEEPALIVE_CNT:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_TCP_KEEPALIVE_CNT */

# ifdef ZMQ_TCP_KEEPALIVE_INTVL
        case ZMQ_TCP_KEEPALIVE_INTVL:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_TCP_KEEPALIVE_INTVL */

# ifdef ZMQ_TCP_ACCEPT_FILTER
        case ZMQ_TCP_ACCEPT_FILTER:
        {
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_TCP_ACCEPT_FILTER option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_TCP_ACCEPT_FILTER */

# ifdef ZMQ_RCVMORE
        case ZMQ_RCVMORE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_RCVMORE */

# ifdef ZMQ_FD
        case ZMQ_FD:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_FD is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_FD */

# ifdef ZMQ_EVENTS
        case ZMQ_EVENTS:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_EVENTS is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_EVENTS */

# ifdef ZMQ_LAST_ENDPOINT
        case ZMQ_LAST_ENDPOINT:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_LAST_ENDPOINT is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_LAST_ENDPOINT */


        default:
            zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), PHP_ZMQ_INTERNAL_ERROR, "Unknown option key %ld", key);
            return;
    }
    ZMQ_RETURN_THIS;
#endif
#if ZMQ_VERSION_MAJOR == 3

    switch (key) {

# ifdef ZMQ_ROUTER_RAW
        case ZMQ_ROUTER_RAW:
        {
{
        if (intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_ROUTER_RAW is not valid for this socket type", errno);
            return;
        }
}
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_ROUTER_RAW option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_ROUTER_RAW */

# ifdef ZMQ_IPV4ONLY
        case ZMQ_IPV4ONLY:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_IPV4ONLY option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_IPV4ONLY */

# ifdef ZMQ_TYPE
        case ZMQ_TYPE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_TYPE */

# ifdef ZMQ_SNDHWM
        case ZMQ_SNDHWM:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_SNDHWM option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_SNDHWM */

# ifdef ZMQ_RCVHWM
        case ZMQ_RCVHWM:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RCVHWM option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RCVHWM */

# ifdef ZMQ_AFFINITY
        case ZMQ_AFFINITY:
        {
            uint64_t value = (uint64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_AFFINITY option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_AFFINITY */

# ifdef ZMQ_SUBSCRIBE
        case ZMQ_SUBSCRIBE:
        {
{
        if (intern->socket->socket_type != ZMQ_SUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_SUBSCRIBE is not valid for this socket type", errno);
            return;
        }
}
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_SUBSCRIBE */

# ifdef ZMQ_UNSUBSCRIBE
        case ZMQ_UNSUBSCRIBE:
        {
{
        if (intern->socket->socket_type != ZMQ_SUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_UNSUBSCRIBE is not valid for this socket type", errno);
            return;
        }
}
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_UNSUBSCRIBE */

# ifdef ZMQ_IDENTITY
        case ZMQ_IDENTITY:
        {
{
        if (intern->socket->socket_type != ZMQ_REQ &&
            intern->socket->socket_type != ZMQ_REP &&
            intern->socket->socket_type != ZMQ_DEALER &&
            intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_IDENTITY is not valid for this socket type", errno);
            return;
        }
}
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_IDENTITY option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_IDENTITY */

# ifdef ZMQ_RATE
        case ZMQ_RATE:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RATE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RATE */

# ifdef ZMQ_RECOVERY_IVL
        case ZMQ_RECOVERY_IVL:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RECOVERY_IVL */

# ifdef ZMQ_SNDBUF
        case ZMQ_SNDBUF:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_SNDBUF option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_SNDBUF */

# ifdef ZMQ_RCVBUF
        case ZMQ_RCVBUF:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RCVBUF option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RCVBUF */

# ifdef ZMQ_LINGER
        case ZMQ_LINGER:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_LINGER option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_LINGER */

# ifdef ZMQ_RECONNECT_IVL
        case ZMQ_RECONNECT_IVL:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RECONNECT_IVL */

# ifdef ZMQ_RECONNECT_IVL_MAX
        case ZMQ_RECONNECT_IVL_MAX:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RECONNECT_IVL_MAX */

# ifdef ZMQ_BACKLOG
        case ZMQ_BACKLOG:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_BACKLOG option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_BACKLOG */

# ifdef ZMQ_MAXMSGSIZE
        case ZMQ_MAXMSGSIZE:
        {
            int64_t value = (int64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_MAXMSGSIZE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_MAXMSGSIZE */

# ifdef ZMQ_MULTICAST_HOPS
        case ZMQ_MULTICAST_HOPS:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_MULTICAST_HOPS option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_MULTICAST_HOPS */

# ifdef ZMQ_RCVTIMEO
        case ZMQ_RCVTIMEO:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RCVTIMEO */

# ifdef ZMQ_SNDTIMEO
        case ZMQ_SNDTIMEO:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_SNDTIMEO */

# ifdef ZMQ_XPUB_VERBOSE
        case ZMQ_XPUB_VERBOSE:
        {
{
        if (intern->socket->socket_type != ZMQ_XPUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_XPUB_VERBOSE is not valid for this socket type", errno);
            return;
        }
}
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_XPUB_VERBOSE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_XPUB_VERBOSE */

# ifdef ZMQ_TCP_KEEPALIVE
        case ZMQ_TCP_KEEPALIVE:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_TCP_KEEPALIVE */

# ifdef ZMQ_TCP_KEEPALIVE_IDLE
        case ZMQ_TCP_KEEPALIVE_IDLE:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_TCP_KEEPALIVE_IDLE */

# ifdef ZMQ_TCP_KEEPALIVE_CNT
        case ZMQ_TCP_KEEPALIVE_CNT:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_TCP_KEEPALIVE_CNT */

# ifdef ZMQ_TCP_KEEPALIVE_INTVL
        case ZMQ_TCP_KEEPALIVE_INTVL:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_TCP_KEEPALIVE_INTVL */

# ifdef ZMQ_TCP_ACCEPT_FILTER
        case ZMQ_TCP_ACCEPT_FILTER:
        {
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_TCP_ACCEPT_FILTER option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_TCP_ACCEPT_FILTER */

# ifdef ZMQ_RCVMORE
        case ZMQ_RCVMORE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_RCVMORE */

# ifdef ZMQ_FD
        case ZMQ_FD:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_FD is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_FD */

# ifdef ZMQ_EVENTS
        case ZMQ_EVENTS:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_EVENTS is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_EVENTS */

# ifdef ZMQ_LAST_ENDPOINT
        case ZMQ_LAST_ENDPOINT:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_LAST_ENDPOINT is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_LAST_ENDPOINT */


        default:
            zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), PHP_ZMQ_INTERNAL_ERROR, "Unknown option key %ld", key);
            return;
    }
    ZMQ_RETURN_THIS;
#endif
#if ZMQ_VERSION_MAJOR == 2

    switch (key) {

# ifdef ZMQ_HWM
        case ZMQ_HWM:
        {
            uint64_t value = (uint64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_HWM option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_HWM */

# ifdef ZMQ_SWAP
        case ZMQ_SWAP:
        {
            int64_t value = (int64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_SWAP option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_SWAP */

# ifdef ZMQ_AFFINITY
        case ZMQ_AFFINITY:
        {
            uint64_t value = (uint64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_AFFINITY option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_AFFINITY */

# ifdef ZMQ_IDENTITY
        case ZMQ_IDENTITY:
        {
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_IDENTITY option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_IDENTITY */

# ifdef ZMQ_RATE
        case ZMQ_RATE:
        {
            int64_t value = (int64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RATE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RATE */

# ifdef ZMQ_RECOVERY_IVL
        case ZMQ_RECOVERY_IVL:
        {
            int64_t value = (int64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RECOVERY_IVL */

# ifdef ZMQ_RECOVERY_IVL_MSEC
        case ZMQ_RECOVERY_IVL_MSEC:
        {
            int64_t value = (int64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RECOVERY_IVL_MSEC option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RECOVERY_IVL_MSEC */

# ifdef ZMQ_MCAST_LOOP
        case ZMQ_MCAST_LOOP:
        {
            int64_t value = (int64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_MCAST_LOOP option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_MCAST_LOOP */

# ifdef ZMQ_RCVTIMEO
        case ZMQ_RCVTIMEO:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RCVTIMEO option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RCVTIMEO */

# ifdef ZMQ_SNDTIMEO
        case ZMQ_SNDTIMEO:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_SNDTIMEO option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_SNDTIMEO */

# ifdef ZMQ_SNDBUF
        case ZMQ_SNDBUF:
        {
            uint64_t value = (uint64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_SNDBUF option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_SNDBUF */

# ifdef ZMQ_RCVBUF
        case ZMQ_RCVBUF:
        {
            uint64_t value = (uint64_t) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(uint64_t)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RCVBUF option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RCVBUF */

# ifdef ZMQ_LINGER
        case ZMQ_LINGER:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_LINGER option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_LINGER */

# ifdef ZMQ_RECONNECT_IVL
        case ZMQ_RECONNECT_IVL:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RECONNECT_IVL */

# ifdef ZMQ_RECONNECT_IVL_MAX
        case ZMQ_RECONNECT_IVL_MAX:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_RECONNECT_IVL_MAX option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_RECONNECT_IVL_MAX */

# ifdef ZMQ_BACKLOG
        case ZMQ_BACKLOG:
        {
            int value = (int) zval_get_long(zv);

            if (zmq_setsockopt(intern->socket->z_socket, key, &value, sizeof(int)) != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_BACKLOG option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_BACKLOG */

# ifdef ZMQ_SUBSCRIBE
        case ZMQ_SUBSCRIBE:
        {
{
        if (intern->socket->socket_type != ZMQ_SUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_SUBSCRIBE is not valid for this socket type", errno);
            return;
        }
}
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_SUBSCRIBE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_SUBSCRIBE */

# ifdef ZMQ_UNSUBSCRIBE
        case ZMQ_UNSUBSCRIBE:
        {
{
        if (intern->socket->socket_type != ZMQ_SUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_UNSUBSCRIBE is not valid for this socket type", errno);
            return;
        }
}
            int rc;
            zend_string *str = zval_get_string(zv);

            rc = zmq_setsockopt(intern->socket->z_socket, key, str->val, str->len);
            zend_string_release(str);

            if (rc != 0) {
                zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), errno, "Failed to set socket ZMQ::SOCKOPT_UNSUBSCRIBE option: %s", zmq_strerror(errno));
                return;
            }
        }
        break;

# endif /* ifdef ZMQ_UNSUBSCRIBE */

# ifdef ZMQ_TYPE
        case ZMQ_TYPE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_TYPE */

# ifdef ZMQ_RCVMORE
        case ZMQ_RCVMORE:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_RCVMORE */

# ifdef ZMQ_FD
        case ZMQ_FD:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_FD is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_FD */

# ifdef ZMQ_EVENTS
        case ZMQ_EVENTS:
        {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_EVENTS is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        }
        break;

# endif /* ifdef ZMQ_EVENTS */


        default:
            zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), PHP_ZMQ_INTERNAL_ERROR, "Unknown option key %ld", key);
            return;
    }
    ZMQ_RETURN_THIS;
#endif
}


