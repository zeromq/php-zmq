--TEST--
Test callback edge-cases
--SKIPIF--
--XFAIL--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

function try_to_force_ref(&$a, $b) 
{
	echo "CALLED\n";
}

function throw_exception($socket, $pid = null) 
{
	/* This exception should bubble up */
	throw new Exception("hello world");
}

try {
	$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'persistent_socket', 'try_to_force_ref');
	echo "Fail\n";
} catch (ZMQSocketException $e) {
	echo $e->getMessage() . "\n";
}

try {
	$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'persistent_socket', 'throw_exception');
	echo "Fail\n";
} catch (ZMQSocketException $e) {
	echo $e->getMessage() . "\n";
}

--EXPECTF--
Parameter 1 to try_to_force_ref() expected to be a reference, value given
hello world
