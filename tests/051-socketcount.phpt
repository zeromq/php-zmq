--TEST--
Test socket count variations
--SKIPIF--
<?php
	require_once(dirname(__FILE__) . '/skipif.inc'); 
	if (!in_array ('acquire', get_class_methods ('ZMQContext')))
		die ('skip');
	if (!in_array ('getsocketcount', get_class_methods ('ZMQContext')))
		die ('skip');
?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$context = new ZMQContext(1, false);

$socket1 = new ZMQSocket($context, ZMQ::SOCKET_REP);
$socket2 = $context->getSocket(ZMQ::SOCKET_REQ, 'persistent id');

var_dump ($context->getSocketCount());

unset($socket1);
var_dump ($context->getSocketCount());

unset($socket2);
var_dump ($context->getSocketCount());


$context = new ZMQContext(7, true);

$socket1 = new ZMQSocket($context, ZMQ::SOCKET_REP);
$socket2 = $context->getSocket(ZMQ::SOCKET_REQ, 'persistent id');

var_dump ($context->getSocketCount());

unset($socket1);
var_dump ($context->getSocketCount());

// Persistent socket should stay in count
unset($socket2);
var_dump ($context->getSocketCount());

$context = ZMQContext::acquire();

$socket1 = new ZMQSocket($context, ZMQ::SOCKET_REP);
$socket2 = $context->getSocket(ZMQ::SOCKET_REQ, 'persistent id');

var_dump ($context->getSocketCount());

unset($socket1);
var_dump ($context->getSocketCount());

// Persistent socket should stay in count
unset($socket2);
var_dump ($context->getSocketCount());

echo "OK";

--EXPECT--
int(2)
int(1)
int(0)
int(2)
int(1)
int(1)
int(2)
int(1)
int(1)
OK