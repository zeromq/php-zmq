<?php

class UserData
{
	protected $_counter = 0;
	protected $_name;

	public function __construct ($name) {
	  $this->name = $name;
	}

	public function getName () {
	  return $this->name;
	}

	public function increment ()
	{
		return ++$this->_counter;
	}

	public function getCount () {
	  return $this->_counter;
	}
}

function my_cb_func ($user_data)
{
	echo time () . " {$user_data->getName ()} function called {$user_data->increment ()} times\n";
	return $user_data->getcount() < 5 ? true : false;
}

try {
	$ctx = new ZMQContext (1);

	$frontend = $ctx->getSocket(ZMQ::SOCKET_SUB);
	$frontend->bind("tcp://127.0.0.1:5554");
	$frontend->setSockOpt(ZMQ::SOCKOPT_SUBSCRIBE, "");
	$frontend->setSockOpt(ZMQ::SOCKOPT_LINGER, 0);

	$backend = $ctx->getSocket(ZMQ::SOCKET_PUB);
	$backend->bind("tcp://127.0.0.1:5555");
	$backend->setSockOpt(ZMQ::SOCKOPT_LINGER, 0);

	$device = new ZMQDevice($frontend, $backend);

	// Setup callback and user data for callback
	$device->setIdleCallback ('my_cb_func', 2000, new UserData ('idle'));
	$device->setTimerCallback ('my_cb_func', 4000, new UserData ('timer'));
	$device->run ();
	
} catch (ZMQException $e) {
	echo "Failed to run the device: " . $e->getMessage() . "\n";
	exit(1);
}
