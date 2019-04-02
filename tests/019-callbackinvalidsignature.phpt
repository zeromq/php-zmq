--TEST--
Test callback edge-cases
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc');
if (PHP_VERSION_ID >= 70100) die("skip PHP 7.1 and higher fallback to passing argument by value even when forced to reference"); ?>
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
	echo "got exception\n";
}

--EXPECTF--
Warning: Parameter 1 to try_to_force_ref() expected to be a reference, value given in %s on line %d
got exception

