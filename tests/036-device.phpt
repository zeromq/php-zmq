--TEST--
Test device callbacks
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
?>
--FILE--
<?php

function proper_microtime () {
    return round ((microtime (true) * 1000) + 0.5);
}

class CbStateData
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

	public function reset () {
		$this->_counter = 0;
	}
}

$ctx = new ZMQContext ();
$device = new ZMQDevice($ctx->getSocket(ZMQ::SOCKET_SUB), $ctx->getSocket(ZMQ::SOCKET_PUB));

$last_called = proper_microtime ();
$user_data = new CbStateData ('timer');

// Setup callback and user data for callback
$device->setTimerCallback (function ($user_data) use (&$last_called, $device) {
								echo "Triggered for {$device->getTimerTimeout ()}ms timeout" . PHP_EOL;

								$time_elapsed = proper_microtime () - $last_called;

								if ($time_elapsed < $device->getTimerTimeout ()) {
									echo "Called too early, only ${time_elapsed}ms elapsed, expected {$device->getTimerTimeout ()}" . PHP_EOL;
								}
								
								$device->setTimerTimeout ($device->getTimerTimeout () + 50);
								$last_called = proper_microtime ();

								echo "{$user_data->getName ()} function called {$user_data->increment ()} times\n";
								return $user_data->getCount() < 3 ? true : false;
							},
							100,
							$user_data);

// Run first time
$device->run ();

// Run second time
$user_data->reset ();
$device->setTimerTimeout (110);

$device->run ();

echo "OK";
?>
--EXPECT--
Triggered for 100ms timeout
timer function called 1 times
Triggered for 150ms timeout
timer function called 2 times
Triggered for 200ms timeout
timer function called 3 times
Triggered for 110ms timeout
timer function called 1 times
Triggered for 160ms timeout
timer function called 2 times
Triggered for 210ms timeout
timer function called 3 times
OK