--TEST--
Test a ZMQCert can get and set metadata.
--SKIPIF--
<?php

	require_once __DIR__ . '/skipif.inc';

	if (!class_exists('ZMQCert')) {
		die('skip');
	}
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

// If the parameters are incorrect, then it should still return the metadata
// keys.
var_dump($cert->getMetaKeys(123));
--EXPECT--
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
array(2) {
  [0]=>
  string(3) "baz"
  [1]=>
  string(3) "foo"
}
