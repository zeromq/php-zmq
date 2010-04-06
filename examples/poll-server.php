<?php

/* Create socket, request-reply pattern (reply socket) */
$server = new ZeroMQ(ZeroMQ::SOCKET_REP);
$server->setContextOptions(1, 1, true);
$server->bind("tcp://127.0.0.1:5555");

/* Create new pollset for incoming message */
$pi = new ZeroMQPoll();
$pi->add($server, ZeroMQ::POLL_IN);

/* And another pollset for outgoing messages */
$po = new ZeroMQPoll();
$po->add($server, ZeroMQ::POLL_OUT);

$r = array('sdfsfd');
$w = array();

while ($pi->poll($r, $w, -1)) {
    
    if (count($r) > 0) {
        try {
            echo "Received message: " . $server->recv() . "\n";
        } catch (Exception $e) {
            echo "Got exception {$e->getMessage()}\n";
        }
    
        $po->poll($r, $w, -1);
        if (count($w) > 0) {
            try {
                $server->send("Got it!");
            } catch (Exception $e) {
                echo "Got exception {$e->getMessage()}\n";
            }
        }
    }
}