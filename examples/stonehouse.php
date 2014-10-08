<?php

//  The Stonehouse Pattern
//
//  Where we allow any clients to connect, but we promise clients
//  that we are who we claim to be, and our conversations won't be
//  tampered with or modified, or spied on.

//  Create context and start authentication engine
$ctx = new ZMQContext();
$auth = new ZMQAuth($ctx);
$auth->allow('127.0.0.1');

//  Tell the authenticator how to handle CURVE requests
$auth->configure(ZMQAuth::AUTH_TYPE_CURVE, '*', ZMQ::CURVE_ALLOW_ANY);

//  We need two certificates, one for the client and one for
//  the server. The client must know the server's public key
//  to make a CURVE connection.
$clientCert = new ZMQCert();
$serverCert = new ZMQCert();
$serverKey = $serverCert->getPublicTxt();

//  Create and bind server socket
$server = $ctx->getSocket(ZMQ::SOCKET_PUSH);
$serverCert->apply($server);
$server->setSockOpt(ZMQ::SOCKOPT_CURVE_SERVER, true);
$server->bind('tcp://*:9000');

//  Create and connect client socket
$client = $ctx->getSocket(ZMQ::SOCKET_PULL);
$clientCert->apply($client);
$client->setSockOpt(ZMQ::SOCKOPT_CURVE_SERVERKEY, $serverKey);
$client->connect('tcp://127.0.0.1:9000');

//  Send a single message from server to client
$server->send('Hello');
$message = $client->recv();
assert($message === 'Hello');
echo "Stonehouse test OK\n";
