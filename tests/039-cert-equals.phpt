--TEST--
Test two ZMQCerts can be tested for equality.
--SKIPIF--
<?php

	require_once __DIR__ . '/skipif.inc';

	if (!class_exists('ZMQCert')) {
		die('skip');
	}
--FILE--
<?php

$cert = new ZMQCert();
$newCert = new ZMQCert();

var_dump($cert->equals($cert));
var_dump($newCert->equals($cert));
--EXPECT--
bool(true)
bool(false)
