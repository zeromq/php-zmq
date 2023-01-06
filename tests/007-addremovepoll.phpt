--TEST--
Test adding / removing items
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

/* Create socket, request-reply pattern (reply socket) */
$s = create_server();
$z = create_client();


/* Create PHP stream socket */
$socket_server = stream_socket_server("tcp://127.0.0.1:5858", $errno, $errstr);

if (!$socket_server) {
	echo "Failed to create socket server: {$errstr}" . PHP_EOL;
	exit (1);
}

$socket_client = stream_socket_client("tcp://127.0.0.1:5858", $errno, $errstr);

if (!$socket_client) {
	echo "Failed to create socket client: {$errstr}" . PHP_EOL;
	exit (1);
}

/* Accept the client connection */
$stream = stream_socket_accept ($socket_server);

/* Write something from client so that connection will be readable and writable */
fwrite($socket_client, "1");

$poll   = new ZMQPoll();
$obj_id = $poll->add($z, ZMQ::POLL_IN);
$fp_id  = $poll->add($stream, ZMQ::POLL_IN | ZMQ::POLL_OUT);

var_dump($obj_id, $fp_id, $poll->count());

$readable = array();
$writable = array();
$poll->poll($readable, $writable, 1000);
var_dump($readable, $writable);

fclose ($stream);
fclose ($socket_client);
fclose ($socket_server);

var_dump($poll->poll($readable, $writable, 1000));
var_dump($poll->getLastErrors());

$poll->remove($fp_id);

$poll->clear();
var_dump($poll->count());

--EXPECTF--
string(34) "o:%s"
string(3) "r:%d"
int(2)
array(1) {
  [0]=>
  resource(%d) of type (stream)
}
array(1) {
  [0]=>
  resource(%d) of type (stream)
}
int(1)
array(1) {
  [0]=>
  string(3) "r:%d"
}
int(0)
