<?php

//  The Strawhouse Pattern
//
//  We allow or deny clients according to their IP address. It may keep
//  spammers and itiots away, but won't stop a real attacker for more
//  than a heartbeat.

//  Create context
$ctx = new ZMQContext();

//  Start an authentication engine for this context. This engine
//  allows or denies incoming connections (talking to the libzmq
//  core over a protocol called ZAP).
$auth = new ZMQAuth($ctx);

//  Whitelist our address; any other address will be rejected
$auth->allow('127.0.0.1');

//  Create and bind server socket
$server = $ctx->getSocket(ZMQ::SOCKET_PUSH);
$server->setSockOpt(ZMQ::SOCKOPT_ZAP_DOMAIN, 'global');
$server->bind('tcp://*:9000');

//  Create and connect client socket
$client = $ctx->getSocket(ZMQ::SOCKET_PULL);
$client->connect('tcp://127.0.0.1:9000');

//  Send a single message from server to client
$server->send('Hello');
$message = $client->recv();
assert($message === 'Hello');
echo "Strawhouse test OK\n";
