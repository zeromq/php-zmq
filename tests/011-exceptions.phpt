--TEST--
Test exceptions
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

try {
	throw new ZMQContextException();
} catch (ZMQException $e) {
	echo "1 catched\n";
}

try {
	throw new ZMQSocketException();
} catch (ZMQException $e) {
	echo "2 catched\n";
}

try {
	throw new ZMQPollException();
} catch (ZMQException $e) {
	echo "3 catched\n";
}

--EXPECT--
1 catched
2 catched
3 catched