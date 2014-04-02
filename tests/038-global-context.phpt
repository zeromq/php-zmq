--TEST--
Test global context
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

class TestThread1 extends Thread
{
	public function run() {
		$endpoint1 = new ZMQSocket(ZMQContext::acquire(), ZMQ::SOCKET_PUB);
		$endpoint1->bind("inproc://hello");

		sleep (1000);
		$endpoint1->sendmsg("Hello world!");
	}
}

class TestThread2 extends Thread
{
	public function run() {
		$endpoint2 = new ZMQSocket(ZMQContext::acquire(), ZMQ::SOCKET_SUB);
		$endpoint2->setSockOpt(ZMQ::SOCKOPT_SUBSCRIBE, "Hel");
		$endpoint2->connect("inproc://hello");
		$message = $endpoint2->recvmsg();
		var_dump($message);
	}
}

$t1 = new TestThread1 ();
$t2 = new TestThread2 ();

$t1->run ();
sleep (100);
$t2->run ();



--EXPECT--
string(12) "Hello world!"