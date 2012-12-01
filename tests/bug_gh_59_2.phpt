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

function forkRepWorker()
{
    $pid = pcntl_fork();
    if ($pid != 0) {
        return $pid;
    }

    $context = new ZMQContext();
    $rep = $context->getSocket(\ZMQ::SOCKET_REP);
    $rep->connect('ipc://test2.ipc');

    $msg = $rep->recv();
    $rep->send($msg.'bar');
    sleep(2);
    exit;
}

$context = new ZMQContext(1, false);
$dealer = $context->getSocket(ZMQ::SOCKET_DEALER);

$pids[] = forkRepWorker($dealer);
$pids[] = forkRepWorker($dealer);

$dealer->bind('ipc://test2.ipc');
sleep (1);

$dealer->sendmulti(array('A', '', 'foo'));
$dealer->sendmulti(array('B', '', 'bar'));

$msgs = array();
$msgs[] = $dealer->recvmulti();
$msgs[] = $dealer->recvmulti();

foreach ($pids as $pid) {
    pcntl_waitpid($pid, $status, WUNTRACED);
}

var_dump(count ($msgs));
echo "OK";

--EXPECT--
int(2)
OK