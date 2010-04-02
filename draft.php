<?php

/* Create new queue object */
$queue = new ZeroMQ();

/* Create persistent socket called 'MySock1' */
$socket1 = new ZeroMQSocket(ZeroMQ::SOCKET_REQ, "MySock1");
$socket1->connect("tcp://127.0.0.1:5555");


/* And another persistent socket called 'MySock2' */
$socket2 = new ZeroMQSocket(ZeroMQ::SOCKET_REQ, "MySock2");
$socket2->connect("tcp://127.0.0.1:5555");

/* Assign socket 1 to the queue, send and receive */
var_dump($queue->setSocket($socket1)
         ->send("hello there, using socket 1")
         ->recv());

/* Assign socket 2 to the queue, send and receive */
var_dump($queue->setSocket($socket2)
         ->send("hello there, using socket 2")
         ->recv());
         
var_dump($socket1->getContextOptions());
var_dump($socket2->getContextOptions());