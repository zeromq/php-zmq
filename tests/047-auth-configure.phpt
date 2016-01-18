--TEST--
Test a ZMQAuth can be configured.
--SKIPIF--
<?php
	require_once __DIR__ . '/skipif.inc';
	require_once __DIR__ . '/skipif-czmq2.inc';
--FILE--
<?php

define('TEST_DIR', __DIR__ . '/tmp');
define('PASSWORDS_FILE', TEST_DIR . '/passwords');
define('CERTS_DIR', TEST_DIR . '/certs');
define('CERT_FILE', CERTS_DIR . '/cert');

if (!file_exists(TEST_DIR)) {
	mkdir(TEST_DIR);
}
if (!file_exists(CERTS_DIR)) {
	mkdir(CERTS_DIR);
}

$context = new ZMQContext();
$auth = new ZMQAuth($context);

// Test a ZMQAuth can be configured to use PLAIN authentication.
touch(PASSWORDS_FILE);
var_dump($auth->configure(ZMQAuth::AUTH_TYPE_PLAIN, '*', PASSWORDS_FILE) === $auth);
unlink(PASSWORDS_FILE);

// Test a ZMQAuth can be configured to use CURVE authentication.
$cert = new ZMQCert();
$cert->save(CERT_FILE);

var_dump($auth->configure(ZMQAuth::AUTH_TYPE_CURVE, '*', CERTS_DIR) === $auth);

// Test ZMQAuth#configure throws an exception when the auth type isn't
// recognised.
try {
	$auth->configure(-1, '*', CERTS_DIR);
} catch (ZMQAuthException $e) {
	var_dump($e->getMessage());
}

unlink(CERT_FILE);
unlink(CERT_FILE . '_secret');
rmdir(CERTS_DIR);
rmdir(TEST_DIR);
--EXPECT--
bool(true)
bool(true)
string(62) "Unknown auth type. Are you using one of the ZMQAuth constants?"
