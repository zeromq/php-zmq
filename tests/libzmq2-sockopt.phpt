--TEST--
Test setting socket options
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');
if (!defined('ZMQ::LIBZMQ_VERSION_MAJOR') || ZMQ::LIBZMQ_VERSION_MAJOR < 2) {
    die ("skip This test is for PHP7 and libzmq version 2.x and up");
}
?>
--FILE--
<?php

$tested = 0;

$removedVersion = 3;
/* socket option is marked mode="rw" type=uint64 php_type=int */
if (defined ("ZMQ::SOCKOPT_HWM") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_HWM, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_HWM);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_HWM) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_HWM: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
$removedVersion = 3;
/* socket option is marked mode="rw" type=int64 php_type=int */
if (defined ("ZMQ::SOCKOPT_SWAP") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_SWAP, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_SWAP);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_SWAP) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_SWAP: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
$removedVersion = false;
/* socket option is marked mode="rw" type=uint64 php_type=int */
if (defined ("ZMQ::SOCKOPT_AFFINITY") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_IDENTITY") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int64 php_type=int */
if (defined ("ZMQ::SOCKOPT_RATE") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int64 php_type=int */
if (defined ("ZMQ::SOCKOPT_RECOVERY_IVL") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = 3;
/* socket option is marked mode="rw" type=int64 php_type=int */
if (defined ("ZMQ::SOCKOPT_RECOVERY_IVL_MSEC") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_RECOVERY_IVL_MSEC, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_RECOVERY_IVL_MSEC);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_RECOVERY_IVL_MSEC) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_RECOVERY_IVL_MSEC: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
$removedVersion = 3;
/* socket option is marked mode="rw" type=int64 php_type=int */
if (defined ("ZMQ::SOCKOPT_MCAST_LOOP") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_MCAST_LOOP, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_MCAST_LOOP);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_MCAST_LOOP) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_MCAST_LOOP: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_RCVTIMEO") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_SNDTIMEO") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=uint64 php_type=int */
if (defined ("ZMQ::SOCKOPT_SNDBUF") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
    $test_value = 1;

    $socket = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_SUB);

    // Test read-write
    $socket->setSockOpt(ZMQ::SOCKOPT_SNDBUF, $test_value);
    $retval = $socket->getSockOpt(ZMQ::SOCKOPT_SNDBUF);

    if ($socket->getSockOpt(ZMQ::SOCKOPT_SNDBUF) !== $test_value) {
        echo "Failed to set ZMQ::SOCKOPT_SNDBUF: expected=[$test_value] actual=[$retval]" . PHP_EOL;
    }
    $tested++;


}
$removedVersion = false;
/* socket option is marked mode="rw" type=uint64 php_type=int */
if (defined ("ZMQ::SOCKOPT_RCVBUF") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_LINGER") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_RECONNECT_IVL") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_RECONNECT_IVL_MAX") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_BACKLOG") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="w" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_SUBSCRIBE") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="w" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_UNSUBSCRIBE") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="r" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_TYPE") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="r" type=int64 php_type=int */
if (defined ("ZMQ::SOCKOPT_RCVMORE") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="r" type=socket php_type=resource */
if (defined ("ZMQ::SOCKOPT_FD") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {

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
$removedVersion = false;
/* socket option is marked mode="r" type=uint32 php_type=int */
if (defined ("ZMQ::SOCKOPT_EVENTS") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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

if ($tested == 0) {
    echo "Did not test any constants" . PHP_EOL;
}
echo "OK";
--EXPECT--
OK

