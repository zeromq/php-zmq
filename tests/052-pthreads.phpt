--TEST--
Test pthreads integration
--SKIPIF--
<?php 
	require_once(dirname(__FILE__) . '/skipif.inc'); 
	if (!extension_loaded ('pthreads')) {
		die ('skip Requires pthreads extension');
	}
	if (!in_array ('acquire', get_class_methods ('ZMQContext')))
		die ('skip');
	if (!in_array ('getsocketcount', get_class_methods ('ZMQContext')))
		die ('skip');
?>
--FILE--
<?php

$threads = 10;

class MyWorker extends Thread {
	public $sendThisBack;

	public function __construct($sendThisBack){
		$this->sendThisBack = $sendThisBack;
	}

	public function run() {
		$context = ZMQContext::acquire();

		$socket = $context->getSocket(ZMQ::SOCKET_PUSH);
		$socket->connect ("inproc://pthreads-test");
		$socket->send($this->sendThisBack);
		
		sleep(2);
	}
}

$context = ZMQContext::acquire();


$socket = $context->getSocket(ZMQ::SOCKET_PULL);
$socket->bind("inproc://pthreads-test");
$socket->setSockOpt(ZMQ::SOCKOPT_HWM, 1000);

$request = array();

for ($i = 0; $i < $threads; $i++) {
	$requests[$i] = new MyWorker("thr_$i");
	$requests[$i]->start();
}

var_dump($context->getSocketCount());

for ($i = 0; $i < $threads; $i++) {
	$requests[$i]->join();
}

for ($i = 0; $i < $threads; $i++) {
	$socket->recv();
}

echo "OK";

--EXPECT--
int(11)
OK