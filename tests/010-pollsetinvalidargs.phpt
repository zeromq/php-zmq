--TEST--
Test invalid args for ZMQPoll
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

try {
	$poll = new ZMQPoll();
	$poll->add('string here', 0);
} catch (ZMQPollException $e) {
	echo "Got exception\n";
}

try {
	$poll = new ZMQPoll();
	$poll->add(new stdClass(), 0);
} catch (ZMQPollException $e) {
	echo "Got second exception\n";
}

--EXPECT--
Got exception
Got second exception