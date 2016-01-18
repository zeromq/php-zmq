--TEST--
Test a ZMQCert can be saved.
--SKIPIF--
<?php

	require_once __DIR__ . '/skipif.inc';
	require_once __DIR__ . '/skipif-czmq2.inc';
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

// #savePublic
$certPath = BASE_CERT_DIR . '/cert_public';

$cert = new ZMQCert();
$cert->savePublic($certPath);
var_dump(is_file($certPath));

unlink($certPath);

// #saveSecret
$certPath = BASE_CERT_DIR . '/cert_secret';
$cert->saveSecret($certPath);
var_dump(is_file($certPath));

unlink($certPath);

rmdir(BASE_CERT_DIR);
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
