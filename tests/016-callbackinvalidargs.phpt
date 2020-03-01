--TEST--
Test invalid args for callback
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

try {
	$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'my persistent 1', 'this_function_does_not_exist');
	echo "Fail\n";
} catch (ZMQSocketException $e) {
	echo "OK\n";
} catch (TypeError $e) {
 	echo "OK\n"; // on PHP8
}

try {
	$ctx = new ZMQContext();
	$socket = $ctx->getSocket(ZMQ::SOCKET_REQ, 'my persistent 2', 'this_function_does_not_exist');
	echo "Fail\n";
} catch (ZMQSocketException $e) {
	echo "OK\n";
} catch (TypeError $e) {
 	echo "OK\n"; // on PHP8
}

--EXPECT--
OK
OK