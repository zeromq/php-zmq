--TEST--
Test a ZMQCert can be cloned.
--SKIPIF--
<?php

	require_once __DIR__ . '/skipif.inc';
	require_once __DIR__ . '/skipif-czmq2.inc';
--FILE--
<?php

$cert = new ZMQCert();
$clonedCert = clone $cert;

var_dump($cert->equals($clonedCert));
--EXPECT--
bool(true)
