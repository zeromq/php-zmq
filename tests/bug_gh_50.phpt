--TEST--
Test for Github issue #50
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
?>
--FILE--
<?php

$context = new ZMQContext (1, false);
$server = new ZMQSocket ($context, ZMQ::SOCKET_PUB);
$server->bind ('inproc://test');

$client = new ZMQSocket ($context, ZMQ::SOCKET_SUB);
$client->setsockopt (ZMQ::SOCKOPT_SUBSCRIBE, "");
$client->connect ('inproc://test');

$client2 = new ZMQSocket ($context, ZMQ::SOCKET_SUB);
$client2->setsockopt (ZMQ::SOCKOPT_SUBSCRIBE, "");
$client2->connect ('inproc://test');

$poll = new ZMQPoll ();
$poll->add ($client, ZMQ::POLL_IN);
$poll->add ($client2, ZMQ::POLL_IN);

$readable = array();
$writable = array();

$server->send ("Hello all");

$res = $poll->poll ($readable, $writable, 1000);
var_dump ($poll->count () == $res, $readable, $writable);

foreach ($readable as $r)
    $r->recv ();
    
$poll->remove ($client2);
$server->send ("Hello all");

$res = $poll->poll ($readable, $writable, 1000);
var_dump ($poll->count () == $res, $readable, $writable);

?>

--EXPECT--
bool(true)
array(2) {
  [0]=>
  object(ZMQSocket)#3 (0) {
  }
  [1]=>
  object(ZMQSocket)#4 (0) {
  }
}
array(0) {
}
bool(true)
array(1) {
  [0]=>
  object(ZMQSocket)#3 (0) {
  }
}
array(0) {
}