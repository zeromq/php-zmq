<?php

define('ZEROMQ_TEST_DSN', 'tcp://127.0.0.1:5566');

function create_server($persistent_id = null) 
{
    $server = new ZeroMQ(ZeroMQ::SOCKET_REP, $persistent_id);
    $server->bind(ZEROMQ_TEST_DSN);

    return $server;
}

function create_client($persistent_id = null) 
{
    $client = new ZeroMQ(ZeroMQ::SOCKET_REQ, $persistent_id);
    $client->connect(ZEROMQ_TEST_DSN);

    return $client;
}