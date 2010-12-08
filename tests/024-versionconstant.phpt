--TEST--
Test retrieving version
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

echo strlen(ZMQ::LIBZMQ_VER) > 0 && strpos(ZMQ::LIBZMQ_VER, ".") !== false ? "OK" : FAIL;

--EXPECT--
OK