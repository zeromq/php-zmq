--TEST--
Test socket_monitor
--XFAIL--
Output is too variable at this point. Execute: php 035-monitor.phpt
--FILE--
<?php

error_reporting(E_ALL | E_STRICT);
$url = "tcp://127.0.0.1:7000";

function server($url) {

	$context = new \ZMQContext();
	$socket = $context->getSocket(\ZMQ::SOCKET_REP);
	$monitor = $socket->getSocketMonitor();
	$p = new \ZMQPoll();
	$monitor = $socket->getSocketMonitor();
	$p->add($socket, \ZMQ::POLL_IN);
	$p->add($monitor, \ZMQ::POLL_IN);
	$monitor->connect();
	$socket->bind($url);

	$r_a = $w_a = array();

	$run = true;

	while($run) {

		$rc = $p->poll($r_a, $w_a);

		if($rc) {

			foreach($r_a as $r) {

				if($r === $socket) {

					$ret = $socket->recv();
					printf("server: received %s\n", $ret);
					$socket->send("{$ret}bb");
					$run = false;
				}
				elseif(isset($monitor) && ($r === $monitor) ) {

					$ze = $monitor->read();
					printf("server monitor: received %s\n", print_r($ze, true)); 
				}
			}
		}
	}

	$p->clear();
	$socket->unbind($url);
	$monitor->disconnect();
	unset($monitor);
	unset($socket);
	unset($context);
	exit;
}

$pid = pcntl_fork();

if($pid === 0) {

	server($url);
	exit(0);
}

$context = new \ZMQContext();
$client = $context->getSocket(\ZMQ::SOCKET_REQ);
$p = new \ZMQPoll();
$monitor = $client->getSocketMonitor();
$p->add($client, \ZMQ::POLL_IN);
$p->add($monitor, \ZMQ::POLL_IN);
$monitor->connect();
$client->connect($url);
$client->send("aa", \ZMQ::MODE_DONTWAIT);

$r_a = $w_a = array();

$run = true;

while($run) {

	$rc = $p->poll($r_a, $w_a);

	if($rc) {

		foreach($r_a as $r) {

			if($r === $client) {

				printf("client: %s\n", $client->recv());
			}
			elseif(isset($monitor) && ($r === $monitor) ) {

				$ze = $monitor->read();
				printf("server monitor: %s\n", print_r($ze, true)); 

				if($ze->code === \ZMQEvent::EVENT_DISCONNECTED) {

					$run = false;
				}
			}
		}
	}
}

$p->clear();
$client->disconnect($url);
$monitor->disconnect();
?>
--EXPECT--
