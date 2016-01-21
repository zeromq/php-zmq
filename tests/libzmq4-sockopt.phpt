--TEST--
Test setting socket options
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');
if (!defined('ZMQ::LIBZMQ_VERSION_MAJOR') || ZMQ::LIBZMQ_VERSION_MAJOR != 4) {
    die ("skip This test is for PHP7 and libzmq version 4.x");
}
?>
--FILE--
<?php

$tested = 0;

/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_HEARTBEAT_IVL")) {
    $test_value = 2000;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_DEALER);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_HEARTBEAT_IVL, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_HEARTBEAT_IVL);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_HEARTBEAT_IVL) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_HEARTBEAT_IVL: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_HEARTBEAT_TTL")) {
    $test_value = 4000;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_DEALER);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_HEARTBEAT_TTL, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_HEARTBEAT_TTL);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_HEARTBEAT_TTL) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_HEARTBEAT_TTL: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_HEARTBEAT_TIMEOUT")) {
    $test_value = 6000;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_DEALER);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_HEARTBEAT_TIMEOUT, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_HEARTBEAT_TIMEOUT);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_HEARTBEAT_TIMEOUT) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_HEARTBEAT_TIMEOUT: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_TOS")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_DEALER);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_TOS, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_TOS);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_TOS) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_TOS: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_ROUTER_HANDOVER")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_ROUTER);

    // Test write-only
    $socket->setSockOpt(ZMQ::SOCKOPT_ROUTER_HANDOVER, $test_value);
    $tested++;

    try {
        $socket->getSockOpt(ZMQ::SOCKOPT_ROUTER_HANDOVER);
        echo "Should not be able to get ZMQ::SOCKOPT_ROUTER_HANDOVER" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_ROUTER_MANDATORY")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_ROUTER);

    // Test write-only
    $socket->setSockOpt(ZMQ::SOCKOPT_ROUTER_MANDATORY, $test_value);
    $tested++;

    try {
        $socket->getSockOpt(ZMQ::SOCKOPT_ROUTER_MANDATORY);
        echo "Should not be able to get ZMQ::SOCKOPT_ROUTER_MANDATORY" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_PROBE_ROUTER")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_DEALER);

    // Test write-only
    $socket->setSockOpt(ZMQ::SOCKOPT_PROBE_ROUTER, $test_value);
    $tested++;

    try {
        $socket->getSockOpt(ZMQ::SOCKOPT_PROBE_ROUTER);
        echo "Should not be able to get ZMQ::SOCKOPT_PROBE_ROUTER" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_REQ_RELAXED")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_REQ);

    // Test write-only
    $socket->setSockOpt(ZMQ::SOCKOPT_REQ_RELAXED, $test_value);
    $tested++;

    try {
        $socket->getSockOpt(ZMQ::SOCKOPT_REQ_RELAXED);
        echo "Should not be able to get ZMQ::SOCKOPT_REQ_RELAXED" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_REQ_CORRELATE")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_REQ);

    // Test write-only
    $socket->setSockOpt(ZMQ::SOCKOPT_REQ_CORRELATE, $test_value);
    $tested++;

    try {
        $socket->getSockOpt(ZMQ::SOCKOPT_REQ_CORRELATE);
        echo "Should not be able to get ZMQ::SOCKOPT_REQ_CORRELATE" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_CONFLATE")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_PUSH);

    // Test write-only
    $socket->setSockOpt(ZMQ::SOCKOPT_CONFLATE, $test_value);
    $tested++;

    try {
        $socket->getSockOpt(ZMQ::SOCKOPT_CONFLATE);
        echo "Should not be able to get ZMQ::SOCKOPT_CONFLATE" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="rw" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_ZAP_DOMAIN")) {
    $test_value = "test";

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_ZAP_DOMAIN, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_ZAP_DOMAIN);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_ZAP_DOMAIN) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_ZAP_DOMAIN: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="r" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_MECHANISM")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-only
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_MECHANISM);
    if (is_int($retval) === false) {
        echo "Incorrect return type for ZMQ::SOCKOPT_MECHANISM: expected=[int] actual=[" .gettype($retval). "]" . PHP_EOL;
    }
    $tested++;

    try {
        $socket->setSockOpt(ZMQ::SOCKOPT_MECHANISM, 'x');
        echo "Should not be able to set ZMQ::SOCKOPT_MECHANISM" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_PLAIN_SERVER")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_PUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_PLAIN_SERVER, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_PLAIN_SERVER);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_PLAIN_SERVER) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_PLAIN_SERVER: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_PLAIN_USERNAME")) {
    $test_value = "test";

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_PLAIN_USERNAME, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_PLAIN_USERNAME);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_PLAIN_USERNAME) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_PLAIN_USERNAME: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_PLAIN_PASSWORD")) {
    $test_value = "test";

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_PLAIN_PASSWORD, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_PLAIN_PASSWORD);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_PLAIN_PASSWORD) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_PLAIN_PASSWORD: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_IPV6")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_IPV6, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_IPV6);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_IPV6) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_IPV6: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_IMMEDIATE")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_DEALER);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_IMMEDIATE, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_IMMEDIATE);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_IMMEDIATE) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_IMMEDIATE: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_ROUTER_RAW")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_ROUTER);

    // Test write-only
    $socket->setSockOpt(ZMQ::SOCKOPT_ROUTER_RAW, $test_value);
    $tested++;

    try {
        $socket->getSockOpt(ZMQ::SOCKOPT_ROUTER_RAW);
        echo "Should not be able to get ZMQ::SOCKOPT_ROUTER_RAW" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_IPV4ONLY")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_IPV4ONLY, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_IPV4ONLY);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_IPV4ONLY) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_IPV4ONLY: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="r" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_TYPE")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-only
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_TYPE);
    if (is_int($retval) === false) {
        echo "Incorrect return type for ZMQ::SOCKOPT_TYPE: expected=[int] actual=[" .gettype($retval). "]" . PHP_EOL;
    }
    $tested++;

    try {
        $socket->setSockOpt(ZMQ::SOCKOPT_TYPE, 'x');
        echo "Should not be able to set ZMQ::SOCKOPT_TYPE" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_SNDHWM")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_PUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_SNDHWM, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_SNDHWM);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_SNDHWM) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_SNDHWM: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_RCVHWM")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_RCVHWM, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_RCVHWM);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_RCVHWM) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_RCVHWM: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=uint64 php_type=int */
