--TEST--
Test callback edge-cases
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

function try_to_force_ref(&$a, $b) 
{
	echo "CALLED\n";
}

try {
	$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'persistent_socket', 'try_to_force_ref');
	echo "Fail\n";
} catch (ZMQSocketException $e) {
	echo $e->getMessage() . "\n";
}

--EXPECTF--
Warning: Parameter 1 to try_to_force_ref() expected to be a reference, value given in %s on line %d
Failed to invoke 'on_new_socket' callback try_to_force_ref()

