--TEST--
Test a ZMQCert can be saved.
--SKIPIF--
<?php

	require_once __DIR__ . '/skipif.inc';

	if (!class_exists('ZMQCert')) {
		die('skip');
	}
--FILE--
<?php

define('BASE_CERT_DIR', __DIR__ . '/certs');
mkdir(BASE_CERT_DIR);

// #save
$certPath = BASE_CERT_DIR . '/cert';

$cert = new ZMQCert();
$cert->save($certPath);
var_dump(is_file($certPath));
var_dump(is_file($certPath . '_secret'));

unlink($certPath);
unlink($certPath . '_secret');

try {
	$cert->save('/path/to/cert');
} catch (ZMQCertException $e) {
	var_dump($e->getMessage());
}

// #savePublic
$certPath = BASE_CERT_DIR . '/cert_public';

$cert = new ZMQCert();
$cert->savePublic($certPath);
var_dump(is_file($certPath));

unlink($certPath);

try {
	$cert->savePublic('/path/to/cert_public');
} catch (ZMQCertException $e) {
	var_dump($e->getMessage());
}

// #saveSecret
$certPath = BASE_CERT_DIR . '/cert_secret';
$cert->saveSecret($certPath);
var_dump(is_file($certPath));

unlink($certPath);

try {
	$cert->saveSecret('/path/to/cert_secret');
} catch (ZMQCertException $e) {
	var_dump($e->getMessage());
}

rmdir(BASE_CERT_DIR);
--EXPECT--
bool(true)
bool(true)
string(47) "Failed to save the certificate to /path/to/cert"
bool(true)
string(61) "Failed to save the public certificate to /path/to/cert_public"
bool(true)
string(61) "Failed to save the secret certificate to /path/to/cert_secret"
