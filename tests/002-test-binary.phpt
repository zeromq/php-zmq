--TEST--
Test send / recv binary
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$rose = file_get_contents(dirname(__FILE__) . '/rose.jpg');

$server = create_server();
$client = create_client();

$client->sendmsg($rose);

$message = $server->recvmsg();
var_dump(strlen($message));

$server->sendmsg($message);

$message = $client->recvmsg();
var_dump(strlen($message));

var_dump($message === $rose);

--EXPECTF--
int(1580)
int(1580)
bool(true)