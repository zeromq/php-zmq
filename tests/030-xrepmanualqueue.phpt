--TEST--
Test send / recv with a manually created XREQ and XREP device
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
    if(!defined('ZMQ::SOCKOPT_RCVLABEL')) die('skip Only for in libzmq 3.3.0');
?>
--FILE--
<?php

$ctx = new ZMQContext();
$req = new ZMQSocket($ctx, ZMQ::SOCKET_REQ);
$xrep = new ZMQSocket($ctx, ZMQ::SOCKET_XREP);
$xreq = new ZMQSocket($ctx, ZMQ::SOCKET_XREQ);
$rep = new ZMQSocket($ctx, ZMQ::SOCKET_REP);
$xrep->bind('inproc://xrep');
$xreq->bind('inproc://xreq');
$req->connect('inproc://xrep');
$rep->connect('inproc://xreq');
$in = array('hi', 'there');
$req->sendMulti($in);

do {
	$message = $xrep->recv();
	$more = $xrep->getSockOpt(ZMQ::SOCKOPT_RCVMORE);
	if( $xrep->getSockOpt( ZMQ::SOCKOPT_RCVLABEL ) ) {
		$xreq->send( $message, ZMQ::MODE_SNDLABEL );
	} else {
		$xreq->send( $message, $more ? ZMQ::MODE_SNDMORE : 0 );
	}
} while( $more );

$out = $rep->recvMulti();
assert($in == $out);

$rep->sendMulti(array("oh", "hello!"));

do {
	$message = $xreq->recv();
	$more = $xreq->getSockOpt(ZMQ::SOCKOPT_RCVMORE);
	if( $xreq->getSockOpt( ZMQ::SOCKOPT_RCVLABEL ) ) {
		$xrep->send( $message, ZMQ::MODE_SNDLABEL );
	} else {
		$xrep->send( $message, $more ? ZMQ::MODE_SNDMORE : 0 );
	}
} while( $more );

var_dump($req->recvMulti());



--EXPECT--
array(2) {
  [0]=>
  string(2) "oh"
  [1]=>
  string(6) "hello!"
}
