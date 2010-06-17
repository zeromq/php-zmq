--TEST--
Test clearing and reusing ZMQPoll
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$poll = new ZMQPoll();
$ctx  = new ZMQContext();

for ($i = 0; $i < 10; $i++) {
    $id = $poll->add(new ZMQSocket($ctx, ZMQ::SOCKET_REP), ZMQ::POLL_IN);
    
}

var_dump($poll->count());
$poll->clear();
var_dump($poll->count());


for ($i = 0; $i < 10; $i++) {
    $ids[] = $poll->add(new ZMQSocket($ctx, ZMQ::SOCKET_REP, 'dfd'), ZMQ::POLL_IN);
}

var_dump($poll->count());

for ($i = 0; $i < 10; $i++) {
    if ($poll->remove($ids[$i]) !== true) {
        echo 'err';
    }
}
var_dump($poll->count());

--EXPECT--
int(10)
int(0)
int(10)
int(0)