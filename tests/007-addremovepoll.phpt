--TEST--
Test adding / removing items
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php
/* Create socket, request-reply pattern (reply socket) */
$z = new ZMQ(ZMQ::SOCKET_REP);
$z->setContextOptions(1,1,true);
$z->bind("tcp://127.0.0.1:5555");

/* create handle */
$fp = fsockopen("tcp://example.com:80");

$poll = new ZMQPoll();
$obj_id = $poll->add($z, ZMQ::POLL_IN | ZMQ::POLL_OUT);
$fp_id = $poll->add($fp, ZMQ::POLL_IN | ZMQ::POLL_OUT);

var_dump($obj_id, $fp_id, $poll->count());

$a = array();
$b = array();
$poll->poll($a, $b, 100);
var_dump($a, $b);


fclose($fp);

var_dump($poll->poll($a, $b, 100));
var_dump($poll->getLastErrors());

$poll->clear();
var_dump($poll->count());

--EXPECTF--
string(34) "o:%s"
string(3) "r:%d"
int(2)
array(0) {
}
array(1) {
  [0]=>
  resource(%d) of type (stream)
}
int(1)
array(1) {
  [0]=>
  string(3) "r:%d"
}
int(0)