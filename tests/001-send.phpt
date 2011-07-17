--TEST--
Test send / recv
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$server = create_server();
$client = create_client();

$client->sendmsg("Hello world!");

$message = $server->recvmsg();
var_dump($message);
$server->sendmsg($message);

$message = $client->recvmsg();
var_dump($message);

--EXPECT--
string(12) "Hello world!"
string(12) "Hello world!"