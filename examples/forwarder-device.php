<?php

class IdleUserData
{
	protected $_counter = 0;
	
	public function increment ()
	{
		return $this->_counter++;
	}
}

function my_idle_func ($user_data)
{
	echo "Idle function called {$user_data->increment ()} times\n";
}

try {
	$ctx = new ZMQContext (1);

	$frontend = $ctx->getSocket(ZMQ::SOCKET_SUB);
	$frontend->connect("tcp://127.0.0.1:5454");
	$frontend->setSockOpt(ZMQ::SOCKOPT_SUBSCRIBE, "");
	$frontend->setSockOpt(ZMQ::SOCKOPT_LINGER, 0);

	$backend = $ctx->getSocket(ZMQ::SOCKET_PUB);
	$backend->bind("tcp://127.0.0.1:5555");
	$backend->setSockOpt(ZMQ::SOCKOPT_LINGER, 0);
	
	$device = new ZMQDevice($frontend, $backend);
	
	// Return from poll every 5 seconds if there is no activity
	$device->setIdleTimeout (5000);
	
	// Setup callback and user data for callback
	$device->setIdleCallback ('my_idle_func', new IdleUserData ());
	$device->run ();
	
} catch (ZMQException $e) {
	echo "Failed to run the device: " . $e->getMessage() . "\n";
	exit(1);
}
