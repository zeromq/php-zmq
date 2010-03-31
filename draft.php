<?php

dl("zeromq.so");

$queue = new ZeroMQ();
$queue->setSocket(new ZeroMQSocket(ZeroMQ::SOCKET_REP, "tcp://lo:5555"));

$message = new ZeroMQMessage("Hello world!");
$queue->send($message);


