--TEST--
Test set/get context options
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$test = new ZMQ(ZMQ::SOCKET_REQ);
$test->setContextOptions(2);

try {
    $test->setContextOptions(-1);
} catch (ZMQException $e) {
    echo "incorrect args\n";
}

var_dump($test->getContextOptions());
$test->bind(ZEROMQ_TEST_DSN);

try {
    $test->setContextOptions(4);
} catch (ZMQException $e) {
    echo "Got exception\n";
}

var_dump($test->getContextOptions());

--EXPECT--
incorrect args
array(1) {
  ["io_threads"]=>
  int(2)
}
Got exception
array(1) {
  ["io_threads"]=>
  int(2)
}