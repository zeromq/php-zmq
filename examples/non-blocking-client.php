<?php

/* Create new queue object */
$queue = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, "MySock1");
$queue->connect("tcp://127.0.0.1:5555");

/* Assign socket 1 to the queue, send and receive */
$retries = 5;
$sending = true;
do {
    try {
        if ($sending) {
            echo "Sending message\n";
            $queue->send("This is a message", ZMQ::MODE_NOBLOCK);
            $sending = false;
        } else {
            echo "Got response: " . $queue->recv(ZMQ::MODE_NOBLOCK) . "\n";
            break;
        }
    } catch (ZMQSocketException $e) {
        if ($e->getCode() === ZMQ::ERR_EAGAIN) {
            echo " - Unable to execute operation, retrying ($retries)\n";
        } else {
            die(" - Error: " . $e->getMessage());
        }
    }
    usleep(5);
} while (1 && --$retries);

?>
