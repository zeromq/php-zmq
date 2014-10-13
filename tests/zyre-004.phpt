--TEST--
Test [Zyre] Zyre objects can exchange data with a peer
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipzyre.inc'); ?>
--FILE--
<?php

$ctx = new ZMQContext;

$z1 = new ZMQZyre($ctx);
$z1->start();

$z2 = new ZMQZyre($ctx);
$z2->start();

usleep(100000);

// Enter
$obj = $z1->recv();
var_dump($obj->command);

// Enter
$obj = $z2->recv();
var_dump($obj->command);
$peer = $obj->peer;

$z2->sendPeer($peer, 'Some very usefull data');

usleep(100000);

// SHOUT
$obj = $z1->recv();
var_dump($obj->data);

$z1->stop();

usleep(100000);

// Exit
$obj = $z2->recv();
var_dump($obj->command);

$z2->stop();

--EXPECTF--
string(5) "ENTER"
string(5) "ENTER"
string(22) "Some very usefull data"
string(4) "EXIT"
