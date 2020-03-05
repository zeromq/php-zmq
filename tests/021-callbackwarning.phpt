--TEST--
Test warning in callback
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

error_reporting(0);

function generate_warning($a, $b) 
{
	in_array(1, 1);
}

try {
    $socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'persistent_socket', 'generate_warning');
    // on PHP7 and lower
    $lastError = error_get_last();
    if(strpos($lastError['message'], 'in_array() expects parameter 2 to be array') !== false)
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
