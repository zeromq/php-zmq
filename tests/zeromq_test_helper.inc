<?php

define('ZEROMQ_TEST_DSN', 'tcp://127.0.0.1:5566');

function create_server($persistent_id = null) 
{
    $server_socket = new ZeroMQSocket(ZeroMQ::SOCKET_REP, $persistent_id);
    $server_socket->bind(ZEROMQ_TEST_DSN);
    
    $server = new ZeroMQ();
    $server->setSocket($server_socket);
    
    return $server;
}

function create_client($persistent_id = null) 
{
    $socket = new ZeroMQSocket(ZeroMQ::SOCKET_REQ, $persistent_id);
    $socket->connect(ZEROMQ_TEST_DSN);

    $client = new ZeroMQ();
    $client->setSocket($socket);
    
    return $client;
}