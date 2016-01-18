--TEST--
Test shared context
--SKIPIF--
<?php
	require_once(dirname(__FILE__) . '/skipif.inc');
	if (!in_array ('acquire', get_class_methods ('ZMQContext')))
		die ('skip');
?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$context = ZMQContext::acquire();

$socket1 = new ZMQSocket($context, ZMQ::SOCKET_REP);
$socket2 = ZMQContext::acquire()->getSocket(ZMQ::SOCKET_REQ, 'persistent id');

$dsn = uniqid("inproc://shared-ctx-");

$socket1->bind ($dsn);
$socket2->connect ($dsn);

$socket2->send("hello");
var_dump($socket1->recv());

var_dump ($context->isPersistent());
var_dump ($context->getSocketCount());

echo "OK";

--EXPECT--
string(5) "hello"
bool(true)
int(2)
OK