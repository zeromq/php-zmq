--TEST--
set/get context options
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$test = new ZeroMQSocket(ZeroMQ::SOCKET_REQ);
$test->setContextOptions(2, 2);

try {
    $test->setContextOptions(-1, -1);
} catch (ZeroMQSocketException $e) {
    echo "incorrect args\n";
}

var_dump($test->getContextOptions());
$test->bind(ZEROMQ_TEST_DSN);

try {
    $test->setContextOptions(4,2);
} catch (ZeroMQSocketException $e) {
    echo "Got exception\n";
}

--EXPECT--
incorrect args
array(2) {
  ["app_threads"]=>
  int(2)
  ["io_threads"]=>
  int(2)
}
Got exception