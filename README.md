PHP bindings for 0MQ. The documentation is available at http://php.net/zmq

[![Build Status](https://travis-ci.org/mkoppanen/php-zmq.png?branch=master)](https://travis-ci.org/mkoppanen/php-zmq)

The API is roughly as follows:

    <?php

    /* Create new queue object */
    $queue = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, "MySock1");

    /* Connect to an endpoint */
    $queue->connect("tcp://127.0.0.1:5555");

    /* send and receive */
    var_dump($queue->send("hello there, using socket 1")->recv());

    ?>


For installation instructions see http://pecl.php.net/zmq
