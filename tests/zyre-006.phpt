--TEST--
Test [Zyre] Use ZMQSocket, build by ZMQZyre::getSocket, in a ZMQPoll
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipzyre.inc'); ?>
--FILE--
<?php

$ctx = new ZMQContext;

$z1 = new ZMQZyre($ctx);
$z1->start();
$z1->join('ZMQZyreTestGroup');

usleep(100000);

$z2 = new ZMQZyre($ctx);
$z2->start();
$z2->join('ZMQZyreTestGroup');

usleep(100000);

$z1->sendGroup('ZMQZyreTestGroup', 'A');
$z1->sendGroup('ZMQZyreTestGroup', 'B');

$poll = new ZMQPoll;
$poll->add($z2->getSocket(), ZMQ::POLL_IN);

$readable = array();
$writable = array();

for ($i=0; $i<4; $i++) {
try {
   $events = $poll->poll($readable, $writable, -1);
   $errors = $poll->getLastErrors();

    if (count($errors) > 0) {
       foreach ($errors as $error) {
           echo "Error polling object " . $error . "\n";
       }
       die('polling error');
    }
   } catch (ZMQPollException $e) {
       echo "poll failed: " . $e->getMessage() . "\n";
       die('polling exception');
   }

   if ($events > 0) {
       /* Loop through readable objects and recv messages */
       foreach ($readable as $r) {
           // Don't read the Socket use the recv function of zyre
           // Socket will return a multi-part zmq message, instead zyre will parse it and produce an abject
           $obj = $z2->recv();
           var_dump($obj->command);
       }
   }
}
--EXPECTF--
string(5) "ENTER"
string(4) "JOIN"
string(5) "SHOUT"
string(5) "SHOUT"

