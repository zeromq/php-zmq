--TEST--
Test that callback is only called on new socket
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'persistent_socket', 'bind_callback');
$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'persistent_socket', 'bind_callback');
$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'persistent_socket', 'bind_callback');
$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'persistent_socket', 'bind_callback');
$socket = new ZMQSocket(new ZMQContext(), ZMQ::SOCKET_REQ, 'persistent_socket', 'bind_callback');

$array = $socket->getEndpoints();

echo count($array['bind']) . "\n";
echo "OK";

--EXPECT--
1
OK