--TEST--
Test pollset items
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); 
	if (PHP_VERSION_ID < 70000) {
		die ("skip PHP7 only");
	}

?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$s = create_server();
$poll = new ZMQPoll();

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

$poll->add(create_client(), ZMQ::POLL_IN);
$poll->add($stream, ZMQ::POLL_IN);
$poll->add(create_client(), ZMQ::POLL_IN);

foreach ($poll->items() as $item) {
	unset($item);
}
var_dump($poll->items());
var_dump($poll->clear()->items());

echo "OK";

--EXPECTF--
array(3) {
  ["o:%s"]=>
  object(ZMQSocket)#%d (%d) {
  }
  ["r:%d"]=>
  resource(%d) of type (stream)
  ["o:%s"]=>
  object(ZMQSocket)#%d (%d) {
  }
}
array(0) {
}
OK
