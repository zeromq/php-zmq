--TEST--
Test send / recv binary
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$rose = file_get_contents(dirname(__FILE__) . '/rose.jpg');

/* Create 'server' */
$server = new ZeroMQ();

/* Create socket */
$socket = new ZeroMQSocket(ZeroMQ::SOCKET_REP);
$socket->bind("tcp://127.0.0.1:5566");

/* Assign socket */
$server->setSocket($socket);

$socket = new ZeroMQSocket(ZeroMQ::SOCKET_REQ);
$socket->connect("tcp://127.0.0.1:5566");

$client = new ZeroMQ();
$client->setSocket($socket);

$client->send($rose);

$message = $server->recv();
var_dump(strlen($message));

$server->send($message);

$message = $client->recv();
var_dump(strlen($message));

var_dump($message === $rose);

--EXPECT--
int(2051)
int(2051)
bool(true)