--TEST--
Test setting socket options
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');
if (!defined('ZMQ::LIBZMQ_VERSION_MAJOR') || ZMQ::LIBZMQ_VERSION_MAJOR < 4) {
    die ("skip This test is for PHP7 and libzmq version 4.x and up");
}
?>
--FILE--
<?php

$tested = 0;

$removedVersion = false;
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_ROUTER_MANDATORY") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_PROBE_ROUTER") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_REQ_RELAXED") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_REQ_CORRELATE") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="w" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_CONFLATE") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_ZAP_DOMAIN") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="r" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_MECHANISM") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_PLAIN_SERVER") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_PLAIN_USERNAME") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=string php_type=string */
if (defined ("ZMQ::SOCKOPT_PLAIN_PASSWORD") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_IPV6") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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
$removedVersion = false;
/* socket option is marked mode="rw" type=int php_type=int */
if (defined ("ZMQ::SOCKOPT_IMMEDIATE") && ($removedVersion === false || ZMQ::LIBZMQ_VERSION_MAJOR < $removedVersion)) {
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

if ($tested == 0) {
    echo "Did not test any constants" . PHP_EOL;
}
echo "OK";
--EXPECT--
OK

