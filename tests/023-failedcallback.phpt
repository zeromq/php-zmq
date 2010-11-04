--TEST--
Test that failing callback does not add socket to plist
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

function throw_stuff($a, $b) 
{
	throw new Exception("failed");
}

function just_echo($a, $b) 
{
	echo "called just_echo\n";
}

$context = new ZMQContext();

try {
    $socket = $context->getSocket(ZMQ::SOCKET_PUSH, 'test id', 'throw_stuff');
    echo "fail\n";
} catch (Exception $e) {
    echo "success\n";
}

try {
    $socket = $context->getSocket(ZMQ::SOCKET_PUSH, 'test id', 'throw_stuff');
    echo "fail\n";
} catch (Exception $e) {
    echo "success\n";
}

try {
    $socket = $context->getSocket(ZMQ::SOCKET_PUSH, 'test id', 'just_echo');
    echo "success\n";
} catch (Exception $e) {
    echo "fail\n";
}

echo "OK\n";
/**/

try {
    $socket = new ZMQSocket($context, ZMQ::SOCKET_PUSH, 'xx id', 'throw_stuff');
    echo "fail\n";
} catch (Exception $e) {
    echo "success\n";
}

try {
    $socket = new ZMQSocket($context, ZMQ::SOCKET_PUSH, 'xx id', 'throw_stuff');
    echo "fail\n";
} catch (Exception $e) {
    echo "success\n";
}

try {
    $socket = new ZMQSocket($context, ZMQ::SOCKET_PUSH, 'xx id', 'just_echo');
    echo "success\n";
} catch (Exception $e) {
    echo "fail\n";
}


echo "OK\n";

--EXPECTF--
success
success
called just_echo
success
OK
success
success
called just_echo
success
OK

