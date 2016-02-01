<?php
/**
 * zmq-API v@PACKAGE_VERSION@ Docs build by DocThor [2016-02-01]
 * @package zmq
 */

/**
 * @package zmq
 */
class ZMQ {
	const SOCKET_PAIR = 0;
	const SOCKET_PUB = 1;
	const SOCKET_SUB = 2;
	const SOCKET_REQ = 3;
	const SOCKET_REP = 4;
	const SOCKET_XREQ = 5;
	const SOCKET_XREP = 6;
	const SOCKET_PUSH = 8;
	const SOCKET_PULL = 7;
	const SOCKET_DEALER = 5;
	const SOCKET_ROUTER = 6;
	const SOCKET_XSUB = 10;
	const SOCKET_XPUB = 9;
	const SOCKET_STREAM = 11;
	const SOCKET_UPSTREAM = 7;
	const SOCKET_DOWNSTREAM = 8;
	const POLL_IN = 1;
	const POLL_OUT = 2;
	const MODE_SNDMORE = 2;
	const MODE_NOBLOCK = 1;
	const MODE_DONTWAIT = 1;
	const ERR_INTERNAL = -99;
	const ERR_EAGAIN = 35;
	const ERR_ENOTSUP = 45;
	const ERR_EFSM = 156384763;
	const ERR_ETERM = 156384765;
	const LIBZMQ_VER = '4.1.4';
	const LIBZMQ_VERSION = '4.1.4';
	const LIBZMQ_VERSION_ID = 40104;
	const LIBZMQ_VERSION_MAJOR = 4;
	const LIBZMQ_VERSION_MINOR = 1;
	const LIBZMQ_VERSION_PATCH = 4;
	const SOCKOPT_TOS = 57;
	const SOCKOPT_ROUTER_HANDOVER = 56;
	const SOCKOPT_ROUTER_MANDATORY = 33;
	const SOCKOPT_PROBE_ROUTER = 51;
	const SOCKOPT_REQ_RELAXED = 53;
	const SOCKOPT_REQ_CORRELATE = 52;
	const SOCKOPT_CONFLATE = 54;
	const SOCKOPT_ZAP_DOMAIN = 55;
	const SOCKOPT_MECHANISM = 43;
	const SOCKOPT_PLAIN_SERVER = 44;
	const SOCKOPT_PLAIN_USERNAME = 45;
	const SOCKOPT_PLAIN_PASSWORD = 46;
	const SOCKOPT_CURVE_SERVER = 47;
	const SOCKOPT_CURVE_PUBLICKEY = 48;
	const SOCKOPT_CURVE_SECRETKEY = 49;
	const SOCKOPT_CURVE_SERVERKEY = 50;
	const SOCKOPT_GSSAPI_SERVER = 62;
	const SOCKOPT_GSSAPI_PLAINTEXT = 65;
	const SOCKOPT_GSSAPI_PRINCIPAL = 63;
	const SOCKOPT_GSSAPI_SERVICE_PRINCIPAL = 64;
	const SOCKOPT_IPV6 = 42;
	const SOCKOPT_IMMEDIATE = 39;
	const SOCKOPT_ROUTER_RAW = 41;
	const SOCKOPT_IPV4ONLY = 31;
	const SOCKOPT_DELAY_ATTACH_ON_CONNECT = 39;
	const SOCKOPT_TYPE = 16;
	const SOCKOPT_SNDHWM = 23;
	const SOCKOPT_RCVHWM = 24;
	const SOCKOPT_AFFINITY = 4;
	const SOCKOPT_SUBSCRIBE = 6;
	const SOCKOPT_UNSUBSCRIBE = 7;
	const SOCKOPT_IDENTITY = 5;
	const SOCKOPT_RATE = 8;
	const SOCKOPT_RECOVERY_IVL = 9;
	const SOCKOPT_SNDBUF = 11;
	const SOCKOPT_RCVBUF = 12;
	const SOCKOPT_LINGER = 17;
	const SOCKOPT_RECONNECT_IVL = 18;
	const SOCKOPT_RECONNECT_IVL_MAX = 21;
	const SOCKOPT_BACKLOG = 19;
	const SOCKOPT_MAXMSGSIZE = 22;
	const SOCKOPT_MULTICAST_HOPS = 25;
	const SOCKOPT_RCVTIMEO = 27;
	const SOCKOPT_SNDTIMEO = 28;
	const SOCKOPT_XPUB_VERBOSE = 40;
	const SOCKOPT_TCP_KEEPALIVE = 34;
	const SOCKOPT_TCP_KEEPALIVE_IDLE = 36;
	const SOCKOPT_TCP_KEEPALIVE_CNT = 35;
	const SOCKOPT_TCP_KEEPALIVE_INTVL = 37;
	const SOCKOPT_TCP_ACCEPT_FILTER = 38;
	const SOCKOPT_RCVMORE = 13;
	const SOCKOPT_FD = 14;
	const SOCKOPT_EVENTS = 15;
	const SOCKOPT_LAST_ENDPOINT = 32;
	const SOCKOPT_HWM = 2001;
	const CTXOPT_MAX_SOCKETS = 2;
	const CTXOPT_MAX_SOCKETS_DEFAULT = 1023;
	const EVENT_CONNECTED = 1;
	const EVENT_CONNECT_DELAYED = 2;
	const EVENT_CONNECT_RETRIED = 4;
	const EVENT_LISTENING = 8;
	const EVENT_BIND_FAILED = 16;
	const EVENT_ACCEPTED = 32;
	const EVENT_ACCEPT_FAILED = 64;
	const EVENT_CLOSED = 128;
	const EVENT_CLOSE_FAILED = 256;
	const EVENT_DISCONNECTED = 512;
	const EVENT_MONITOR_STOPPED = 1024;
	const EVENT_ALL = 65535;
	public function clock() {}
	public function z85encode($data) {}
	public function z85decode($data) {}
	public function curvekeypair() {}
}
/**
 * @package zmq
 */
