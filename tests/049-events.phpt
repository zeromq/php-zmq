--TEST--
Test events
--SKIPIF--
<?php
	require_once(dirname(__FILE__) . '/skipif.inc');
	if (!in_array ('monitor', get_class_methods ('zmqsocket')))
		die ('skip monitor not supported in libzmq or PHP version (required: libzmq 4.1.0+ / PHP7)');
?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$context = new ZMQContext();

$client = $context->getSocket(ZMQ::SOCKET_DEALER);
$client->monitor("inproc://socket-monitor");

$monitor = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_PAIR);
$monitor->connect("inproc://socket-monitor");

$server = $context->getSocket(ZMQ::SOCKET_DEALER);
$server->bind("tcp://*:5050");

$client->connect("tcp://127.0.0.1:5050");
$event = $monitor->recvEvent();
var_dump ($event, $event["event"] == ZMQ::EVENT_CONNECT_DELAYED);

$event = $monitor->recvEvent();
var_dump ($event, $event["event"] == ZMQ::EVENT_CONNECTED);

echo "OK";

--EXPECTF--
array(3) {
  ["event"]=>
  int(2)
  ["value"]=>
  int(%d)
  ["address"]=>
  string(20) "tcp://127.0.0.1:5050"
}
bool(true)
array(3) {
  ["event"]=>
  int(1)
  ["value"]=>
  int(%d)
  ["address"]=>
  string(20) "tcp://127.0.0.1:5050"
}
bool(true)
OK