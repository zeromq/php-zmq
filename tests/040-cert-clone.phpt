--TEST--
Test a ZMQCert can be cloned.
--SKIPIF--
<?php

	require_once __DIR__ . '/skipif.inc';

	if (!class_exists('ZMQCert')) {
		die('skip');
	}
--FILE--
<?php

$cert = new ZMQCert();
$clonedCert = clone $cert;

var_dump($cert->equals($clonedCert));
--EXPECT--
bool(true)
