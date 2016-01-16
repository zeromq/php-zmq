--TEST--
Test getting persistent id
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$client = create_server('hello');
var_dump($client->getPersistentId());

--EXPECT--
string(5) "hello"