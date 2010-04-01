--TEST--
Test send / recv binary
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$socket = new ZeroMQSocket(ZeroMQ::SOCKET_REQ, "MySock1");
$socket->connect("tcp://127.0.0.1:5555");

$queue = new ZeroMQ();
$queue->setSocket($socket);

$rose = file_get_contents(dirname(__FILE__) . '/rose.jpg');

$message = new ZeroMQMessage($rose);
$queue->send($message);

$rose_back = $queue->recv()->getMessage();

if ($rose !== $rose_back || strlen($rose) !== strlen($rose_back))
  echo "Fail";
else
  echo "Success";

--EXPECT--
Success