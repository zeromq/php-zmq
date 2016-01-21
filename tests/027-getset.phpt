--TEST--
Test setting and getting values
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$context = new ZMQContext();
$socket = $context->getSocket(ZMQ::SOCKET_DEALER);

$socket->setSockOpt (ZMQ::SOCKOPT_IDENTITY, "Hello");
var_dump ($socket->getSockOpt (ZMQ::SOCKOPT_IDENTITY));

$socket->setSockOpt (ZMQ::SOCKOPT_BACKLOG, 100);
var_dump ($socket->getSockOpt (ZMQ::SOCKOPT_BACKLOG));

$socket->setSockOpt (ZMQ::SOCKOPT_LINGER, 50);
var_dump ($socket->getSockOpt (ZMQ::SOCKOPT_LINGER));

echo "OK\n";

--EXPECTF--
string(5) "Hello"
int(100)
int(50)
OK
