<?php

/*
    The client sends two messages using two different sockets
    and then exits
*/

/* Create new queue object */
$queue = new ZeroMQ();

/* Create persistent socket called 'MySock1' */
$socket1 = new ZeroMQSocket(ZeroMQ::SOCKET_REQ, "MySock1");
$socket1->connect("tcp://127.0.0.1:5555");

/* Assign socket 1 to the queue, send and receive */
var_dump($queue->setSocket($socket1)
         ->send("hello there, using socket 1")
         ->recv());

/* And another persistent socket called 'MySock2' */
$socket1 = new ZeroMQSocket(ZeroMQ::SOCKET_REQ, "MySock2");
$socket1->connect("tcp://127.0.0.1:5555");

/* Assign socket 2 to the queue, send and receive */
var_dump($queue->setSocket($socket1)
         ->send("hello there, using socket 2")
         ->recv());
