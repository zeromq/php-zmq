--TEST--
Test [Zyre] Object can be instancied multiple time
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipzyre.inc'); ?>
--FILE--
<?php

$ctx = new ZMQContext;
$z1 = new ZMQZyre($ctx);
$z2 = new ZMQZyre($ctx);
$z3 = new ZMQZyre($ctx);
echo "OK";

--EXPECTF--
OK
