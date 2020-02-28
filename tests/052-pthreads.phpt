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
	private $sendThisBack;

	public function __construct($sendThisBack){
		$this->sendThisBack = $sendThisBack;
	}

	public function run() {
		$context = ZMQContext::acquire();
		$socket = $context->getSocket(ZMQ::SOCKET_PUSH);
		$socket->connect ("inproc://pthreads-test");
		$socket->send($this->sendThisBack);
		usleep(500 * 1000);
	}
}

class MyServer extends Thread {
	private $threads;
	
	public function __construct($threads){
		$this->threads = $threads;
	}
	
	public function run() {
		$context = ZMQContext::acquire();
		$socket = $context->getSocket(ZMQ::SOCKET_PULL);
		$socket->bind("inproc://pthreads-test");
		$socket->setSockOpt(ZMQ::SOCKOPT_HWM, 1000);
		usleep(500 * 1000);
		
		echo 'Receiving responses' . PHP_EOL;
		$responses = array();
		for ($i = 0; $i < $this->threads; $i++) {
			$responses[] = $socket->recv();
		}
		sort($responses);
		foreach($responses as $response){
			echo $response . PHP_EOL;
		}
	}
}

$server = new MyServer($threads);
$server->start();
echo 'Server started' . PHP_EOL;

$requests = array();
for ($i = 0; $i < $threads; $i++) {
	$requests[$i] = new MyWorker("thr_$i");
	$requests[$i]->start();
}
echo 'Workers started' . PHP_EOL;

for ($i = 0; $i < $threads; $i++) {
	$requests[$i]->join();
}
$server->join();
echo 'All requests pushed' . PHP_EOL;

echo "OK";

--EXPECT--
Server started
Workers started
Receiving responses
thr_0
thr_1
thr_2
thr_3
thr_4
thr_5
thr_6
thr_7
thr_8
thr_9
All requests pushed
OK