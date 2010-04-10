<?php

/* Create socket, request-reply pattern (reply socket) */
$server = new ZeroMQ(ZeroMQ::SOCKET_REP);
$server->setContextOptions(1, 1, true)
       ->bind("tcp://127.0.0.1:5555");

/* Create new pollset for incoming message */
$poll = new ZeroMQPoll();
$poll->add($server, ZeroMQ::POLL_IN | ZeroMQ::POLL_OUT);

/* Initialise readable and writable arrays */
$readable = array();
$writable = array();

/* Poll until there is something to do */
while (true) {
    
    $events = $poll->poll($readable, $writable, -1);
    
    if ($events > 0) {
        try {
            /* Loop through readable objects and recv messages */
            foreach ($readable as $r) {
                echo "Received message: " . $r->recv() . "\n";
            }
        
            /* Loop through writable and send back messages */
            foreach ($writable as $w) {
                $w->send("Got it!");
            }   
        } catch (Exception $e) {
            echo "Got exception {$e->getMessage()}\n";
        }
    }
}
