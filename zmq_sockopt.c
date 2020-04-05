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

/*
    WARNING! WARNING!

    This file is generated code. See README for editing
*/

#include "php_zmq.h"
#include "php_zmq_private.h"
#include "zmq_object_access.c"
#include "zmq_sockopts_makros.h"



/*
    sockopts_register.gsl
*/
void php_zmq_register_sockopt_constants (zend_class_entry *php_zmq_sc_entry)
{
#define PHP_ZMQ_REGISTER_SOCKOPT(const_name, value) zend_declare_class_constant_long(php_zmq_sc_entry, const_name, sizeof(const_name) - 1, value);

#if (ZMQ_VERSION_MAJOR >= 4)
#   if (ZMQ_VERSION_MINOR >= 3)
# ifdef ZMQ_ONLY_FIRST_SUBSCRIBE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ONLY_FIRST_SUBSCRIBE", ZMQ_ONLY_FIRST_SUBSCRIBE);
# endif
# ifdef ZMQ_WSS_TRUST_SYSTEM
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_WSS_TRUST_SYSTEM", ZMQ_WSS_TRUST_SYSTEM);
# endif
# ifdef ZMQ_WSS_HOSTNAME
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_WSS_HOSTNAME", ZMQ_WSS_HOSTNAME);
# endif
# ifdef ZMQ_WSS_TRUST_PEM
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_WSS_TRUST_PEM", ZMQ_WSS_TRUST_PEM);
# endif
# ifdef ZMQ_WSS_CERT_PEM
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_WSS_CERT_PEM", ZMQ_WSS_CERT_PEM);
# endif
# ifdef ZMQ_WSS_KEY_PEM
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_WSS_KEY_PEM", ZMQ_WSS_KEY_PEM);
# endif
# ifdef ZMQ_OUT_BATCH_SIZE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_OUT_BATCH_SIZE", ZMQ_OUT_BATCH_SIZE);
# endif
# ifdef ZMQ_IN_BATCH_SIZE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_IN_BATCH_SIZE", ZMQ_IN_BATCH_SIZE);
# endif
# ifdef ZMQ_SOCKS_PASSWORD
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SOCKS_PASSWORD", ZMQ_SOCKS_PASSWORD);
# endif
# ifdef ZMQ_SOCKS_USERNAME
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SOCKS_USERNAME", ZMQ_SOCKS_USERNAME);
# endif
# ifdef ZMQ_XPUB_MANUAL_LAST_VALUE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_XPUB_MANUAL_LAST_VALUE", ZMQ_XPUB_MANUAL_LAST_VALUE);
# endif
# ifdef ZMQ_ROUTER_NOTIFY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ROUTER_NOTIFY", ZMQ_ROUTER_NOTIFY);
# endif
# ifdef ZMQ_MULTICAST_LOOP
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MULTICAST_LOOP", ZMQ_MULTICAST_LOOP);
# endif
# ifdef ZMQ_METADATA
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_METADATA", ZMQ_METADATA);
# endif
# ifdef ZMQ_LOOPBACK_FASTPATH
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LOOPBACK_FASTPATH", ZMQ_LOOPBACK_FASTPATH);
# endif
# ifdef ZMQ_ZAP_ENFORCE_DOMAIN
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ZAP_ENFORCE_DOMAIN", ZMQ_ZAP_ENFORCE_DOMAIN);
# endif
# ifdef ZMQ_GSSAPI_PRINCIPAL_NAMETYPE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_GSSAPI_PRINCIPAL_NAMETYPE", ZMQ_GSSAPI_PRINCIPAL_NAMETYPE);
# endif
# ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE", ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE);
# endif
# ifdef ZMQ_BINDTODEVICE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_BINDTODEVICE", ZMQ_BINDTODEVICE);
# endif
# endif
#endif /* ZMQ_MAJOR_VERSION == 4 */
#if (ZMQ_VERSION_MAJOR >= 4)
#   if (ZMQ_VERSION_MINOR >= 2)
# ifdef ZMQ_HEARTBEAT_IVL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HEARTBEAT_IVL", ZMQ_HEARTBEAT_IVL);
# endif
# ifdef ZMQ_HEARTBEAT_TTL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HEARTBEAT_TTL", ZMQ_HEARTBEAT_TTL);
# endif
# ifdef ZMQ_HEARTBEAT_TIMEOUT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HEARTBEAT_TIMEOUT", ZMQ_HEARTBEAT_TIMEOUT);
# endif
# ifdef ZMQ_USE_FD
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_USE_FD", ZMQ_USE_FD);
# endif
# ifdef ZMQ_XPUB_MANUAL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_XPUB_MANUAL", ZMQ_XPUB_MANUAL);
# endif
# ifdef ZMQ_XPUB_WELCOME_MSG
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_XPUB_WELCOME_MSG", ZMQ_XPUB_WELCOME_MSG);
# endif
# ifdef ZMQ_STREAM_NOTIFY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_STREAM_NOTIFY", ZMQ_STREAM_NOTIFY);
# endif
# ifdef ZMQ_INVERT_MATCHING
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_INVERT_MATCHING", ZMQ_INVERT_MATCHING);
# endif
# ifdef ZMQ_XPUB_VERBOSER
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_XPUB_VERBOSER", ZMQ_XPUB_VERBOSER);
# endif
# ifdef ZMQ_CONNECT_TIMEOUT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_CONNECT_TIMEOUT", ZMQ_CONNECT_TIMEOUT);
# endif
# ifdef ZMQ_TCP_MAXRT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TCP_MAXRT", ZMQ_TCP_MAXRT);
# endif
# ifdef ZMQ_THREAD_SAFE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_THREAD_SAFE", ZMQ_THREAD_SAFE);
# endif
# ifdef ZMQ_MULTICAST_MAXTPDU
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MULTICAST_MAXTPDU", ZMQ_MULTICAST_MAXTPDU);
# endif
# ifdef ZMQ_VMCI_BUFFER_SIZE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_VMCI_BUFFER_SIZE", ZMQ_VMCI_BUFFER_SIZE);
# endif
# ifdef ZMQ_VMCI_BUFFER_MIN_SIZE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_VMCI_BUFFER_MIN_SIZE", ZMQ_VMCI_BUFFER_MIN_SIZE);
# endif
# ifdef ZMQ_VMCI_BUFFER_MAX_SIZE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_VMCI_BUFFER_MAX_SIZE", ZMQ_VMCI_BUFFER_MAX_SIZE);
# endif
# ifdef ZMQ_VMCI_CONNECT_TIMEOUT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_VMCI_CONNECT_TIMEOUT", ZMQ_VMCI_CONNECT_TIMEOUT);
# endif
# endif
#endif /* ZMQ_MAJOR_VERSION == 4 */
#if (ZMQ_VERSION_MAJOR >= 4)
#   if (ZMQ_VERSION_MINOR >= 1)
# ifdef ZMQ_TOS
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_TOS", ZMQ_TOS);
# endif
# ifdef ZMQ_ROUTER_HANDOVER
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_ROUTER_HANDOVER", ZMQ_ROUTER_HANDOVER);
# endif
# ifdef ZMQ_CONNECT_RID
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_CONNECT_RID", ZMQ_CONNECT_RID);
# endif
# ifdef ZMQ_HANDSHAKE_IVL
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HANDSHAKE_IVL", ZMQ_HANDSHAKE_IVL);
# endif
# ifdef ZMQ_SOCKS_PROXY
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SOCKS_PROXY", ZMQ_SOCKS_PROXY);
# endif
# ifdef ZMQ_XPUB_NODROP
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_XPUB_NODROP", ZMQ_XPUB_NODROP);
# endif
# endif
#endif /* ZMQ_MAJOR_VERSION == 4 */
#if (ZMQ_VERSION_MAJOR >= 4)
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
#endif /* ZMQ_MAJOR_VERSION == 4 */
#if (ZMQ_VERSION_MAJOR >= 3)
# ifdef ZMQ_SNDHWM
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_SNDHWM", ZMQ_SNDHWM);
# endif
# ifdef ZMQ_RCVHWM
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_RCVHWM", ZMQ_RCVHWM);
# endif
# ifdef ZMQ_MAXMSGSIZE
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MAXMSGSIZE", ZMQ_MAXMSGSIZE);
# endif
# ifdef ZMQ_MULTICAST_HOPS
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_MULTICAST_HOPS", ZMQ_MULTICAST_HOPS);
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
# ifdef ZMQ_LAST_ENDPOINT
    PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_LAST_ENDPOINT", ZMQ_LAST_ENDPOINT);
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
#endif /* ZMQ_MAJOR_VERSION == 3 */
#if (ZMQ_VERSION_MAJOR >= 2)
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
    // PHP_ZMQ_REGISTER_SOCKOPT("SOCKOPT_HWM", ZMQ_HWM); // already present
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

#if (ZMQ_VERSION_MAJOR >= 4)
#   if (ZMQ_VERSION_MINOR >= 3)

    switch (key) {
# ifdef ZMQ_ONLY_FIRST_SUBSCRIBE

        case ZMQ_ONLY_FIRST_SUBSCRIBE:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_ONLY_FIRST_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_ONLY_FIRST_SUBSCRIBE */
# ifdef ZMQ_WSS_TRUST_SYSTEM

        case ZMQ_WSS_TRUST_SYSTEM:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_WSS_TRUST_SYSTEM is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_WSS_TRUST_SYSTEM */
# ifdef ZMQ_WSS_HOSTNAME

        case ZMQ_WSS_HOSTNAME:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_WSS_HOSTNAME is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_WSS_HOSTNAME */
# ifdef ZMQ_WSS_TRUST_PEM

        case ZMQ_WSS_TRUST_PEM:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_WSS_TRUST_PEM is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_WSS_TRUST_PEM */
# ifdef ZMQ_WSS_CERT_PEM

        case ZMQ_WSS_CERT_PEM:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_WSS_CERT_PEM is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_WSS_CERT_PEM */
# ifdef ZMQ_WSS_KEY_PEM

        case ZMQ_WSS_KEY_PEM:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_WSS_KEY_PEM is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_WSS_KEY_PEM */
# ifdef ZMQ_OUT_BATCH_SIZE

        case ZMQ_OUT_BATCH_SIZE:
	        SOCKOPTS_GET_INT(OUT_BATCH_SIZE, int);
        break;

# endif /* ZMQ_OUT_BATCH_SIZE */
# ifdef ZMQ_IN_BATCH_SIZE

        case ZMQ_IN_BATCH_SIZE:
	        SOCKOPTS_GET_INT(IN_BATCH_SIZE, int);
        break;

# endif /* ZMQ_IN_BATCH_SIZE */
# ifdef ZMQ_SOCKS_PASSWORD

        case ZMQ_SOCKS_PASSWORD:
	        SOCKOPTS_GET_STRING(SOCKS_PASSWORD, 255, 0)
        break;

# endif /* ZMQ_SOCKS_PASSWORD */
# ifdef ZMQ_SOCKS_USERNAME

        case ZMQ_SOCKS_USERNAME:
	        SOCKOPTS_GET_STRING(SOCKS_USERNAME, 255, 0)
        break;

# endif /* ZMQ_SOCKS_USERNAME */
# ifdef ZMQ_XPUB_MANUAL_LAST_VALUE

        case ZMQ_XPUB_MANUAL_LAST_VALUE:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_XPUB_MANUAL_LAST_VALUE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_XPUB_MANUAL_LAST_VALUE */
# ifdef ZMQ_ROUTER_NOTIFY

        case ZMQ_ROUTER_NOTIFY:
	        SOCKOPTS_GET_INT(ROUTER_NOTIFY, int);
        break;

# endif /* ZMQ_ROUTER_NOTIFY */
# ifdef ZMQ_MULTICAST_LOOP

        case ZMQ_MULTICAST_LOOP:
	        SOCKOPTS_GET_INT(MULTICAST_LOOP, int);
        break;

# endif /* ZMQ_MULTICAST_LOOP */
# ifdef ZMQ_METADATA

        case ZMQ_METADATA:
	        SOCKOPTS_GET_STRING(METADATA, 255, 0)
        break;

# endif /* ZMQ_METADATA */
# ifdef ZMQ_LOOPBACK_FASTPATH

        case ZMQ_LOOPBACK_FASTPATH:
	        SOCKOPTS_GET_INT(LOOPBACK_FASTPATH, int);
        break;

# endif /* ZMQ_LOOPBACK_FASTPATH */
# ifdef ZMQ_ZAP_ENFORCE_DOMAIN

        case ZMQ_ZAP_ENFORCE_DOMAIN:
	        SOCKOPTS_GET_INT(ZAP_ENFORCE_DOMAIN, int);
        break;

# endif /* ZMQ_ZAP_ENFORCE_DOMAIN */
# ifdef ZMQ_GSSAPI_PRINCIPAL_NAMETYPE

        case ZMQ_GSSAPI_PRINCIPAL_NAMETYPE:
	        SOCKOPTS_GET_INT(GSSAPI_PRINCIPAL_NAMETYPE, int);
        break;

# endif /* ZMQ_GSSAPI_PRINCIPAL_NAMETYPE */
# ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE

        case ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE:
	        SOCKOPTS_GET_INT(GSSAPI_SERVICE_PRINCIPAL_NAMETYPE, int);
        break;

# endif /* ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE */
# ifdef ZMQ_BINDTODEVICE

        case ZMQ_BINDTODEVICE:
	        SOCKOPTS_GET_STRING(BINDTODEVICE, 255, 0)
        break;

# endif /* ZMQ_BINDTODEVICE */
    }

# endif

#endif /* ZMQ_VERSION_MAJOR == 4 */
#if (ZMQ_VERSION_MAJOR >= 4)
#   if (ZMQ_VERSION_MINOR >= 2)

    switch (key) {
# ifdef ZMQ_HEARTBEAT_IVL

        case ZMQ_HEARTBEAT_IVL:
	        SOCKOPTS_GET_INT(HEARTBEAT_IVL, int);
        break;

# endif /* ZMQ_HEARTBEAT_IVL */
# ifdef ZMQ_HEARTBEAT_TTL

        case ZMQ_HEARTBEAT_TTL:
	        SOCKOPTS_GET_INT(HEARTBEAT_TTL, int);
        break;

# endif /* ZMQ_HEARTBEAT_TTL */
# ifdef ZMQ_HEARTBEAT_TIMEOUT

        case ZMQ_HEARTBEAT_TIMEOUT:
	        SOCKOPTS_GET_INT(HEARTBEAT_TIMEOUT, int);
        break;

# endif /* ZMQ_HEARTBEAT_TIMEOUT */
# ifdef ZMQ_USE_FD

        case ZMQ_USE_FD:
	        SOCKOPTS_GET_INT(USE_FD, int);
        break;

# endif /* ZMQ_USE_FD */
# ifdef ZMQ_XPUB_MANUAL

        case ZMQ_XPUB_MANUAL:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_XPUB_MANUAL is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_XPUB_MANUAL */
# ifdef ZMQ_XPUB_WELCOME_MSG

        case ZMQ_XPUB_WELCOME_MSG:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_XPUB_WELCOME_MSG is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_XPUB_WELCOME_MSG */
# ifdef ZMQ_STREAM_NOTIFY

        case ZMQ_STREAM_NOTIFY:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_STREAM_NOTIFY is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_STREAM_NOTIFY */
# ifdef ZMQ_INVERT_MATCHING

        case ZMQ_INVERT_MATCHING:
{
        if (intern->socket->socket_type != ZMQ_XPUB &&
            intern->socket->socket_type != ZMQ_PUB &&
            intern->socket->socket_type != ZMQ_SUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_INVERT_MATCHING is not valid for this socket type", errno);
            return;
        }
}
	        SOCKOPTS_GET_INT(INVERT_MATCHING, int);
        break;

# endif /* ZMQ_INVERT_MATCHING */
# ifdef ZMQ_XPUB_VERBOSER

        case ZMQ_XPUB_VERBOSER:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_XPUB_VERBOSER is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_XPUB_VERBOSER */
# ifdef ZMQ_CONNECT_TIMEOUT

        case ZMQ_CONNECT_TIMEOUT:
	        SOCKOPTS_GET_INT(CONNECT_TIMEOUT, int);
        break;

# endif /* ZMQ_CONNECT_TIMEOUT */
# ifdef ZMQ_TCP_MAXRT

        case ZMQ_TCP_MAXRT:
	        SOCKOPTS_GET_INT(TCP_MAXRT, int);
        break;

# endif /* ZMQ_TCP_MAXRT */
# ifdef ZMQ_THREAD_SAFE

        case ZMQ_THREAD_SAFE:
	        SOCKOPTS_GET_INT(THREAD_SAFE, int);
        break;

# endif /* ZMQ_THREAD_SAFE */
# ifdef ZMQ_MULTICAST_MAXTPDU

        case ZMQ_MULTICAST_MAXTPDU:
	        SOCKOPTS_GET_INT(MULTICAST_MAXTPDU, int);
        break;

# endif /* ZMQ_MULTICAST_MAXTPDU */
# ifdef ZMQ_VMCI_BUFFER_SIZE

        case ZMQ_VMCI_BUFFER_SIZE:
	        SOCKOPTS_GET_INT(VMCI_BUFFER_SIZE, uint64_t);
        break;

# endif /* ZMQ_VMCI_BUFFER_SIZE */
# ifdef ZMQ_VMCI_BUFFER_MIN_SIZE

        case ZMQ_VMCI_BUFFER_MIN_SIZE:
	        SOCKOPTS_GET_INT(VMCI_BUFFER_MIN_SIZE, uint64_t);
        break;

# endif /* ZMQ_VMCI_BUFFER_MIN_SIZE */
# ifdef ZMQ_VMCI_BUFFER_MAX_SIZE

        case ZMQ_VMCI_BUFFER_MAX_SIZE:
	        SOCKOPTS_GET_INT(VMCI_BUFFER_MAX_SIZE, uint64_t);
        break;

# endif /* ZMQ_VMCI_BUFFER_MAX_SIZE */
# ifdef ZMQ_VMCI_CONNECT_TIMEOUT

        case ZMQ_VMCI_CONNECT_TIMEOUT:
	        SOCKOPTS_GET_INT(VMCI_CONNECT_TIMEOUT, int);
        break;

# endif /* ZMQ_VMCI_CONNECT_TIMEOUT */
    }

# endif

#endif /* ZMQ_VERSION_MAJOR == 4 */
#if (ZMQ_VERSION_MAJOR >= 4)
#   if (ZMQ_VERSION_MINOR >= 1)

    switch (key) {
# ifdef ZMQ_TOS

        case ZMQ_TOS:
	        SOCKOPTS_GET_INT(TOS, int);
        break;

# endif /* ZMQ_TOS */
# ifdef ZMQ_ROUTER_HANDOVER

        case ZMQ_ROUTER_HANDOVER:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_ROUTER_HANDOVER is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_ROUTER_HANDOVER */
# ifdef ZMQ_CONNECT_RID

        case ZMQ_CONNECT_RID:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_CONNECT_RID is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_CONNECT_RID */
# ifdef ZMQ_HANDSHAKE_IVL

        case ZMQ_HANDSHAKE_IVL:
	        SOCKOPTS_GET_INT(HANDSHAKE_IVL, int);
        break;

# endif /* ZMQ_HANDSHAKE_IVL */
# ifdef ZMQ_SOCKS_PROXY

        case ZMQ_SOCKS_PROXY:
	        SOCKOPTS_GET_STRING(SOCKS_PROXY, 255, 0)
        break;

# endif /* ZMQ_SOCKS_PROXY */
# ifdef ZMQ_XPUB_NODROP

        case ZMQ_XPUB_NODROP:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_XPUB_NODROP is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_XPUB_NODROP */
    }

# endif

#endif /* ZMQ_VERSION_MAJOR == 4 */
#if (ZMQ_VERSION_MAJOR >= 4)

    switch (key) {
# ifdef ZMQ_ROUTER_MANDATORY

        case ZMQ_ROUTER_MANDATORY:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_ROUTER_MANDATORY is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_ROUTER_MANDATORY */
# ifdef ZMQ_PROBE_ROUTER

        case ZMQ_PROBE_ROUTER:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_PROBE_ROUTER is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_PROBE_ROUTER */
# ifdef ZMQ_REQ_RELAXED

        case ZMQ_REQ_RELAXED:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_REQ_RELAXED is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_REQ_RELAXED */
# ifdef ZMQ_REQ_CORRELATE

        case ZMQ_REQ_CORRELATE:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_REQ_CORRELATE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_REQ_CORRELATE */
# ifdef ZMQ_CONFLATE

        case ZMQ_CONFLATE:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_CONFLATE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_CONFLATE */
# ifdef ZMQ_ZAP_DOMAIN

        case ZMQ_ZAP_DOMAIN:
	        SOCKOPTS_GET_STRING(ZAP_DOMAIN, 255, 0)
        break;

# endif /* ZMQ_ZAP_DOMAIN */
# ifdef ZMQ_MECHANISM

        case ZMQ_MECHANISM:
	        SOCKOPTS_GET_INT(MECHANISM, int);
        break;

# endif /* ZMQ_MECHANISM */
# ifdef ZMQ_PLAIN_SERVER

        case ZMQ_PLAIN_SERVER:
	        SOCKOPTS_GET_INT(PLAIN_SERVER, int);
        break;

# endif /* ZMQ_PLAIN_SERVER */
# ifdef ZMQ_PLAIN_USERNAME

        case ZMQ_PLAIN_USERNAME:
	        SOCKOPTS_GET_STRING(PLAIN_USERNAME, 255, 0)
        break;

# endif /* ZMQ_PLAIN_USERNAME */
# ifdef ZMQ_PLAIN_PASSWORD

        case ZMQ_PLAIN_PASSWORD:
	        SOCKOPTS_GET_STRING(PLAIN_PASSWORD, 255, 0)
        break;

# endif /* ZMQ_PLAIN_PASSWORD */
# ifdef ZMQ_CURVE_SERVER

        case ZMQ_CURVE_SERVER:
	        SOCKOPTS_GET_INT(CURVE_SERVER, int);
        break;

# endif /* ZMQ_CURVE_SERVER */
# ifdef ZMQ_CURVE_PUBLICKEY

        case ZMQ_CURVE_PUBLICKEY:
	        SOCKOPTS_GET_STRING(CURVE_PUBLICKEY, 32, 1)
        break;

# endif /* ZMQ_CURVE_PUBLICKEY */
# ifdef ZMQ_CURVE_SECRETKEY

        case ZMQ_CURVE_SECRETKEY:
	        SOCKOPTS_GET_STRING(CURVE_SECRETKEY, 32, 1)
        break;

# endif /* ZMQ_CURVE_SECRETKEY */
# ifdef ZMQ_CURVE_SERVERKEY

        case ZMQ_CURVE_SERVERKEY:
	        SOCKOPTS_GET_STRING(CURVE_SERVERKEY, 32, 1)
        break;

# endif /* ZMQ_CURVE_SERVERKEY */
# ifdef ZMQ_GSSAPI_SERVER

        case ZMQ_GSSAPI_SERVER:
	        SOCKOPTS_GET_INT(GSSAPI_SERVER, int);
        break;

# endif /* ZMQ_GSSAPI_SERVER */
# ifdef ZMQ_GSSAPI_PLAINTEXT

        case ZMQ_GSSAPI_PLAINTEXT:
	        SOCKOPTS_GET_INT(GSSAPI_PLAINTEXT, int);
        break;

# endif /* ZMQ_GSSAPI_PLAINTEXT */
# ifdef ZMQ_GSSAPI_PRINCIPAL

        case ZMQ_GSSAPI_PRINCIPAL:
	        SOCKOPTS_GET_STRING(GSSAPI_PRINCIPAL, 255, 0)
        break;

# endif /* ZMQ_GSSAPI_PRINCIPAL */
# ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL

        case ZMQ_GSSAPI_SERVICE_PRINCIPAL:
	        SOCKOPTS_GET_STRING(GSSAPI_SERVICE_PRINCIPAL, 255, 0)
        break;

# endif /* ZMQ_GSSAPI_SERVICE_PRINCIPAL */
# ifdef ZMQ_IPV6

        case ZMQ_IPV6:
	        SOCKOPTS_GET_INT(IPV6, int);
        break;

# endif /* ZMQ_IPV6 */
# ifdef ZMQ_IMMEDIATE

        case ZMQ_IMMEDIATE:
	        SOCKOPTS_GET_INT(IMMEDIATE, int);
        break;

# endif /* ZMQ_IMMEDIATE */
    }


#endif /* ZMQ_VERSION_MAJOR == 4 */
#if (ZMQ_VERSION_MAJOR >= 3)

    switch (key) {
# ifdef ZMQ_SNDHWM

        case ZMQ_SNDHWM:
	        SOCKOPTS_GET_INT(SNDHWM, int);
        break;

# endif /* ZMQ_SNDHWM */
# ifdef ZMQ_RCVHWM

        case ZMQ_RCVHWM:
	        SOCKOPTS_GET_INT(RCVHWM, int);
        break;

# endif /* ZMQ_RCVHWM */
# ifdef ZMQ_MAXMSGSIZE

        case ZMQ_MAXMSGSIZE:
	        SOCKOPTS_GET_INT(MAXMSGSIZE, int64_t);
        break;

# endif /* ZMQ_MAXMSGSIZE */
# ifdef ZMQ_MULTICAST_HOPS

        case ZMQ_MULTICAST_HOPS:
	        SOCKOPTS_GET_INT(MULTICAST_HOPS, int);
        break;

# endif /* ZMQ_MULTICAST_HOPS */
# ifdef ZMQ_XPUB_VERBOSE

        case ZMQ_XPUB_VERBOSE:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_XPUB_VERBOSE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_XPUB_VERBOSE */
# ifdef ZMQ_TCP_KEEPALIVE

        case ZMQ_TCP_KEEPALIVE:
	        SOCKOPTS_GET_INT(TCP_KEEPALIVE, int);
        break;

# endif /* ZMQ_TCP_KEEPALIVE */
# ifdef ZMQ_TCP_KEEPALIVE_IDLE

        case ZMQ_TCP_KEEPALIVE_IDLE:
	        SOCKOPTS_GET_INT(TCP_KEEPALIVE_IDLE, int);
        break;

# endif /* ZMQ_TCP_KEEPALIVE_IDLE */
# ifdef ZMQ_TCP_KEEPALIVE_CNT

        case ZMQ_TCP_KEEPALIVE_CNT:
	        SOCKOPTS_GET_INT(TCP_KEEPALIVE_CNT, int);
        break;

# endif /* ZMQ_TCP_KEEPALIVE_CNT */
# ifdef ZMQ_TCP_KEEPALIVE_INTVL

        case ZMQ_TCP_KEEPALIVE_INTVL:
	        SOCKOPTS_GET_INT(TCP_KEEPALIVE_INTVL, int);
        break;

# endif /* ZMQ_TCP_KEEPALIVE_INTVL */
# ifdef ZMQ_TCP_ACCEPT_FILTER

        case ZMQ_TCP_ACCEPT_FILTER:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_TCP_ACCEPT_FILTER is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_TCP_ACCEPT_FILTER */
# ifdef ZMQ_LAST_ENDPOINT

        case ZMQ_LAST_ENDPOINT:
	        SOCKOPTS_GET_STRING(LAST_ENDPOINT, 255, 0)
        break;

# endif /* ZMQ_LAST_ENDPOINT */
# ifdef ZMQ_ROUTER_RAW

        case ZMQ_ROUTER_RAW:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_ROUTER_RAW is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_ROUTER_RAW */
# ifdef ZMQ_IPV4ONLY

        case ZMQ_IPV4ONLY:
	        SOCKOPTS_GET_INT(IPV4ONLY, int);
        break;

# endif /* ZMQ_IPV4ONLY */
    }


#endif /* ZMQ_VERSION_MAJOR == 3 */
#if (ZMQ_VERSION_MAJOR >= 2)

    switch (key) {
# ifdef ZMQ_HWM

        case ZMQ_HWM:
	        SOCKOPTS_GET_INT(HWM, uint64_t);
        break;

# endif /* ZMQ_HWM */
# ifdef ZMQ_SWAP

        case ZMQ_SWAP:
	        SOCKOPTS_GET_INT(SWAP, int64_t);
        break;

# endif /* ZMQ_SWAP */
# ifdef ZMQ_AFFINITY

        case ZMQ_AFFINITY:
	        SOCKOPTS_GET_INT(AFFINITY, uint64_t);
        break;

# endif /* ZMQ_AFFINITY */
# ifdef ZMQ_IDENTITY

        case ZMQ_IDENTITY:
{
        if (intern->socket->socket_type != ZMQ_REQ &&
            intern->socket->socket_type != ZMQ_REP &&
            intern->socket->socket_type != ZMQ_DEALER &&
            intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_IDENTITY is not valid for this socket type", errno);
            return;
        }
}
	        SOCKOPTS_GET_STRING(IDENTITY, 255, 1)
        break;

# endif /* ZMQ_IDENTITY */
# ifdef ZMQ_RATE

        case ZMQ_RATE:
# if ZMQ_VERSION_MAJOR < 3
	        SOCKOPTS_GET_INT(RATE, int64_t);
# else
	        SOCKOPTS_GET_INT(RATE, int);
# endif
        break;

# endif /* ZMQ_RATE */
# ifdef ZMQ_RECOVERY_IVL

        case ZMQ_RECOVERY_IVL:
# if ZMQ_VERSION_MAJOR < 3
	        SOCKOPTS_GET_INT(RECOVERY_IVL, int64_t);
# else
	        SOCKOPTS_GET_INT(RECOVERY_IVL, int);
# endif
        break;

# endif /* ZMQ_RECOVERY_IVL */
# ifdef ZMQ_RECOVERY_IVL_MSEC

        case ZMQ_RECOVERY_IVL_MSEC:
	        SOCKOPTS_GET_INT(RECOVERY_IVL_MSEC, int64_t);
        break;

# endif /* ZMQ_RECOVERY_IVL_MSEC */
# ifdef ZMQ_MCAST_LOOP

        case ZMQ_MCAST_LOOP:
	        SOCKOPTS_GET_INT(MCAST_LOOP, int64_t);
        break;

# endif /* ZMQ_MCAST_LOOP */
# ifdef ZMQ_RCVTIMEO

        case ZMQ_RCVTIMEO:
	        SOCKOPTS_GET_INT(RCVTIMEO, int);
        break;

# endif /* ZMQ_RCVTIMEO */
# ifdef ZMQ_SNDTIMEO

        case ZMQ_SNDTIMEO:
	        SOCKOPTS_GET_INT(SNDTIMEO, int);
        break;

# endif /* ZMQ_SNDTIMEO */
# ifdef ZMQ_SNDBUF

        case ZMQ_SNDBUF:
# if ZMQ_VERSION_MAJOR < 3
	        SOCKOPTS_GET_INT(SNDBUF, uint64_t);
# else
	        SOCKOPTS_GET_INT(SNDBUF, int);
# endif
        break;

# endif /* ZMQ_SNDBUF */
# ifdef ZMQ_RCVBUF

        case ZMQ_RCVBUF:
# if ZMQ_VERSION_MAJOR < 3
	        SOCKOPTS_GET_INT(RCVBUF, uint64_t);
# else
	        SOCKOPTS_GET_INT(RCVBUF, int);
# endif
        break;

# endif /* ZMQ_RCVBUF */
# ifdef ZMQ_LINGER

        case ZMQ_LINGER:
	        SOCKOPTS_GET_INT(LINGER, int);
        break;

# endif /* ZMQ_LINGER */
# ifdef ZMQ_RECONNECT_IVL

        case ZMQ_RECONNECT_IVL:
	        SOCKOPTS_GET_INT(RECONNECT_IVL, int);
        break;

# endif /* ZMQ_RECONNECT_IVL */
# ifdef ZMQ_RECONNECT_IVL_MAX

        case ZMQ_RECONNECT_IVL_MAX:
	        SOCKOPTS_GET_INT(RECONNECT_IVL_MAX, int);
        break;

# endif /* ZMQ_RECONNECT_IVL_MAX */
# ifdef ZMQ_BACKLOG

        case ZMQ_BACKLOG:
	        SOCKOPTS_GET_INT(BACKLOG, int);
        break;

# endif /* ZMQ_BACKLOG */
# ifdef ZMQ_SUBSCRIBE

        case ZMQ_SUBSCRIBE:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_SUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_SUBSCRIBE */
# ifdef ZMQ_UNSUBSCRIBE

        case ZMQ_UNSUBSCRIBE:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Getting ZMQ::SOCKOPT_UNSUBSCRIBE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ZMQ_UNSUBSCRIBE */
# ifdef ZMQ_TYPE

        case ZMQ_TYPE:
	        SOCKOPTS_GET_INT(TYPE, int);
        break;

# endif /* ZMQ_TYPE */
# ifdef ZMQ_RCVMORE

        case ZMQ_RCVMORE:
# if ZMQ_VERSION_MAJOR < 3
	        SOCKOPTS_GET_INT(RCVMORE, int64_t);
# else
	        SOCKOPTS_GET_INT(RCVMORE, int);
# endif
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
# if ZMQ_VERSION_MAJOR < 3
	        SOCKOPTS_GET_INT(EVENTS, uint32_t);
# else
	        SOCKOPTS_GET_INT(EVENTS, int);
# endif
        break;

# endif /* ZMQ_EVENTS */
    }


#endif /* ZMQ_VERSION_MAJOR == 2 */

    zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), PHP_ZMQ_INTERNAL_ERROR, "Unknown option key %ld", key);
    return;
}
/* }}} */

