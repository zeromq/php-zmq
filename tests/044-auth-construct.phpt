--TEST--
Test a ZMQAuth can be constructed.
--SKIPIF--
<?php
	require_once __DIR__ . '/skipif.inc';

	if (!class_exists('ZMQAuth')) {
		die('skip');
	}
--FILE--
<?php

$context = new ZMQContext();
$auth = new ZMQAuth($context);
var_dump((bool)$auth);
--EXPECT--
bool(true)
