--TEST--
Test for Github issue #59
--SKIPIF--
<?php 
    require_once(dirname(__FILE__) . '/skipif.inc');

	if (!extension_loaded ('pcntl'))
		die("skip");
?>
--FILE--
<?php

include dirname(__FILE__) . '/zeromq_test_helper.inc';
$server = create_server();

// fork a child to execute cmd, in case it crashes
$pid = pcntl_fork();
if ($pid == -1)
{
	die('could not fork');
}
else if ($pid)
{
	// we are the parent
	pcntl_wait($status);
	$exitcode = pcntl_wexitstatus($status);
}
else
	exit(0);

echo "OK";


--EXPECT--
OK