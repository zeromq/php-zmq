--TEST--
Test startmonitor
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc');

	if (!in_array ('startmonitor', get_class_methods ('zmqsocket')))
		die ('skip startmonitor not supported in libzmq version');
?>
--FILE--
<?php
$zmq=new ZMQContext();
$mainsok=$zmq->getSocket(ZMQ::SOCKET_REP);
$mainsok->startmonitor('inproc://mainsock.events');
$evsok=$zmq->getSocket(ZMQ::SOCKET_PAIR);
$evsok->type='ev';
$evsok->connect('inproc://mainsock.events');
$mainsok->bind('tcp://127.0.0.1:5566');
$msg=$evsok->recvMulti();
$ev=unpack("Scode/Larg",$msg[0]);
echo $ev['code']."\nOK\n";
?>
--EXPECT--
8
OK
