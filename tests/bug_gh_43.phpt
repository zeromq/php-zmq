--TEST--
Test for Github issue #43
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
?>
--FILE--
<?php

$context = new ZMQContext (1, false);

$sock1 = new ZMQSocket ($context, ZMQ::SOCKET_PUB);
$sock2 = new ZMQSocket ($context, ZMQ::SOCKET_SUB);

$device = new ZMQDevice (0, $sock1, $sock2);

echo "OK";
?>

--EXPECTF--
Warning: ZMQDevice::__construct() expects exactly 2 parameters, 3 given in %s/bug_gh_43.php on line %d
OK