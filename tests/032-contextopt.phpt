--TEST--
Test context options
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
    if(!defined('ZMQ::CTXOPT_MAX_SOCKETS')) die('skip');
?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$context = new ZMQContext();

if (($ims=$context->getOpt(ZMQ::CTXOPT_MAX_SOCKETS))>512) echo "OK\n"; else echo "$ims<=512\n";
var_dump($context->setOpt(ZMQ::CTXOPT_MAX_SOCKETS, 512));
var_dump($context->getOpt(ZMQ::CTXOPT_MAX_SOCKETS));

echo "OK";

--EXPECT--
OK
NULL
int(512)
OK