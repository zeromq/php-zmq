--TEST--
Test device capture
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
?>
--FILE--
<?php
require dirname(__FILE__) . '/zeromq_test_helper.inc';

function idle_func($val)
{
  return false;
}

$context = new ZMQContext();

$front = new ZMQSocket($context, ZMQ::SOCKET_PULL);
$front->bind (ZEROMQ_TEST_DSN);

$sender = new ZMQSocket($context, ZMQ::SOCKET_PUSH);
$sender->connect(ZEROMQ_TEST_DSN);


$backend = new ZMQSocket($context, ZMQ::SOCKET_PUSH);
$backend->bind (ZEROMQ_TEST_DSN2);

$receiver = new ZMQSocket($context, ZMQ::SOCKET_PULL);
$receiver->connect(ZEROMQ_TEST_DSN2);


$capture = new ZMQSocket($context, ZMQ::SOCKET_PUB);
$capture->bind ('inproc://capture');

$capture_listener = new ZMQSocket($context, ZMQ::SOCKET_SUB);
$capture_listener->connect ('inproc://capture');
$capture_listener->setSockOpt (ZMQ::SOCKOPT_SUBSCRIBE, "");






$device = new ZMQDevice($front, $backend, $capture);
$device->setIdleTimeout(100);
$device->setIdleCallback(function () { return false; }, 'ddd');


$sender->sendmsg ("Hello backend");
$device->run ();
$device->run ();

echo "Receiveing from receiver" . PHP_EOL;
var_dump($receiver->recvmsg());

echo "Receiveing from capture listener" . PHP_EOL;
var_dump($capture_listener->recvmsg());

echo "OK";
?>
--EXPECT--
Receiveing from receiver
string(13) "Hello backend"
Receiveing from capture listener
string(13) "Hello backend"
OK