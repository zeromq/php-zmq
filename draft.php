<?php

$zmq = new ZeroMQ(ZeroMQ::SOCKET_REQ);
$zmq->setContextOptions(1, 1, true)
    ->connect('tcp://127.0.0.1:5555');


$q = new ZeroMQ();

$zmq = new ZeroMQ(ZeroMQ::SOCKET_REQ);
$socket->setContextOptions(1, 1, true)
         ->connect('tcp://127.0.0.1:5555');

$p = new ZeroMQPoll();
$p->add($socket, ZeroMQ::POLL_OUT | ZeroMQ::POLL_IN);

$queue = new ZeroMQ();

$readable = array();
$writable = array();

while ($p->poll($readable, $writable, -1)) {

    foreach ($readable as $read_sock) {
        try {
            var_dump($queue->setSocket($read_sock)->recv());
        } catch (ZeroMQSocketException $e) {
            echo "ZeroMQSocketException: $e->getMessage()\n";
        } catch (ZeroMQException $e) {
            echo "ZeroMQException: $e->getMessage()\n";
        }
    }

    foreach ($writable as $socket) {
        try {
            var_dump($queue->setSocket($read_sock)->send("Hello!"));
        } catch (ZeroMQSocketException $e) {
            echo "ZeroMQSocketException: $e->getMessage()\n";
        } catch (ZeroMQException $e) {
            echo "ZeroMQException: $e->getMessage()\n";
        }
    }
}

