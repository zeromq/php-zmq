--TEST--
Test for Github issue #165
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php

$context = new ZMQContext (1, false);
$server = new ZMQSocket ($context, ZMQ::SOCKET_PUB);
$server->bind ('inproc://test');

$fd = $server->getSockOpt(ZMQ::SOCKOPT_FD);

$read   = array($fd);
$write  = NULL;
$except = NULL;
stream_select($read, $write, $except, 0);

echo "OK";
?>
--EXPECT--
OK
