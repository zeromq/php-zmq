--TEST--
Test callback arguments on persistent and non-persistent socket
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

function dump_args(ZMQSocket $s, $p = null) 
{
	var_dump($s, $p);
}

$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'persistent_socket', 'dump_args');
$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, null, 'dump_args');

echo "OK";

--EXPECTF--
object(ZMQSocket)#%d (0) {
}
string(17) "persistent_socket"
object(ZMQSocket)#%d (0) {
}
NULL
OK