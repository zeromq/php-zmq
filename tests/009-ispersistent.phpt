--TEST--
Test ispersistent on context and socket
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

/* Persistent context */
$context = new ZMQContext();
$socket  = $context->getSocket(ZMQ::SOCKET_REQ, 'persistentId');
$socket2 = $context->getSocket(ZMQ::SOCKET_REQ, null);

var_dump($context->isPersistent(), 
         $socket->isPersistent(),
         $socket->getPersistentId(),
         $socket2->isPersistent(),
         $socket2->getPersistentId());

/* Non-persistent context */
$context = new ZMQContext(1, false);
$socket  = $context->getSocket(ZMQ::SOCKET_REQ, 'persistentId');
$socket2 = $context->getSocket(ZMQ::SOCKET_REQ, null);

var_dump($context->isPersistent(), 
         $socket->isPersistent(),
         $socket->getPersistentId(),
         $socket2->isPersistent(),
         $socket2->getPersistentId());


--EXPECTF--
bool(true)
bool(true)
string(12) "persistentId"
bool(false)
NULL
bool(false)
bool(false)
NULL
bool(false)
NULL