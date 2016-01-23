--TEST--
Test curve keypair
--SKIPIF--
<?php
	require_once(dirname(__FILE__) . '/skipif.inc');
	if (!in_array ('curvekeypair', get_class_methods ('zmq')))
		die ('skip curvekeypair not found in libzmq');
?>
--FILE--
<?php

function test_z85_decode_encode($input) {

	$decoded = zmq::z85decode($input);
	$encoded = zmq::z85encode($decoded);

	if ($input !== $encoded) {
		echo "E: test_z85_decode_encode: input=[$input] encoded=[$encoded] decoded=[$decoded]" . PHP_EOL;
	}
}

$keypair = ZMQ::curveKeypair();

test_z85_decode_encode($keypair['public_key']);
test_z85_decode_encode($keypair['secret_key']);


echo "OK";

--EXPECT--
OK