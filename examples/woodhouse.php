<?php

//  The Woodhouse Pattern
//
//  It may keep some malicious people out but all it takes is a bit
//  of network sniffing, and they'll be able to fake their way in.

//  Create context and start authentication engine
$ctx = new ZMQContext();
$auth = new ZMQAuth($ctx);
$auth->allow('127.0.0.1');

//  Tell the authenticator how to handle PLAIN requests
$auth->configure(ZMQAuth::AUTH_TYPE_PLAIN, '*', __DIR__ . '/passwords');

//  Create and bind server socket
$server = $ctx->getSocket(ZMQ::SOCKET_PUSH);
$server->setSockOpt(ZMQ::SOCKOPT_PLAIN_SERVER, true);
$server->bind('tcp://*:9000');

//  Create and connect client socket
$client = $ctx->getSocket(ZMQ::SOCKET_PULL);
$client->setSockOpt(ZMQ::SOCKOPT_PLAIN_USERNAME, 'admin');
$client->setSockOpt(ZMQ::SOCKOPT_PLAIN_PASSWORD, 'secret');
$client->connect('tcp://127.0.0.1:9000');

//  Send a single message from server to client
$server->send('Hello');
$message = $client->recv();
assert($message === 'Hello');
echo "Woodhouse test OK\n";
