<?php

	if (!class_exists('ZMQCert')) {
		die('skip This test requires php-zmq to be compiled with --with-czmq (only CZMQ 2.x supported)');
	}
