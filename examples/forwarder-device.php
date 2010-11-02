<?php

try {
	$ctx = new ZMQContext(2);

	$frontend = $ctx->getSocket(ZMQ::SOCKET_SUB);
	$frontend->connect("tcp://127.0.0.1:5454");
	$frontend->setSockOpt(ZMQ::SOCKOPT_SUBSCRIBE, "");

	$backend = $ctx->getSocket(ZMQ::SOCKET_PUB);
	$frontend->bind("tcp://127.0.0.1:5555");
	
	new ZMQDevice(ZMQ::DEVICE_FORWARDER, $frontend, $backend);
	
} catch (ZMQException $e) {
	echo "Failed to run the device: " . $e->getMessage() . "\n";
	exit(1);
}
