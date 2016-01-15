--TEST--
Test getting endpoints
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$server = create_server();
$client = create_client();

var_dump($client->getEndpoints());
var_dump($server->getEndpoints());

$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ);
var_dump($socket->getEndpoints());

--EXPECTF--
array(2) {
  ["connect"]=>
  array(1) {
    [0]=>
    string(%d) "inproc://php-test"
  }
  ["bind"]=>
  array(0) {
  }
}
array(2) {
  ["connect"]=>
  array(0) {
  }
  ["bind"]=>
  array(1) {
    [0]=>
    string(%d) "inproc://php-test"
  }
}
array(2) {
  ["connect"]=>
  array(0) {
  }
  ["bind"]=>
  array(0) {
  }
}