/* {{{ proto ZMQSocket ZMQSocket::setSockOpt(integer $SOCKOPT, mixed $value)
    Set a socket option
*/
PHP_METHOD(zmqsocket, setsockopt)
{
    php_zmq_socket_object *intern;
    zend_long key;
    zval *zv;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lz/", &key, &zv) == FAILURE) {
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

#if (ZMQ_VERSION_MAJOR >= 4)
#   if (ZMQ_VERSION_MINOR >= 3)

    switch (key) {

# ifdef ZMQ_ONLY_FIRST_SUBSCRIBE
        case ZMQ_ONLY_FIRST_SUBSCRIBE:
{
        if (intern->socket->socket_type != ZMQ_XPUB &&
            intern->socket->socket_type != ZMQ_XSUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_ONLY_FIRST_SUBSCRIBE is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(ONLY_FIRST_SUBSCRIBE, int)
        break;

# endif /* ifdef ZMQ_ONLY_FIRST_SUBSCRIBE */

# ifdef ZMQ_WSS_TRUST_SYSTEM
        case ZMQ_WSS_TRUST_SYSTEM:
			SOCKOPTS_SET_INT(WSS_TRUST_SYSTEM, int)
        break;

# endif /* ifdef ZMQ_WSS_TRUST_SYSTEM */

# ifdef ZMQ_WSS_HOSTNAME
        case ZMQ_WSS_HOSTNAME:
                SOCKOPTS_SET_STRING(WSS_HOSTNAME)

        break;

# endif /* ifdef ZMQ_WSS_HOSTNAME */

# ifdef ZMQ_WSS_TRUST_PEM
        case ZMQ_WSS_TRUST_PEM:
                SOCKOPTS_SET_STRING(WSS_TRUST_PEM)

        break;

# endif /* ifdef ZMQ_WSS_TRUST_PEM */

# ifdef ZMQ_WSS_CERT_PEM
        case ZMQ_WSS_CERT_PEM:
                SOCKOPTS_SET_STRING(WSS_CERT_PEM)

        break;

# endif /* ifdef ZMQ_WSS_CERT_PEM */

# ifdef ZMQ_WSS_KEY_PEM
        case ZMQ_WSS_KEY_PEM:
                SOCKOPTS_SET_STRING(WSS_KEY_PEM)

        break;

# endif /* ifdef ZMQ_WSS_KEY_PEM */

# ifdef ZMQ_OUT_BATCH_SIZE
        case ZMQ_OUT_BATCH_SIZE:
			SOCKOPTS_SET_INT(OUT_BATCH_SIZE, int)
        break;

# endif /* ifdef ZMQ_OUT_BATCH_SIZE */

# ifdef ZMQ_IN_BATCH_SIZE
        case ZMQ_IN_BATCH_SIZE:
			SOCKOPTS_SET_INT(IN_BATCH_SIZE, int)
        break;

# endif /* ifdef ZMQ_IN_BATCH_SIZE */

# ifdef ZMQ_SOCKS_PASSWORD
        case ZMQ_SOCKS_PASSWORD:
                SOCKOPTS_SET_STRING(SOCKS_PASSWORD)

        break;

# endif /* ifdef ZMQ_SOCKS_PASSWORD */

# ifdef ZMQ_SOCKS_USERNAME
        case ZMQ_SOCKS_USERNAME:
                SOCKOPTS_SET_STRING(SOCKS_USERNAME)

        break;

# endif /* ifdef ZMQ_SOCKS_USERNAME */

# ifdef ZMQ_XPUB_MANUAL_LAST_VALUE
        case ZMQ_XPUB_MANUAL_LAST_VALUE:
{
        if (intern->socket->socket_type != ZMQ_XPUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_XPUB_MANUAL_LAST_VALUE is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(XPUB_MANUAL_LAST_VALUE, int)
        break;

# endif /* ifdef ZMQ_XPUB_MANUAL_LAST_VALUE */

# ifdef ZMQ_ROUTER_NOTIFY
        case ZMQ_ROUTER_NOTIFY:
			SOCKOPTS_SET_INT(ROUTER_NOTIFY, int)
        break;

# endif /* ifdef ZMQ_ROUTER_NOTIFY */

# ifdef ZMQ_MULTICAST_LOOP
        case ZMQ_MULTICAST_LOOP:
			SOCKOPTS_SET_INT(MULTICAST_LOOP, int)
        break;

# endif /* ifdef ZMQ_MULTICAST_LOOP */

# ifdef ZMQ_METADATA
        case ZMQ_METADATA:
                SOCKOPTS_SET_STRING(METADATA)

        break;

# endif /* ifdef ZMQ_METADATA */

# ifdef ZMQ_LOOPBACK_FASTPATH
        case ZMQ_LOOPBACK_FASTPATH:
			SOCKOPTS_SET_INT(LOOPBACK_FASTPATH, int)
        break;

# endif /* ifdef ZMQ_LOOPBACK_FASTPATH */

# ifdef ZMQ_ZAP_ENFORCE_DOMAIN
        case ZMQ_ZAP_ENFORCE_DOMAIN:
			SOCKOPTS_SET_INT(ZAP_ENFORCE_DOMAIN, int)
        break;

# endif /* ifdef ZMQ_ZAP_ENFORCE_DOMAIN */

# ifdef ZMQ_GSSAPI_PRINCIPAL_NAMETYPE
        case ZMQ_GSSAPI_PRINCIPAL_NAMETYPE:
			SOCKOPTS_SET_INT(GSSAPI_PRINCIPAL_NAMETYPE, int)
        break;

# endif /* ifdef ZMQ_GSSAPI_PRINCIPAL_NAMETYPE */

# ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE
        case ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE:
			SOCKOPTS_SET_INT(GSSAPI_SERVICE_PRINCIPAL_NAMETYPE, int)
        break;

# endif /* ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE */

# ifdef ZMQ_BINDTODEVICE
        case ZMQ_BINDTODEVICE:
                SOCKOPTS_SET_STRING(BINDTODEVICE)

        break;

# endif /* ifdef ZMQ_BINDTODEVICE */

    }
# endif

#endif /* ZMQ_VERSION_MAJOR == 4 */
#if (ZMQ_VERSION_MAJOR >= 4)
#   if (ZMQ_VERSION_MINOR >= 2)

    switch (key) {

# ifdef ZMQ_HEARTBEAT_IVL
        case ZMQ_HEARTBEAT_IVL:
			SOCKOPTS_SET_INT(HEARTBEAT_IVL, int)
        break;

# endif /* ifdef ZMQ_HEARTBEAT_IVL */

# ifdef ZMQ_HEARTBEAT_TTL
        case ZMQ_HEARTBEAT_TTL:
			SOCKOPTS_SET_INT(HEARTBEAT_TTL, int)
        break;

# endif /* ifdef ZMQ_HEARTBEAT_TTL */

# ifdef ZMQ_HEARTBEAT_TIMEOUT
        case ZMQ_HEARTBEAT_TIMEOUT:
			SOCKOPTS_SET_INT(HEARTBEAT_TIMEOUT, int)
        break;

# endif /* ifdef ZMQ_HEARTBEAT_TIMEOUT */

# ifdef ZMQ_USE_FD
        case ZMQ_USE_FD:
			SOCKOPTS_SET_INT(USE_FD, int)
        break;

# endif /* ifdef ZMQ_USE_FD */

# ifdef ZMQ_XPUB_MANUAL
        case ZMQ_XPUB_MANUAL:
{
        if (intern->socket->socket_type != ZMQ_XPUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_XPUB_MANUAL is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(XPUB_MANUAL, int)
        break;

# endif /* ifdef ZMQ_XPUB_MANUAL */

# ifdef ZMQ_XPUB_WELCOME_MSG
        case ZMQ_XPUB_WELCOME_MSG:
{
        if (intern->socket->socket_type != ZMQ_XPUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_XPUB_WELCOME_MSG is not valid for this socket type", errno);
            return;
        }
}
                SOCKOPTS_SET_STRING(XPUB_WELCOME_MSG)

        break;

# endif /* ifdef ZMQ_XPUB_WELCOME_MSG */

# ifdef ZMQ_STREAM_NOTIFY
        case ZMQ_STREAM_NOTIFY:
{
        if (intern->socket->socket_type != ZMQ_STREAM) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_STREAM_NOTIFY is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(STREAM_NOTIFY, int)
        break;

# endif /* ifdef ZMQ_STREAM_NOTIFY */

# ifdef ZMQ_INVERT_MATCHING
        case ZMQ_INVERT_MATCHING:
{
        if (intern->socket->socket_type != ZMQ_XPUB &&
            intern->socket->socket_type != ZMQ_PUB &&
            intern->socket->socket_type != ZMQ_SUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_INVERT_MATCHING is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(INVERT_MATCHING, int)
        break;

# endif /* ifdef ZMQ_INVERT_MATCHING */

# ifdef ZMQ_XPUB_VERBOSER
        case ZMQ_XPUB_VERBOSER:
{
        if (intern->socket->socket_type != ZMQ_XPUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_XPUB_VERBOSER is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(XPUB_VERBOSER, int)
        break;

# endif /* ifdef ZMQ_XPUB_VERBOSER */

# ifdef ZMQ_CONNECT_TIMEOUT
        case ZMQ_CONNECT_TIMEOUT:
			SOCKOPTS_SET_INT(CONNECT_TIMEOUT, int)
        break;

# endif /* ifdef ZMQ_CONNECT_TIMEOUT */

# ifdef ZMQ_TCP_MAXRT
        case ZMQ_TCP_MAXRT:
			SOCKOPTS_SET_INT(TCP_MAXRT, int)
        break;

# endif /* ifdef ZMQ_TCP_MAXRT */

# ifdef ZMQ_THREAD_SAFE
        case ZMQ_THREAD_SAFE:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_THREAD_SAFE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ifdef ZMQ_THREAD_SAFE */

# ifdef ZMQ_MULTICAST_MAXTPDU
        case ZMQ_MULTICAST_MAXTPDU:
			SOCKOPTS_SET_INT(MULTICAST_MAXTPDU, int)
        break;

# endif /* ifdef ZMQ_MULTICAST_MAXTPDU */

# ifdef ZMQ_VMCI_BUFFER_SIZE
        case ZMQ_VMCI_BUFFER_SIZE:
			SOCKOPTS_SET_INT(VMCI_BUFFER_SIZE, uint64_t)
        break;

# endif /* ifdef ZMQ_VMCI_BUFFER_SIZE */

# ifdef ZMQ_VMCI_BUFFER_MIN_SIZE
        case ZMQ_VMCI_BUFFER_MIN_SIZE:
			SOCKOPTS_SET_INT(VMCI_BUFFER_MIN_SIZE, uint64_t)
        break;

# endif /* ifdef ZMQ_VMCI_BUFFER_MIN_SIZE */

# ifdef ZMQ_VMCI_BUFFER_MAX_SIZE
        case ZMQ_VMCI_BUFFER_MAX_SIZE:
			SOCKOPTS_SET_INT(VMCI_BUFFER_MAX_SIZE, uint64_t)
        break;

# endif /* ifdef ZMQ_VMCI_BUFFER_MAX_SIZE */

# ifdef ZMQ_VMCI_CONNECT_TIMEOUT
        case ZMQ_VMCI_CONNECT_TIMEOUT:
			SOCKOPTS_SET_INT(VMCI_CONNECT_TIMEOUT, int)
        break;

# endif /* ifdef ZMQ_VMCI_CONNECT_TIMEOUT */

    }
# endif

#endif /* ZMQ_VERSION_MAJOR == 4 */
#if (ZMQ_VERSION_MAJOR >= 4)
#   if (ZMQ_VERSION_MINOR >= 1)

    switch (key) {

# ifdef ZMQ_TOS
        case ZMQ_TOS:
			SOCKOPTS_SET_INT(TOS, int)
        break;

# endif /* ifdef ZMQ_TOS */

# ifdef ZMQ_ROUTER_HANDOVER
        case ZMQ_ROUTER_HANDOVER:
{
        if (intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_ROUTER_HANDOVER is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(ROUTER_HANDOVER, int)
        break;

# endif /* ifdef ZMQ_ROUTER_HANDOVER */

# ifdef ZMQ_CONNECT_RID
        case ZMQ_CONNECT_RID:
{
        if (intern->socket->socket_type != ZMQ_ROUTER &&
            intern->socket->socket_type != ZMQ_STREAM) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_CONNECT_RID is not valid for this socket type", errno);
            return;
        }
}
                SOCKOPTS_SET_STRING(CONNECT_RID)

        break;

# endif /* ifdef ZMQ_CONNECT_RID */

# ifdef ZMQ_HANDSHAKE_IVL
        case ZMQ_HANDSHAKE_IVL:
			SOCKOPTS_SET_INT(HANDSHAKE_IVL, int)
        break;

# endif /* ifdef ZMQ_HANDSHAKE_IVL */

# ifdef ZMQ_SOCKS_PROXY
        case ZMQ_SOCKS_PROXY:
                SOCKOPTS_SET_STRING(SOCKS_PROXY)

        break;

# endif /* ifdef ZMQ_SOCKS_PROXY */

# ifdef ZMQ_XPUB_NODROP
        case ZMQ_XPUB_NODROP:
{
        if (intern->socket->socket_type != ZMQ_XPUB &&
            intern->socket->socket_type != ZMQ_PUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_XPUB_NODROP is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(XPUB_NODROP, int)
        break;

# endif /* ifdef ZMQ_XPUB_NODROP */

    }
# endif

#endif /* ZMQ_VERSION_MAJOR == 4 */
#if (ZMQ_VERSION_MAJOR >= 4)

    switch (key) {

# ifdef ZMQ_ROUTER_MANDATORY
        case ZMQ_ROUTER_MANDATORY:
{
        if (intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_ROUTER_MANDATORY is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(ROUTER_MANDATORY, int)
        break;

# endif /* ifdef ZMQ_ROUTER_MANDATORY */

# ifdef ZMQ_PROBE_ROUTER
        case ZMQ_PROBE_ROUTER:
{
        if (intern->socket->socket_type != ZMQ_ROUTER &&
            intern->socket->socket_type != ZMQ_DEALER &&
            intern->socket->socket_type != ZMQ_REQ) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_PROBE_ROUTER is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(PROBE_ROUTER, int)
        break;

# endif /* ifdef ZMQ_PROBE_ROUTER */

# ifdef ZMQ_REQ_RELAXED
        case ZMQ_REQ_RELAXED:
{
        if (intern->socket->socket_type != ZMQ_REQ) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_REQ_RELAXED is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(REQ_RELAXED, int)
        break;

# endif /* ifdef ZMQ_REQ_RELAXED */

# ifdef ZMQ_REQ_CORRELATE
        case ZMQ_REQ_CORRELATE:
{
        if (intern->socket->socket_type != ZMQ_REQ) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_REQ_CORRELATE is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(REQ_CORRELATE, int)
        break;

# endif /* ifdef ZMQ_REQ_CORRELATE */

# ifdef ZMQ_CONFLATE
        case ZMQ_CONFLATE:
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
			SOCKOPTS_SET_INT(CONFLATE, int)
        break;

# endif /* ifdef ZMQ_CONFLATE */

# ifdef ZMQ_ZAP_DOMAIN
        case ZMQ_ZAP_DOMAIN:
                SOCKOPTS_SET_STRING(ZAP_DOMAIN)

        break;

# endif /* ifdef ZMQ_ZAP_DOMAIN */

# ifdef ZMQ_MECHANISM
        case ZMQ_MECHANISM:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_MECHANISM is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ifdef ZMQ_MECHANISM */

# ifdef ZMQ_PLAIN_SERVER
        case ZMQ_PLAIN_SERVER:
			SOCKOPTS_SET_INT(PLAIN_SERVER, int)
        break;

# endif /* ifdef ZMQ_PLAIN_SERVER */

# ifdef ZMQ_PLAIN_USERNAME
        case ZMQ_PLAIN_USERNAME:
                SOCKOPTS_SET_STRING(PLAIN_USERNAME)

        break;

# endif /* ifdef ZMQ_PLAIN_USERNAME */

# ifdef ZMQ_PLAIN_PASSWORD
        case ZMQ_PLAIN_PASSWORD:
                SOCKOPTS_SET_STRING(PLAIN_PASSWORD)

        break;

# endif /* ifdef ZMQ_PLAIN_PASSWORD */

# ifdef ZMQ_CURVE_SERVER
        case ZMQ_CURVE_SERVER:
			SOCKOPTS_SET_INT(CURVE_SERVER, int)
        break;

# endif /* ifdef ZMQ_CURVE_SERVER */

# ifdef ZMQ_CURVE_PUBLICKEY
        case ZMQ_CURVE_PUBLICKEY:
                SOCKOPTS_SET_STRING(CURVE_PUBLICKEY)

        break;

# endif /* ifdef ZMQ_CURVE_PUBLICKEY */

# ifdef ZMQ_CURVE_SECRETKEY
        case ZMQ_CURVE_SECRETKEY:
                SOCKOPTS_SET_STRING(CURVE_SECRETKEY)

        break;

# endif /* ifdef ZMQ_CURVE_SECRETKEY */

# ifdef ZMQ_CURVE_SERVERKEY
        case ZMQ_CURVE_SERVERKEY:
                SOCKOPTS_SET_STRING(CURVE_SERVERKEY)

        break;

# endif /* ifdef ZMQ_CURVE_SERVERKEY */

# ifdef ZMQ_GSSAPI_SERVER
        case ZMQ_GSSAPI_SERVER:
			SOCKOPTS_SET_INT(GSSAPI_SERVER, int)
        break;

# endif /* ifdef ZMQ_GSSAPI_SERVER */

# ifdef ZMQ_GSSAPI_PLAINTEXT
        case ZMQ_GSSAPI_PLAINTEXT:
			SOCKOPTS_SET_INT(GSSAPI_PLAINTEXT, int)
        break;

# endif /* ifdef ZMQ_GSSAPI_PLAINTEXT */

# ifdef ZMQ_GSSAPI_PRINCIPAL
        case ZMQ_GSSAPI_PRINCIPAL:
                SOCKOPTS_SET_STRING(GSSAPI_PRINCIPAL)

        break;

# endif /* ifdef ZMQ_GSSAPI_PRINCIPAL */

# ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL
        case ZMQ_GSSAPI_SERVICE_PRINCIPAL:
                SOCKOPTS_SET_STRING(GSSAPI_SERVICE_PRINCIPAL)

        break;

# endif /* ifdef ZMQ_GSSAPI_SERVICE_PRINCIPAL */

# ifdef ZMQ_IPV6
        case ZMQ_IPV6:
			SOCKOPTS_SET_INT(IPV6, int)
        break;

# endif /* ifdef ZMQ_IPV6 */

# ifdef ZMQ_IMMEDIATE
        case ZMQ_IMMEDIATE:
			SOCKOPTS_SET_INT(IMMEDIATE, int)
        break;

# endif /* ifdef ZMQ_IMMEDIATE */

    }

#endif /* ZMQ_VERSION_MAJOR == 4 */
#if (ZMQ_VERSION_MAJOR >= 3)

    switch (key) {

# ifdef ZMQ_SNDHWM
        case ZMQ_SNDHWM:
			SOCKOPTS_SET_INT(SNDHWM, int)
        break;

# endif /* ifdef ZMQ_SNDHWM */

# ifdef ZMQ_RCVHWM
        case ZMQ_RCVHWM:
			SOCKOPTS_SET_INT(RCVHWM, int)
        break;

# endif /* ifdef ZMQ_RCVHWM */

# ifdef ZMQ_MAXMSGSIZE
        case ZMQ_MAXMSGSIZE:
			SOCKOPTS_SET_INT(MAXMSGSIZE, int64_t)
        break;

# endif /* ifdef ZMQ_MAXMSGSIZE */

# ifdef ZMQ_MULTICAST_HOPS
        case ZMQ_MULTICAST_HOPS:
			SOCKOPTS_SET_INT(MULTICAST_HOPS, int)
        break;

# endif /* ifdef ZMQ_MULTICAST_HOPS */

# ifdef ZMQ_XPUB_VERBOSE
        case ZMQ_XPUB_VERBOSE:
{
        if (intern->socket->socket_type != ZMQ_XPUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_XPUB_VERBOSE is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(XPUB_VERBOSE, int)
        break;

# endif /* ifdef ZMQ_XPUB_VERBOSE */

# ifdef ZMQ_TCP_KEEPALIVE
        case ZMQ_TCP_KEEPALIVE:
			SOCKOPTS_SET_INT(TCP_KEEPALIVE, int)
        break;

# endif /* ifdef ZMQ_TCP_KEEPALIVE */

# ifdef ZMQ_TCP_KEEPALIVE_IDLE
        case ZMQ_TCP_KEEPALIVE_IDLE:
			SOCKOPTS_SET_INT(TCP_KEEPALIVE_IDLE, int)
        break;

# endif /* ifdef ZMQ_TCP_KEEPALIVE_IDLE */

# ifdef ZMQ_TCP_KEEPALIVE_CNT
        case ZMQ_TCP_KEEPALIVE_CNT:
			SOCKOPTS_SET_INT(TCP_KEEPALIVE_CNT, int)
        break;

# endif /* ifdef ZMQ_TCP_KEEPALIVE_CNT */

# ifdef ZMQ_TCP_KEEPALIVE_INTVL
        case ZMQ_TCP_KEEPALIVE_INTVL:
			SOCKOPTS_SET_INT(TCP_KEEPALIVE_INTVL, int)
        break;

# endif /* ifdef ZMQ_TCP_KEEPALIVE_INTVL */

# ifdef ZMQ_TCP_ACCEPT_FILTER
        case ZMQ_TCP_ACCEPT_FILTER:
                SOCKOPTS_SET_STRING(TCP_ACCEPT_FILTER)

        break;

# endif /* ifdef ZMQ_TCP_ACCEPT_FILTER */

# ifdef ZMQ_LAST_ENDPOINT
        case ZMQ_LAST_ENDPOINT:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_LAST_ENDPOINT is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ifdef ZMQ_LAST_ENDPOINT */

# ifdef ZMQ_ROUTER_RAW
        case ZMQ_ROUTER_RAW:
{
        if (intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_ROUTER_RAW is not valid for this socket type", errno);
            return;
        }
}
			SOCKOPTS_SET_INT(ROUTER_RAW, int)
        break;

# endif /* ifdef ZMQ_ROUTER_RAW */

# ifdef ZMQ_IPV4ONLY
        case ZMQ_IPV4ONLY:
			SOCKOPTS_SET_INT(IPV4ONLY, int)
        break;

# endif /* ifdef ZMQ_IPV4ONLY */

    }

#endif /* ZMQ_VERSION_MAJOR == 3 */
#if (ZMQ_VERSION_MAJOR >= 2)

    switch (key) {

# ifdef ZMQ_HWM
        case ZMQ_HWM:
			SOCKOPTS_SET_INT(HWM, uint64_t)
        break;

# endif /* ifdef ZMQ_HWM */

# ifdef ZMQ_SWAP
        case ZMQ_SWAP:
			SOCKOPTS_SET_INT(SWAP, int64_t)
        break;

# endif /* ifdef ZMQ_SWAP */

# ifdef ZMQ_AFFINITY
        case ZMQ_AFFINITY:
			SOCKOPTS_SET_INT(AFFINITY, uint64_t)
        break;

# endif /* ifdef ZMQ_AFFINITY */

# ifdef ZMQ_IDENTITY
        case ZMQ_IDENTITY:
{
        if (intern->socket->socket_type != ZMQ_REQ &&
            intern->socket->socket_type != ZMQ_REP &&
            intern->socket->socket_type != ZMQ_DEALER &&
            intern->socket->socket_type != ZMQ_ROUTER) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_IDENTITY is not valid for this socket type", errno);
            return;
        }
}
                SOCKOPTS_SET_STRING(IDENTITY)

        break;

# endif /* ifdef ZMQ_IDENTITY */

# ifdef ZMQ_RATE
        case ZMQ_RATE:
# if ZMQ_VERSION_MAJOR < 3
			SOCKOPTS_SET_INT(RATE, int64_t)
# else
			SOCKOPTS_SET_INT(RATE, int)
# endif
        break;

# endif /* ifdef ZMQ_RATE */

# ifdef ZMQ_RECOVERY_IVL
        case ZMQ_RECOVERY_IVL:
# if ZMQ_VERSION_MAJOR < 3
			SOCKOPTS_SET_INT(RECOVERY_IVL, int64_t)
# else
			SOCKOPTS_SET_INT(RECOVERY_IVL, int)
# endif
        break;

# endif /* ifdef ZMQ_RECOVERY_IVL */

# ifdef ZMQ_RECOVERY_IVL_MSEC
        case ZMQ_RECOVERY_IVL_MSEC:
			SOCKOPTS_SET_INT(RECOVERY_IVL_MSEC, int64_t)
        break;

# endif /* ifdef ZMQ_RECOVERY_IVL_MSEC */

# ifdef ZMQ_MCAST_LOOP
        case ZMQ_MCAST_LOOP:
			SOCKOPTS_SET_INT(MCAST_LOOP, int64_t)
        break;

# endif /* ifdef ZMQ_MCAST_LOOP */

# ifdef ZMQ_RCVTIMEO
        case ZMQ_RCVTIMEO:
			SOCKOPTS_SET_INT(RCVTIMEO, int)
        break;

# endif /* ifdef ZMQ_RCVTIMEO */

# ifdef ZMQ_SNDTIMEO
        case ZMQ_SNDTIMEO:
			SOCKOPTS_SET_INT(SNDTIMEO, int)
        break;

# endif /* ifdef ZMQ_SNDTIMEO */

# ifdef ZMQ_SNDBUF
        case ZMQ_SNDBUF:
# if ZMQ_VERSION_MAJOR < 3
			SOCKOPTS_SET_INT(SNDBUF, uint64_t)
# else
			SOCKOPTS_SET_INT(SNDBUF, int)
# endif
        break;

# endif /* ifdef ZMQ_SNDBUF */

# ifdef ZMQ_RCVBUF
        case ZMQ_RCVBUF:
# if ZMQ_VERSION_MAJOR < 3
			SOCKOPTS_SET_INT(RCVBUF, uint64_t)
# else
			SOCKOPTS_SET_INT(RCVBUF, int)
# endif
        break;

# endif /* ifdef ZMQ_RCVBUF */

# ifdef ZMQ_LINGER
        case ZMQ_LINGER:
			SOCKOPTS_SET_INT(LINGER, int)
        break;

# endif /* ifdef ZMQ_LINGER */

# ifdef ZMQ_RECONNECT_IVL
        case ZMQ_RECONNECT_IVL:
			SOCKOPTS_SET_INT(RECONNECT_IVL, int)
        break;

# endif /* ifdef ZMQ_RECONNECT_IVL */

# ifdef ZMQ_RECONNECT_IVL_MAX
        case ZMQ_RECONNECT_IVL_MAX:
			SOCKOPTS_SET_INT(RECONNECT_IVL_MAX, int)
        break;

# endif /* ifdef ZMQ_RECONNECT_IVL_MAX */

# ifdef ZMQ_BACKLOG
        case ZMQ_BACKLOG:
			SOCKOPTS_SET_INT(BACKLOG, int)
        break;

# endif /* ifdef ZMQ_BACKLOG */

# ifdef ZMQ_SUBSCRIBE
        case ZMQ_SUBSCRIBE:
{
        if (intern->socket->socket_type != ZMQ_SUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_SUBSCRIBE is not valid for this socket type", errno);
            return;
        }
}
                SOCKOPTS_SET_STRING(SUBSCRIBE)

        break;

# endif /* ifdef ZMQ_SUBSCRIBE */

# ifdef ZMQ_UNSUBSCRIBE
        case ZMQ_UNSUBSCRIBE:
{
        if (intern->socket->socket_type != ZMQ_SUB) {
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "ZMQ::SOCKOPT_UNSUBSCRIBE is not valid for this socket type", errno);
            return;
        }
}
                SOCKOPTS_SET_STRING(UNSUBSCRIBE)

        break;

# endif /* ifdef ZMQ_UNSUBSCRIBE */

# ifdef ZMQ_TYPE
        case ZMQ_TYPE:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_TYPE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ifdef ZMQ_TYPE */

# ifdef ZMQ_RCVMORE
        case ZMQ_RCVMORE:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_RCVMORE is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ifdef ZMQ_RCVMORE */

# ifdef ZMQ_FD
        case ZMQ_FD:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_FD is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ifdef ZMQ_FD */

# ifdef ZMQ_EVENTS
        case ZMQ_EVENTS:
            zend_throw_exception(php_zmq_socket_exception_sc_entry_get (), "Setting ZMQ::SOCKOPT_EVENTS is not supported", PHP_ZMQ_INTERNAL_ERROR);
            return;
        break;

# endif /* ifdef ZMQ_EVENTS */

    }

#endif /* ZMQ_VERSION_MAJOR == 2 */

    zend_throw_exception_ex(php_zmq_socket_exception_sc_entry_get (), PHP_ZMQ_INTERNAL_ERROR, "Unknown option key %ld", key);
    return;
}
/* }}} */


