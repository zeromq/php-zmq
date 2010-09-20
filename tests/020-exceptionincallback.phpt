--TEST--
Test throwing exception from callback
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

function this_throws($a, $b) 
{
	throw new Exception("Hello there");
}

try {
	$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'persistent_socket', 'this_throws');
	echo "Fail\n";
} catch (Exception $e) {
	echo $e->getMessage() . "\n";
}

--EXPECTF--
Hello there