if (defined ("ZMQ::SOCKOPT_AFFINITY")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_AFFINITY, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_AFFINITY);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_AFFINITY) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_AFFINITY: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="w" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_SUBSCRIBE")) {
    $test_value = "test";

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test write-only
    $socket->setSockOpt(ZMQ::SOCKOPT_SUBSCRIBE, $test_value);
    $tested++;

    try {
        $socket->getSockOpt(ZMQ::SOCKOPT_SUBSCRIBE);
        echo "Should not be able to get ZMQ::SOCKOPT_SUBSCRIBE" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="w" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_UNSUBSCRIBE")) {
    $test_value = "test";

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test write-only
    $socket->setSockOpt(ZMQ::SOCKOPT_UNSUBSCRIBE, $test_value);
    $tested++;

    try {
        $socket->getSockOpt(ZMQ::SOCKOPT_UNSUBSCRIBE);
        echo "Should not be able to get ZMQ::SOCKOPT_UNSUBSCRIBE" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="rw" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_IDENTITY")) {
    $test_value = "test";

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_DEALER);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_IDENTITY, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_IDENTITY);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_IDENTITY) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_IDENTITY: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_RATE")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_RATE, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_RATE);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_RATE) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_RATE: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_RECOVERY_IVL")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_RECOVERY_IVL, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_RECOVERY_IVL);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_RECOVERY_IVL) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_RECOVERY_IVL: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_SNDBUF")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_PUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_SNDBUF, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_SNDBUF);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_SNDBUF) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_SNDBUF: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_RCVBUF")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_RCVBUF, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_RCVBUF);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_RCVBUF) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_RCVBUF: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_LINGER")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_LINGER, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_LINGER);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_LINGER) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_LINGER: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_RECONNECT_IVL")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_RECONNECT_IVL, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_RECONNECT_IVL);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_RECONNECT_IVL) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_RECONNECT_IVL: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_RECONNECT_IVL_MAX")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_RECONNECT_IVL_MAX, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_RECONNECT_IVL_MAX);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_RECONNECT_IVL_MAX) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_RECONNECT_IVL_MAX: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_BACKLOG")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_BACKLOG, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_BACKLOG);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_BACKLOG) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_BACKLOG: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int64 php_type=int */
if (defined ("ZMQ::SOCKOPT_MAXMSGSIZE")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_MAXMSGSIZE, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_MAXMSGSIZE);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_MAXMSGSIZE) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_MAXMSGSIZE: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_MULTICAST_HOPS")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_MULTICAST_HOPS, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_MULTICAST_HOPS);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_MULTICAST_HOPS) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_MULTICAST_HOPS: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_RCVTIMEO")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_RCVTIMEO, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_RCVTIMEO);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_RCVTIMEO) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_RCVTIMEO: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_SNDTIMEO")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_SNDTIMEO, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_SNDTIMEO);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_SNDTIMEO) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_SNDTIMEO: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_XPUB_VERBOSE")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_XPUB);

    // Test write-only
    $socket->setSockOpt(ZMQ::SOCKOPT_XPUB_VERBOSE, $test_value);
    $tested++;

    try {
        $socket->getSockOpt(ZMQ::SOCKOPT_XPUB_VERBOSE);
        echo "Should not be able to get ZMQ::SOCKOPT_XPUB_VERBOSE" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_TCP_KEEPALIVE")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_TCP_KEEPALIVE, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_TCP_KEEPALIVE);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_TCP_KEEPALIVE) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_TCP_KEEPALIVE: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
/* socket option is marked mode="w" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_TCP_ACCEPT_FILTER")) {
    $test_value = "127.0.0.1";

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test write-only
    $socket->setSockOpt(ZMQ::SOCKOPT_TCP_ACCEPT_FILTER, $test_value);
    $tested++;

    try {
        $socket->getSockOpt(ZMQ::SOCKOPT_TCP_ACCEPT_FILTER);
        echo "Should not be able to get ZMQ::SOCKOPT_TCP_ACCEPT_FILTER" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="r" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_RCVMORE")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-only
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_RCVMORE);
    if (is_int($retval) === false) {
        echo "Incorrect return type for ZMQ::SOCKOPT_RCVMORE: expected=[int] actual=[" .gettype($retval). "]" . PHP_EOL;
    }
    $tested++;

    try {
        $socket->setSockOpt(ZMQ::SOCKOPT_RCVMORE, 'x');
        echo "Should not be able to set ZMQ::SOCKOPT_RCVMORE" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="r" type=socket php_type=resource */
if (defined ("ZMQ::SOCKOPT_FD")) {

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-only
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_FD);
    if (is_resource($retval) === false) {
        echo "Incorrect return type for ZMQ::SOCKOPT_FD: expected=[resource] actual=[" .gettype($retval). "]" . PHP_EOL;
    }
    $tested++;

    try {
        $socket->setSockOpt(ZMQ::SOCKOPT_FD, 'x');
        echo "Should not be able to set ZMQ::SOCKOPT_FD" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="r" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_EVENTS")) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-only
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_EVENTS);
    if (is_int($retval) === false) {
        echo "Incorrect return type for ZMQ::SOCKOPT_EVENTS: expected=[int] actual=[" .gettype($retval). "]" . PHP_EOL;
    }
    $tested++;

    try {
        $socket->setSockOpt(ZMQ::SOCKOPT_EVENTS, 'x');
        echo "Should not be able to set ZMQ::SOCKOPT_EVENTS" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}
/* socket option is marked mode="r" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_LAST_ENDPOINT")) {
    $test_value = "test";

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-only
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_LAST_ENDPOINT);
    if (is_string($retval) === false) {
        echo "Incorrect return type for ZMQ::SOCKOPT_LAST_ENDPOINT: expected=[string] actual=[" .gettype($retval). "]" . PHP_EOL;
    }
    $tested++;

    try {
        $socket->setSockOpt(ZMQ::SOCKOPT_LAST_ENDPOINT, 'x');
        echo "Should not be able to set ZMQ::SOCKOPT_LAST_ENDPOINT" . PHP_EOL;
    } catch (ZMQSocketException $e) {}

}

if ($tested == 0) {
    echo "Did not test any constants" . PHP_EOL;
}
echo "OK";
--EXPECT--
OK

