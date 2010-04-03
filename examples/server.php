<?php

/*   
    The server waits for messages from the client
    and echoes back the received message
*/
$server = new ZeroMQ();

/* Create socket, request-reply pattern (reply socket) */
$socket = new ZeroMQSocket(ZeroMQ::SOCKET_REP);
$socket->bind("tcp://127.0.0.1:5555");

/* Assign socket */
$server->setSocket($socket);

/* Loop receiving and echoing back */
while ($message = $server->recv()) {
    echo "Got message: $message\n";
    /* echo back the message */
    $server->send($message);  
}
