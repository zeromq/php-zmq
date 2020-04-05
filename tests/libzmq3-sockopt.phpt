--TEST--
Test setting socket options
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');
if (!defined('ZMQ::LIBZMQ_VERSION_MAJOR') || ZMQ::LIBZMQ_VERSION_MAJOR < 3) {
    die ("skip This test is for PHP7 and libzmq version 3.x and up");
}
?>
--FILE--
<?php

$tested = 0;

$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_SNDHWM") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_RCVHWM") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int64 php_type=int */
if (defined ("ZMQ::SOCKOPT_MAXMSGSIZE") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_MULTICAST_HOPS") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_XPUB_VERBOSE") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_TCP_KEEPALIVE") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_TCP_KEEPALIVE_IDLE") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_TCP_KEEPALIVE_CNT") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_TCP_KEEPALIVE_INTVL") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="w" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_TCP_ACCEPT_FILTER") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="r" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_LAST_ENDPOINT") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_ROUTER_RAW") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_IPV4ONLY") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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

if ($tested == 0) {
    echo "Did not test any constants" . PHP_EOL;
}
echo "OK";
--EXPECT--
OK

