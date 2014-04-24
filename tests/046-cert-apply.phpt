--TEST--
Test a ZMQCert can be applied to a ZMQSocket.
--SKIPIF--
<?php

	require_once __DIR__ . '/skipif.inc';

	if (!class_exists('ZMQCert')) {
		die('skip');
	}
--FILE--
<?php

$context = new ZMQContext();
$socket = $context->getSocket(ZMQ::SOCKET_REQ);
$cert = new ZMQCert();
$cert->apply($socket);
--EXPECT--
