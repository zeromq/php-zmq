--TEST--
Test a ZMQCert can be applied to a ZMQSocket.
--SKIPIF--
<?php

	require_once __DIR__ . '/skipif.inc';
	require_once __DIR__ . '/skipif-czmq2.inc';
--FILE--
<?php

$context = new ZMQContext();
$socket = $context->getSocket(ZMQ::SOCKET_REQ);
$cert = new ZMQCert();
$cert->apply($socket);
--EXPECT--
