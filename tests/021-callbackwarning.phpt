--TEST--
Test warning in callback
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

function generate_warning($a, $b) 
{
	in_array(1, 1);
}

$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'persistent_socket', 'generate_warning');

--EXPECTF--
Warning: in_array() expects parameter 2 to be array, integer given in %s on line %d

