--TEST--
Test unbind
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc'); 
	if (version_compare(ZMQ::LIBZMQ_VER, '4.1.0', '<')) {
		die("skip Unbind doesnt work well before libzqm 4.1.x");
	}
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
    string(17) "inproc://php-test"
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