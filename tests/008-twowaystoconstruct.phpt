--TEST--
Test constructing a socket
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

/* First */
$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ);
var_dump($socket);

/* Second */
$ctx = new ZMQContext();
$socket2 = $ctx->getSocket(ZMQ::SOCKET_REQ);
var_dump($socket2);

--EXPECTF--
object(ZMQSocket)#%d (%d) {
}
object(ZMQSocket)#%d (%d) {
}