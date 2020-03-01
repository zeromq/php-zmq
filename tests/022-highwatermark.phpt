--TEST--
Test that high-watermark works
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');
if (!defined('ZMQ::SOCKOPT_LINGER'))
    die ("Skip Not compiled against new enough version");
?>
--FILE--
<?php

$readable = array();
$writable = array();

$poll = new ZMQPoll();
$ctx  = new ZMQContext();

$req = new ZMQSocket($ctx, ZMQ::SOCKET_REQ);
$req->setSockOpt(ZMQ::SOCKOPT_HWM, 1);
$req->setSockOpt(ZMQ::SOCKOPT_LINGER, 1);
$req->bind("tcp://127.0.0.1:44331");

$rep = new ZMQSocket($ctx, ZMQ::SOCKET_REP);
$rep->connect("tcp://127.0.0.1:44331");

$poll->add($req, ZMQ::POLL_OUT);

$poll->poll($readable, $writable, 1000);
var_dump($writable);

$req->sendmsg('x');

$poll->poll($readable, $writable, 1000);
var_dump($writable);

$rep->recvmsg ();
$rep->sendmsg('x');
$req->recvmsg();

$poll->poll($readable, $writable, 1000);
var_dump($writable);

echo "OK\n";

?>
--EXPECTF--
array(1) {
  [0]=>
  object(ZMQSocket)#3 (0) {
  }
}
array(0) {
}
array(1) {
  [0]=>
  object(ZMQSocket)#3 (0) {
  }
}
OK