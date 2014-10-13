--TEST--
Test [Zyre] Zyre objects can exchange data in a group of peer
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipzyre.inc'); ?>
--FILE--
<?php

$ctx = new ZMQContext;

$z1 = new ZMQZyre($ctx);
$z1->start();
$z1->join('ZMQZyreTestGroup');


$z2 = new ZMQZyre($ctx);
$z2->start();
$z2->join('ZMQZyreTestGroup');


usleep(100000);

// Enter
$obj = $z1->recv();
var_dump($obj->command);

// Join
$obj = $z1->recv();
var_dump($obj->command);
var_dump($obj->group);

// Enter
$obj = $z2->recv();
var_dump($obj->command);

// Join
$obj = $z2->recv();
var_dump($obj->command);
var_dump($obj->group);

$z2->sendGroup('ZMQZyreTestGroup', 'Some usefull data');

usleep(100000);

// SHOUT
$obj = $z1->recv();
var_dump($obj->group);
var_dump($obj->data);

$z1->leave('ZMQZyreTestGroup');

usleep(100000);

// Leave
$obj = $z2->recv();
var_dump($obj->command);
var_dump($obj->group);

$z1->stop();

usleep(100000);

// Exit
$obj = $z2->recv();
var_dump($obj->command);

$z2->stop();

--EXPECTF--
string(5) "ENTER"
string(4) "JOIN"
string(16) "ZMQZyreTestGroup"
string(5) "ENTER"
string(4) "JOIN"
string(16) "ZMQZyreTestGroup"
string(16) "ZMQZyreTestGroup"
string(17) "Some usefull data"
string(5) "LEAVE"
string(16) "ZMQZyreTestGroup"
string(4) "EXIT"
