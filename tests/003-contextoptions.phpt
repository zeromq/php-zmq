--TEST--
set/get context options
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$test = new ZeroMQ(ZeroMQ::SOCKET_REQ);
$test->setContextOptions(2, 2, true);

try {
    $test->setContextOptions(-1, -1);
} catch (ZeroMQException $e) {
    echo "incorrect args\n";
}

var_dump($test->getContextOptions());
$test->bind(ZEROMQ_TEST_DSN);

try {
    $test->setContextOptions(4,2);
} catch (ZeroMQException $e) {
    echo "Got exception\n";
}

var_dump($test->getContextOptions());

--EXPECT--
incorrect args
array(3) {
  ["app_threads"]=>
  int(2)
  ["io_threads"]=>
  int(2)
  ["poll"]=>
  bool(true)
}
Got exception
array(3) {
  ["app_threads"]=>
  int(2)
  ["io_threads"]=>
  int(2)
  ["poll"]=>
  bool(true)
}