<?php

/*
    The client sends messages in a tight loop
*/

/* Create new queue object */
$queue = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_PUB);
$queue->connect("tcp://127.0.0.1:5554");

while (1) {
  $queue->send("hello there!");
}
