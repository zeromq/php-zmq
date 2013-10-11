--TEST--
Test unbind
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
	if (!in_array ('unbind', get_class_methods ('zmqsocket')))
		die ('skip unbind not supported in libzmq version');
?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';

$s = create_server();
$endpoints = $s->getendpoints();
var_dump($endpoints);

foreach ($endpoints['bind'] as $dsn) {
	$s->unbind($dsn);
}

var_dump ($s->getendpoints());
echo "OK";

--EXPECT--
array(2) {
  ["connect"]=>
  array(0) {
  }
  ["bind"]=>
  array(1) {
    [0]=>
    string(20) "tcp://127.0.0.1:5566"
  }
}
array(2) {
  ["connect"]=>
  array(0) {
  }
  ["bind"]=>
  array(0) {
  }
}
OK