<?php

$socket = new ZeroMQSocket(ZeroMQ::SOCKET_REQ, "MySock1");
$socket->setSockOpt(ZeroMQ::SOCKOPT_SNDBUF, 0)
       ->connect("tcp://127.0.0.1:5555");

$queue = new ZeroMQ();
$queue->setSocket($socket);

$message = new ZeroMQMessage("Hello world!");

for ($i = 0; $i < 1000; $i++) {
    $queue->send($message);
    var_dump($queue->recv()->getMessage());
}