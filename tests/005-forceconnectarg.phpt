--TEST--
Test forcing connect
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ);
$socket->connect("tcp://127.0.0.1:5566");
$socket->connect("tcp://127.0.0.1:5566", true);
$socket->connect("tcp://127.0.0.1:5566", true);
$socket->connect("tcp://127.0.0.1:5566", true);
$socket->connect("tcp://127.0.0.1:5566");

var_dump($socket->getEndpoints());

--EXPECTF--
array(2) {
  ["connect"]=>
  array(1) {
    [0]=>
    string(20) "tcp://127.0.0.1:5566"
  }
  ["bind"]=>
  array(0) {
  }
}