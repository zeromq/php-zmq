--TEST--
Test transient so that we're able to close a persistent socket
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$context = new ZMQContext();

$socket  = $context->getSocket(ZMQ::SOCKET_REQ, 'persistentId', function() {
    echo "1\n";
});
unset($socket);

$socket  = $context->getSocket(ZMQ::SOCKET_REQ, 'persistentId', function() {
    echo "2\n";
});
$socket->transient();

$socket  = $context->getSocket(ZMQ::SOCKET_REQ, 'persistentId', function() {
    echo "3\n";
});
$socket->transient();
unset($socket);

--EXPECTF--
1
3