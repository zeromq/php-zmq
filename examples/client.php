<?php

/*
    The client sends two messages using two different sockets
    and then exits
*/

/* Create new queue object */
$queue = new ZeroMQ();

/* Create persistent socket called 'MySock1' */
$socket = new ZeroMQSocket(ZeroMQ::SOCKET_REQ, "MySock1");
$socket->connect("tcp://127.0.0.1:5555");

/* Assign socket 1 to the queue, send and receive */
var_dump($queue->setSocket($socket)
         ->send("hello there!")
         ->recv());

var_dump($socket->getEndPoints());
