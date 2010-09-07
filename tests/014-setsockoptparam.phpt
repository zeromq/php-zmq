--TEST--
Test setSockOpt param type
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$poll = new ZMQPoll();
$ctx  = new ZMQContext();
$sock = new ZMQSocket($ctx, ZMQ::SOCKET_REP);

$test = "value";

$sock->setSockOpt(ZMQ::SOCKOPT_SWAP, $test);
echo gettype($test) . "\n";

echo "done\n";


--EXPECT--
string
done