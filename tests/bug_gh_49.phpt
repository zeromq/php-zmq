--TEST--
Test for Github issue #49
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
?>
--FILE--
<?php

$context = new ZMQContext (1, false);
$server = new ZMQSocket ($context, ZMQ::SOCKET_REP);
$server->bind ('inproc://test');

$client = new ZMQSocket ($context, ZMQ::SOCKET_REQ);
$client->connect ('inproc://test');

$poll = new ZMQPoll();

$poll->add ($server, ZMQ::POLL_IN);
$poll->add ($client, ZMQ::POLL_IN);

for ($i = 0; $i < 10; $i++)
{
    $readable = array();
    $writable = array();

    if ($i % 2)
    {
        $server->send ($i);
    }
    else
    {
        $client->send ($i);
    }
    $event = $poll->poll ($readable, $writable);

    if (!$event)
    {
        continue;
    }
    foreach ($readable as $socket)
    {
        $msg = $socket->recv();
        if ($socket === $server)
        {
            echo 'client to server msg:' . $msg . PHP_EOL;
        }
        else
        {
            echo 'server to client msg:' . $msg . PHP_EOL;
        }
    }
}
?>
--EXPECT--
client to server msg:0
server to client msg:1
client to server msg:2
server to client msg:3
client to server msg:4
server to client msg:5
client to server msg:6
server to client msg:7
client to server msg:8
server to client msg:9