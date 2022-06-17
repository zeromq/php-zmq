--TEST--
Test device callbacks
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
?>
--FILE--
<?php

function proper_microtime () {
    return round ((microtime (true) * 1000));
}

class CbStateData
{
	protected $_counter = 0;
	protected $_name;

	public function __construct ($name) {
	  $this->_name = $name;
	}

	public function getName () {
	  return $this->_name;
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

class test {
	function foo ($user_data) {
		return false;
	}
}

$test = new test ();

$ctx = new ZMQContext ();
$device = new ZMQDevice($ctx->getSocket(ZMQ::SOCKET_SUB), $ctx->getSocket(ZMQ::SOCKET_PUB));

$last_called = proper_microtime ();
$user_data = new CbStateData ('timer');

$orig_cb = function ($user_data) use (&$last_called, $device) {
				echo "Triggered for {$device->getTimerTimeout ()}ms timeout" . PHP_EOL;

				$time_elapsed = (proper_microtime () - $last_called) + 1;

				if ($time_elapsed < $device->getTimerTimeout ()) {
					echo "Called too early, only {$time_elapsed}ms elapsed, expected {$device->getTimerTimeout ()}" . PHP_EOL;
				}

				$device->setTimerTimeout ($device->getTimerTimeout () + 50);
				$last_called = proper_microtime ();

				echo "{$user_data->getName ()} function called {$user_data->increment ()} times\n";
				return $user_data->getCount() < 3 ? true : false;
			};

// Setup callback and user data for callback
$device->setTimerCallback ($orig_cb, 100, $user_data);

// Run first time
$device->run ();

$device->setTimerCallback (array ($test, 'foo'), 100, $user_data);
$device->setTimerCallback (array ($test, 'foo'), 100, $user_data);
$device->setTimerCallback ($orig_cb, 100, $user_data);
sleep (1);

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
