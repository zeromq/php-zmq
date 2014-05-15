--TEST--
Test id2fd
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc');

	if (!in_array ('id2fd', get_class_methods ('zmqsocket')))
		die ('skip id2fd not supported in libzmq version');
?>
--FILE--
<?php
$zmq=new ZMQContext();
$ssock=$zmq->getSocket(ZMQ::SOCKET_ROUTER);
$csock=$zmq->getSocket(ZMQ::SOCKET_REQ);
$ssock->bind('tcp://127.0.0.1:5566');
$csock->connect('tcp://127.0.0.1:5566');
$csock->send("test");
$msg=$ssock->recvMulti();
echo ($ssock->id2fd($msg[0])>0?'OK':'FAIL')."\n";
$msg[2]='ok';
$ssock->sendMulti($msg);
$csock->recv();
echo "DONE\n";
?>
--EXPECT--
OK
DONE
