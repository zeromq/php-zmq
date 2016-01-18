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

class MyWorker extends Thread {
	public $sendThisBack;

	public function __construct($sendThisBack){
		$this->sendThisBack = $sendThisBack;
	}

	public function run() {
		$context = ZMQContext::acquire();
		var_dump($context->getSocketCount());

		$socket = $context->getSocket(ZMQ::SOCKET_PAIR);
		$socket->connect ("inproc://pthreads-test");
		$socket->send($this->sendThisBack);
	}
}

$context = ZMQContext::acquire();
var_dump($context->getSocketCount());

$socket = $context->getSocket(ZMQ::SOCKET_PAIR);
$socket->bind("inproc://pthreads-test");

$payload = "Hello from the other side";
$request = new MyWorker($payload);
 
if ($request->start()) {
	$request->join();
	var_dump ($socket->recv());
}

echo "OK";

--EXPECT--
int(0)
int(1)
string(25) "Hello from the other side"
OK