--TEST--
Test that high-watermark works
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>

if (!defined('ZMQ::SOCKOPT_LINGER'))
    die ("Skip Not compiled against new enough version");

--FILE--
<?php

$readable = array();
$writable = array();

$poll = new ZMQPoll();
$ctx  = new ZMQContext();

$pull = new ZMQSocket($ctx, ZMQ::SOCKET_PULL);
$pull->bind("tcp://127.0.0.1:44331");

$push = new ZMQSocket($ctx, ZMQ::SOCKET_PUSH);
$push->setSockOpt(ZMQ::SOCKOPT_HWM, 1);
$push->setSockOpt(ZMQ::SOCKOPT_LINGER, 1);
$push->connect("tcp://127.0.0.1:44331");

$poll->add($push, ZMQ::POLL_OUT);

$poll->poll(null, $writable, 10);
var_dump($writable);

$push->send('x');

$poll->poll(null, $writable, 10);
var_dump($writable);

echo "OK\n";

?>
--EXPECTF--
array(1) {
  [0]=>
  object(ZMQSocket)#%d (%d) {
  }
}
array(0) {
}
OK