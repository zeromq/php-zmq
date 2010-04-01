--TEST--
Test send / recv
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$socket = new ZeroMQSocket(ZeroMQ::SOCKET_REQ, "MySock1");
$socket->connect("tcp://127.0.0.1:5555");

$queue = new ZeroMQ();
$queue->setSocket($socket);

$message = new ZeroMQMessage("Hello world!");
$queue->send($message);
var_dump($queue->recv()->getMessage());

--EXPECT--
string(12) "Hello world!"