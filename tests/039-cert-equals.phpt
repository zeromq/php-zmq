--TEST--
Test two ZMQCerts can be tested for equality.
--SKIPIF--
<?php

	require_once __DIR__ . '/skipif.inc';
	require_once __DIR__ . '/skipif-czmq2.inc';

	$cert = new ZMQCert();
	if ($cert->getPublicTxt() === str_repeat("0", 40)) {
		// This means no curve
		die("skip No curve enabled in libczmq");
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
