--TEST--
Test remove invalid id from ZMQPoll
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$poll = new ZMQPoll();
$ctx  = new ZMQContext();
$sock = new ZMQSocket($ctx, ZMQ::SOCKET_REP);


$id1 = $poll->add(fopen(__FILE__, 'r'), ZMQ::POLL_IN);
$id2 = $poll->add($sock, ZMQ::POLL_IN);

$poll->remove($id1);
$poll->remove("adsads");

echo "OK";

--EXPECT--
OK