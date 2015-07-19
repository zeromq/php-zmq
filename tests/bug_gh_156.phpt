--TEST--
Test for GitHub issue 156 (https://github.com/mkoppanen/php-zmq/issues/156)
--DESCRIPTION--
The ZMQ_ROUTER_MANDATORY socket option was introduced in ØMQ v3.2.1 but wasn't
included in the appropriate sections of options/sockopts.xml.

Test that the ZMQ_ROUTER_MANDATORY socket option can be set when using ØMQ
v3.2.1 or higher.
--SKIPIF--
<?php

require_once(__DIR__ . '/skipif.inc');

if (!defined('\\ZMQ::SOCKOPT_ROUTER_MANDATORY')) {
    die('skip');
}

--FILE--
<?php

$context = new ZMQContext();
$socket = $context->getSocket(\ZMQ::SOCKET_ROUTER);
$socket->setSockOpt(\ZMQ::SOCKOPT_ROUTER_MANDATORY, 1);

echo "OK";

--EXPECT--
OK
