--TEST--
Test getsockopt / setsockopt
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

if (!is_callable('ZeroMQ', 'getSockOpt'))
	die("skip zeromq 2.0.7 or higher required");

$test = new ZeroMQ(ZeroMQ::SOCKET_REP);

$test->setSockOpt(ZeroMQ::SOCKOPT_HWM, 1);
var_dump($test->getSockOpt(ZeroMQ::SOCKOPT_HWM));

$test->setSockOpt(ZeroMQ::SOCKOPT_IDENTITY, "hello");
var_dump($test->getSockOpt(ZeroMQ::SOCKOPT_IDENTITY));

--EXPECT--
int(1)
string(5) "hello"