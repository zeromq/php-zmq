<?php

/* Create new queue object */
$queue = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, "MySock1");
$queue->connect("tcp://127.0.0.1:5555");

/* Assign socket 1 to the queue, send and receive */
$retries = 5;
$sending = true;
$sent    = false;

$queue->setSockOpt (ZMQ::SOCKOPT_LINGER, 1000);

echo "Trying to send message\n";
do {
    try {
        if ($sending) {
            if ($queue->send("This is a message", ZMQ::MODE_DONTWAIT) !== false) {
                echo "Message sent\n";
                $sent    = true;
                $sending = false;
            }
        }
    } catch (ZMQSocketException $e) {
        die(" - Error: " . $e->getMessage());
    }
    usleep (1000);
} while (1 && --$retries);

$retries = 2;
$receiving = true;
$received  = false;

echo "Trying to receive message\n";
do {
    try {
        if ($receiving) {
            $message = $queue->recv (ZMQ::MODE_DONTWAIT);
            
            if ($message) {
                echo "Received message: " . $message . "\n";
                $receiving = false;
                $received = true;
            }
        }
    } catch (ZMQSocketException $e) {
        die(" - Error: " . $e->getMessage());
    }
    sleep (1);
} while (1 && --$retries);

if (!$received) {
    echo "The receive timed out\n";
}

?>
