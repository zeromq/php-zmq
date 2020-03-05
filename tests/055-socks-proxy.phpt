--TEST--
Test socks proxy
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');
if(!@fsockopen('127.0.0.1', 5557, $errCode, $errStr, 0.1))
    die ('skip test requires local SOCKS5 proxy on port 5557');
?>
--FILE--
<?php

// local socks proxy can be enabled by running sshd and also running
// ssh -D 5557 -C -N root@localhost

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$context = new ZMQContext();
$server  = $context->getSocket(ZMQ::SOCKET_REP, null)
               ->bind('tcp://127.0.0.1:5556');
$context = new ZMQContext();
$client  = $context->getSocket(ZMQ::SOCKET_REQ, null);
$client->setSockOpt(ZMQ::SOCKOPT_SOCKS_PROXY, "localhost:5557");
$client ->connect('tcp://127.0.0.1:5556');

$client->sendmsg("Hello world!");

$message = $server->recvmsg();
var_dump($message);
$server->sendmsg($message);

$message = $client->recvmsg();
var_dump($message);

--EXPECT--
string(12) "Hello world!"
string(12) "Hello world!"