class ZMQContext {
	public function __construct($io_threads = 1, $persistent = true) {}
	public function acquire() {}
	public function getsocketcount() {}
	public function getsocket($type, $dsn, $on_new_socket="") {}
	public function ispersistent() {}
	public function setOpt($option, $value) {}
	public function getOpt($option) {}
}
/**
 * @package zmq
 */
class ZMQSocket {
	public function __construct(ZMQContext $ZMQContext, $type, $persistent_id=null, $on_new_socket=null) {}
	public function send($message, $mode=0) {}
	public function recv($mode="") {}
	public function sendmulti($message, $mode=0) {}
	public function recvmulti($mode=0) {}
	public function bind($dsn, $force=false) {}
	public function connect($dsn, $force=false) {}
	public function monitor($dsn, $events=ZMQ::EVENT_ALL) {}
	public function recvevent($flags=0) {}
	public function unbind($dsn) {}
	public function disconnect($dsn) {}
	public function setsockopt($key, $value) {}
	public function getendpoints() {}
	public function getsockettype() {}
	public function ispersistent() {}
	public function getpersistentid() {}
	public function getsockopt($key) {}
	public function sendmsg($message, $mode=0) {}
	public function recvmsg($mode=0) {}
}
/**
 * @package zmq
 */
class ZMQPoll {
	public function add($entry, $type) {}
	public function poll(&$readable, &$writable, $timeout="") {}
	public function getlasterrors() {}
	public function remove($remove) {}
	public function count() {}
	public function clear() {}
	public function items() {}
}
/**
 * @package zmq
 */
class ZMQDevice {
	public function __construct(ZMQSocket $frontend, ZMQSocket $backend, ZMQSocket $capture=null) {}
	public function run() {}
	public function setidlecallback($idle_callback, $timeout, $user_data="") {}
	public function setidletimeout($timeout) {}
	public function getidletimeout() {}
	public function settimercallback($idle_callback, $timeout, $user_data="") {}
	public function settimertimeout($timeout) {}
	public function gettimertimeout() {}
}
/**
 * @package zmq
 */
class ZMQException extends Exception {
}
/**
 * @package zmq
 */
class ZMQContextException extends ZMQException {
}
/**
 * @package zmq
 */
class ZMQSocketException extends ZMQException {
}
/**
 * @package zmq
 */
class ZMQPollException extends ZMQException {
}
/**
 * @package zmq
 */
class ZMQDeviceException extends ZMQException {
}
