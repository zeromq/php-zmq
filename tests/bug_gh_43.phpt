--TEST--
Test for Github issue #43
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
?>
--FILE--
<?php

error_reporting(0);

$context = new ZMQContext (1, false);

$sock1 = new ZMQSocket ($context, ZMQ::SOCKET_PUB);
$sock2 = new ZMQSocket ($context, ZMQ::SOCKET_SUB);

try {
    $device = new ZMQDevice ($sock1, $sock1, $sock1, $sock1);
    // on PHP7 and lower
    $lastError = error_get_last();
    if(strpos($lastError['message'], 'ZMQDevice::__construct() expects at most 3 parameters, 4 given') !== false)
     	echo "OK\n";
    else{
        echo "FAIL\n";
        print_r($lastError);
    }
}catch(TypeError $e){
 	echo "OK\n"; // on PHP8
}
--EXPECT--
OK
