--TEST--
Test returning socket type
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$context = new ZMQContext();

var_dump ($context->getSocket(ZMQ::SOCKET_PUSH)->getSocketType() === ZMQ::SOCKET_PUSH);

var_dump ($context->getSocket(ZMQ::SOCKET_PUB)->getSocketType() === ZMQ::SOCKET_PUB);

$socket = $context->getSocket(ZMQ::SOCKET_ROUTER);

var_dump ($socket->getSocketType() === $socket->getSockOpt(ZMQ::SOCKOPT_TYPE));

echo "OK\n";

--EXPECTF--
bool(true)
bool(true)
bool(true)
OK
