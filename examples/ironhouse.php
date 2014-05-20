<?php

//  The Ironhouse Pattern
//
//  Security doesn't get any stronger than this. An attacker is going to
//  have to break into your systems to see data before/after encryption.

// Create context and start authentication engine
$ctx = new ZMQContext();
$auth = new ZMQAuth($ctx);
$auth->allow('127.0.0.1');

//  Tell the authenticator how to handle CURVE requests
$auth->configure(ZMQAuth::AUTH_TYPE_CURVE, '*', '.curve');

//  We'll generate a new client certificate and save the public part
//  in the certificate store (in practice this would be done by hand
//  or some out-of-band process).
$clientCert = new ZMQCert();
mkdir('.curve');
$clientCert->setMeta('name', 'Client test certificate');
$clientCert->savePublic('.curve/testcert.pub');

// Prepare the server certificate as we did in Stonehouse
$serverCert = new ZMQCert();
$serverKey = $serverCert->getPublicTxt();

//  Create and bind server socket
$server = $ctx->getSocket(ZMQ::SOCKET_PUSH);
$serverCert->apply($server);
$server->setSockOpt(ZMQ::SOCKOPT_CURVE_SERVER, true);
$server->bind('tcp://127.0.0.1:9000');

//  Create and connect client socket
$client = $ctx->getSocket(ZMQ::SOCKET_PULL);
$clientCert->apply($client);
$client->setSockOpt(ZMQ::SOCKOPT_CURVE_SERVERKEY, $serverKey);
$client->connect('tcp://127.0.0.1:9000');

//  Send a single message from server to client
$server->send('Hello');
$message = $client->recv();
assert($message === 'Hello');
echo "Ironhouse test OK\n";
