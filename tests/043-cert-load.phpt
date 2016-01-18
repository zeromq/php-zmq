--TEST--
Test a ZMQCert can be loaded.
--SKIPIF--
<?php

	require_once __DIR__ . '/skipif.inc';
	require_once __DIR__ . '/skipif-czmq2.inc';
--FILE--
<?php

define('BASE_CERT_DIR', __DIR__ . '/certs');
mkdir(BASE_CERT_DIR);

$certPath = BASE_CERT_DIR . '/cert';
$cert = new ZMQCert();
$cert->save($certPath);

$certCloneEquivalent = new ZMQCert($certPath);
var_dump($certCloneEquivalent->equals($cert));

unlink($certPath);
unlink($certPath . '_secret');

try {
	new ZMQCert('/path/to/cert');
} catch (ZMQCertException $e) {
	var_dump($e->getMessage());
}

rmdir(BASE_CERT_DIR);
--EXPECT--
bool(true)
string(49) "Failed to load the certificate from /path/to/cert"
