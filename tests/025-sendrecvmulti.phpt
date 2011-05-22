--TEST--
Test send / recv for multipart messages
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$server = create_server();
$client = create_client();

$message = array("Hello", "World", 12314);

$client->sendmulti($message);

var_dump($message);

$messages = $server->recvmulti();
var_dump($messages);

$e = $server->sendMulti($message);
var_dump($e == $server);

--EXPECT--
array(3) {
  [0]=>
  string(5) "Hello"
  [1]=>
  string(5) "World"
  [2]=>
  int(12314)
}
array(3) {
  [0]=>
  string(5) "Hello"
  [1]=>
  string(5) "World"
  [2]=>
  string(5) "12314"
}
bool(true)