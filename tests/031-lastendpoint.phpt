--TEST--
Test last endpoint
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
    if(!defined('ZMQ::SOCKOPT_LAST_ENDPOINT')) die('skip');
?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$context = new ZMQContext();
$server  = $context->getSocket(ZMQ::SOCKET_REP)
                   ->bind("inproc://hello-there");
$endpoint = $server->getSockopt(ZMQ::SOCKOPT_LAST_ENDPOINT);

var_dump($endpoint);

echo "OK";

--EXPECT--
string(20) "inproc://hello-there"
OK