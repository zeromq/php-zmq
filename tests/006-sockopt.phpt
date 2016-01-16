--TEST--
Test getsockopt / setsockopt
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

if (!is_callable('ZMQ', 'getSockOpt'))
	die("skip zeromq 2.0.7 or higher required");

$test = create_server();

$test->setSockOpt(ZMQ::SOCKOPT_IDENTITY, "hello");
var_dump($test->getSockOpt(ZMQ::SOCKOPT_IDENTITY));

$test->setSockOpt(ZMQ::SOCKOPT_IDENTITY, str_repeat("a", 255));
var_dump(strlen($test->getSockOpt(ZMQ::SOCKOPT_IDENTITY)));

try {
	$test->setSockOpt(ZMQ::SOCKOPT_IDENTITY, str_repeat("a", 300));
	var_dump(strlen($test->getSockOpt(ZMQ::SOCKOPT_IDENTITY)));
} catch (ZMQSocketException $e) {
	echo "too long";
}

--EXPECT--
string(5) "hello"
int(255)
too long
