--TEST--
Test [Zyre] Headers are received on ENTER event
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipzyre.inc'); ?>
--FILE--
<?php

$ctx = new ZMQContext;

$z1 = new ZMQZyre($ctx);
$z1->setHeader('X-TEST', 'Z1');
$z1->start();

$z2 = new ZMQZyre($ctx);
$z2->setHeader('X-TEST', 'Z2');
$z2->start();

usleep(100000);

$obj = $z1->recv();
var_dump($obj->command);
var_dump($obj->headers->{'X-TEST'});

$obj = $z2->recv();
var_dump($obj->command);
var_dump($obj->headers->{'X-TEST'});

$z1->stop();

$obj = $z2->recv();
var_dump($obj->command);
$z2->stop();

--EXPECTF--
string(5) "ENTER"
string(2) "Z2"
string(5) "ENTER"
string(2) "Z1"
string(4) "EXIT"
