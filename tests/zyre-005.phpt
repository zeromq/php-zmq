--TEST--
Test [Zyre] Test getter of internal ZMQSocket in ZMQZyre
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipzyre.inc'); ?>
--FILE--
<?php

$ctx = new ZMQContext;

$z1 = new ZMQZyre($ctx);
$z1->setHeader('X-TEST', 'Z1');
$z1->start();

usleep(100000);

$z2 = new ZMQZyre($ctx);
$z2->setHeader('X-TEST', 'Z2');
$z2->start();

usleep(100000);

$sock1 = $z1->getSocket();
$sock2 = $z2->getSocket();


var_dump($sock1->recv());   // Enter
$sock1->recv();             // ID
$sock1->recv();             // Headers
$sock1->recv();             // IP:PORT

var_dump($sock2->recv());   // Enter
$sock2->recv();             // ID
$sock2->recv();             // Headers
$sock2->recv();             // IP:PORT

unset($sock1);
unset($sock2);

--EXPECTF--
string(5) "ENTER"
string(5) "ENTER"
