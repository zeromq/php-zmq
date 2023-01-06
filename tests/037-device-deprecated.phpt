--TEST--
Test device deprecated args
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
?>
--FILE--
<?php

$ctx = new ZMQContext ();
$s1 = new ZMQSocket ($ctx, ZMQ::SOCKET_SUB);
$device = new ZMQDevice($s1, $ctx->getSocket(ZMQ::SOCKET_PUB));


// Setup callback and user data for callback
$device->setIdleTimeout (100);
$device->setIdleCallback (function ($user_data) { echo "Called: {$user_data}" . PHP_EOL; return false; }, "test");

// Run first time
$device->run ();

echo "OK";
?>
--EXPECTF--
Deprecated: ZMQDevice::setidlecallback(): The signature for setIdleCallback has changed, please update your code in %s on line %d
Called: test
OK
