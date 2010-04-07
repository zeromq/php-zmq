<?php

/* Create socket, request-reply pattern (reply socket) */
$server = new ZeroMQ(ZeroMQ::SOCKET_REP);
$server->setContextOptions(1, 1, true)
       ->bind("tcp://127.0.0.1:5555");

/* Create new pollset for incoming message */
$poll = new ZeroMQPoll();
$poll->add($server, ZeroMQ::POLL_IN | ZeroMQ::POLL_OUT);

$readable = array();
$writable = array();

while ($poll->poll($readable, $writable, -1)) {

    try {
        foreach ($readable as $r) {
            echo "Received message: " . $r->recv() . "\n";
        }
        
        foreach ($writable as $w) {
            $w->send("Got it!");
        }   
    } catch (Exception $e) {
        echo "Got exception {$e->getMessage()}\n";
    }
}
