--TEST--
Test send / recv
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$server = create_server();
$client = create_client();

//var_dump($client->getSocket()->getEndpoints());
$client->send("Hello world!");
//var_dump($client->getSocket()->getEndpoints());

//var_dump($server->getSocket()->getEndpoints());
$message = $server->recv();
var_dump($server->getSocket()->getEndpoints());

var_dump($message);
$server->send($message);

$message = $client->recv();
var_dump($message);

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
string(12) "Hello world!"
string(12) "Hello world!"