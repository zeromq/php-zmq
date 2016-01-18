--TEST--
Test a ZMQCert can be constructed.
--SKIPIF--
<?php
	require_once __DIR__ . '/skipif.inc';
	require_once __DIR__ . '/skipif-czmq2.inc';
--FILE--
<?php

$cert = new ZMQCert();
var_dump((bool)$cert);

date_default_timezone_set('Europe/London');
$dateTime = new DateTime();

try {
	$cert = new ZMQCert($dateTime);
} catch (ZMQCertException $e) {
	var_dump($e->getMessage());
}
--EXPECT--
bool(true)
string(69) "ZMQCert::__construct() expects parameter 1 to be string, object given"
