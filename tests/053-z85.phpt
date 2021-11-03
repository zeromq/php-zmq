--TEST--
Test z85
--SKIPIF--
<?php
	require_once(dirname(__FILE__) . '/skipif.inc');
	if (!in_array ('z85encode', get_class_methods ('zmq')))
		die ('skip z85encode not found in libzmq');
?>
--FILE--
<?php

function test_z85_encode_decode($input) {
	$encoded = zmq::z85encode($input);
	$decoded = zmq::z85decode($encoded);

	if ($input !== $decoded) {
		echo "E: test_z85_encode_decode: input=[$input] encoded=[$encoded] decoded=[$decoded]" . PHP_EOL;
	}
}

function test_z85_encode($input, $expect) {
	if ($expect !== zmq::z85encode($input)) {
		echo "E: test_z85_encode: input=[$input] expect=[$expect]" . PHP_EOL;
	}
}

function test_z85_decode($input, $expect) {
	if ($expect !== zmq::z85decode($input)) {
		echo "E: test_z85_decode: input=[$input] expect=[$expect]" . PHP_EOL;
	}
}

$file = file_get_contents(__DIR__ . '/rose.jpg');
test_z85_encode_decode(substr($file, 0, 128));
test_z85_encode_decode(substr($file, 128, 128));

for ($i = 4; $i <= 256; $i += 4) {
	$str = substr(str_shuffle(str_repeat("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", $i)), 0, $i);
	test_z85_encode_decode($str);
}

// Incorrect length
test_z85_encode('1234567', null);
test_z85_encode('', null);

test_z85_decode('1234567', null);
test_z85_decode('', null);

echo "OK";

--EXPECT--
OK
