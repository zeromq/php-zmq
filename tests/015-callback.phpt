--TEST--
Test basic callback usage
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'my persistent 1', 'bind_callback');
var_dump($socket->getEndpoints());

$ctx = new ZMQContext();
$socket = $ctx->getSocket(ZMQ::SOCKET_REQ, 'my persistent 2', 'bind_callback');
var_dump($socket->getEndpoints());


--EXPECT--
array(2) {
  ["connect"]=>
  array(0) {
  }
  ["bind"]=>
  array(1) {
    [0]=>
    string(20) "tcp://127.0.0.1:5566"
  }
}
array(2) {
  ["connect"]=>
  array(0) {
  }
  ["bind"]=>
  array(1) {
    [0]=>
    string(20) "tcp://127.0.0.1:5567"
  }
}