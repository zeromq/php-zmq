--TEST--
Test a ZMQAuth can whitelist or blacklist an IP address.
--SKIPIF--
<?php
	require_once __DIR__ . '/skipif.inc';
	require_once __DIR__ . '/skipif-czmq2.inc';
--FILE--
<?php

$context = new ZMQContext();
$auth = new ZMQAuth($context);
var_dump($auth->allow('127.0.0.1') === $auth);
var_dump($auth->deny('192.168.0.1') === $auth);
--EXPECT--
bool(true)
bool(true)
