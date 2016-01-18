--TEST--
Test a ZMQCert can get and set metadata.
--SKIPIF--
<?php

	require_once __DIR__ . '/skipif.inc';
	require_once __DIR__ . '/skipif-czmq2.inc';
--FILE--
<?php

$cert = new ZMQCert();
var_dump($cert->getMeta('foo'));
var_dump($cert->getMetaKeys());

$cert->setMeta('foo', 'bar');
var_dump($cert->getMeta('foo'));
var_dump($cert->getMetaKeys());

$cert->setMeta('baz', 'qux');
var_dump($cert->getMetaKeys());

// This should generate an error
var_dump($cert->getMetaKeys(123));
--EXPECTF--
NULL
array(0) {
}
string(3) "bar"
array(1) {
  [0]=>
  string(3) "foo"
}
array(2) {
  [0]=>
  string(3) "baz"
  [1]=>
  string(3) "foo"
}

Warning: ZMQCert::getMetaKeys() expects exactly 0 parameters, 1 given in %s on line %d
NULL
