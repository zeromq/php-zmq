<?php

//  The Grasslands Pattern
//
//  The Classic ZeroMQ model, plain text with no protection at all.

//  Create context
$ctx = new ZMQContext();

//  Create and bind server socket
$server = $ctx->getSocket(ZMQ::SOCKET_PUSH);
$server->bind('tcp://*:9000');

//  Create and connect client socket
$client = $ctx->getSocket(ZMQ::SOCKET_PULL);
$client->connect('tcp://127.0.0.1:9000');

//  Send a single message from server to client
$server->send( 'Hello' );
$message = $client->recv();
assert($message === 'Hello');
echo "Grasslands test OK\n";
