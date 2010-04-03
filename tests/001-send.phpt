--TEST--
Test send / recv
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

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

$client->send("Hello world!");

$message = $server->recv();
var_dump($message);
$server->send($message);

$message = $client->recv();
var_dump($message);

--EXPECT--
string(12) "Hello world!"
string(12) "Hello world!"