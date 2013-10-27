--TEST--
Test send / recv with an XREQ and XREP device
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

$upstream = new ZMQSocket($context, ZMQ::SOCKET_XREQ);
$upstream->bind(ZEROMQ_TEST_DSN);

$downstream = new ZMQSocket($context, ZMQ::SOCKET_XREP);
$downstream->bind(ZEROMQ_TEST_DSN2);

$device = new ZMQDevice($upstream, $downstream);
$device->setIdleCallback('idle_func', 100, 'test');

$server = new ZMQSocket($context, ZMQ::SOCKET_REP);
$server->connect(ZEROMQ_TEST_DSN);

$client = new ZMQSocket($context, ZMQ::SOCKET_REQ);
$client->connect(ZEROMQ_TEST_DSN2);

$client->sendmsg("Hello server!");
$device->run();
var_dump($server->recvmsg());

$server->sendmsg("Hello client!");
$device->run();
var_dump($client->recvmsg());

--EXPECT--
string(13) "Hello server!"
string(13) "Hello client!"
