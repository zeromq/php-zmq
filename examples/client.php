<?php

/*
    The client connects to the server, sends a message, 
    receives a reply and then exits.
*/
$client = new ZeroMQ();

$socket = new ZeroMQSocket(ZeroMQ::SOCKET_REQ);
$socket->connect("tcp://127.0.0.1:5555");

/* Assign socket */
$client->setSocket($socket);

/* Loop receiving and echoing back */
$client->send("Hello there!");
$message = $client->recv();

var_dump($message);
