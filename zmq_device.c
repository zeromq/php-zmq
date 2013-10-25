/*
+-----------------------------------------------------------------------------------+
|  ZMQ extension for PHP                                                            |
|  Copyright (c) 2010-2013, Mikko Koppanen <mkoppanen@php.net>                      |
|  All rights reserved.                                                             |
+-----------------------------------------------------------------------------------+
|  Redistribution and use in source and binary forms, with or without               |
|  modification, are permitted provided that the following conditions are met:      |
|     * Redistributions of source code must retain the above copyright              |
|       notice, this list of conditions and the following disclaimer.               |
|     * Redistributions in binary form must reproduce the above copyright           |
|       notice, this list of conditions and the following disclaimer in the         |
|       documentation and/or other materials provided with the distribution.        |
|     * Neither the name of the copyright holder nor the                            |
|       names of its contributors may be used to endorse or promote products        |
|       derived from this software without specific prior written permission.       |
+-----------------------------------------------------------------------------------+
|  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND  |
|  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED    |
|  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           |
|  DISCLAIMED. IN NO EVENT SHALL MIKKO KOPPANEN BE LIABLE FOR ANY                   |
|  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES       |
|  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;     |
|  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND      |
|  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       |
|  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS    |
|  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                     |
+-----------------------------------------------------------------------------------+
*/

/*
	Based on zeromq 2.1.x devices, which is:
	Copyright (c) 2007-2011 iMatix Corporation
    Copyright (c) 2007-2011 Other contributors as noted in the AUTHORS file
*/

#include "php_zmq.h"
#include "php_zmq_private.h"

static zend_bool php_zmq_invoke_idle_callback (php_zmq_device_object *intern TSRMLS_DC)
{
	zend_bool retval = 0;
	zval **params[1];
	zval *retval_ptr = NULL;

	params [0]              = &intern->user_data;
	intern->fci.params      = params;
	intern->fci.param_count = 1;

	/* Call the cb */
	intern->fci.no_separation  = 1;
	intern->fci.retval_ptr_ptr = &retval_ptr;

	if (zend_call_function(&(intern->fci), &(intern->fci_cache) TSRMLS_CC) == FAILURE) {
		if (!EG(exception)) {
			zend_throw_exception_ex(php_zmq_device_exception_sc_entry_get (), 0 TSRMLS_CC, "Failed to invoke idle callback %s()", Z_STRVAL_P(intern->fci.function_name));
		}
	}
	if (retval_ptr) {
		convert_to_boolean(retval_ptr);
		if (Z_BVAL_P(retval_ptr)) {
			retval = 1;
		}
		zval_ptr_dtor(&retval_ptr);
	}
	return retval;
}

static
int s_capture_message (void *socket, zmq_msg_t *msg, int more)
{
	int rc;
	zmq_msg_t msg_cp;
	rc = zmq_msg_init (&msg_cp);
	if (rc == -1)
		return -1;

	rc = zmq_msg_copy (&msg_cp, msg);
	if (rc == -1) {
		zmq_msg_close (&msg_cp);
		return -1;
	}

	return
		zmq_sendmsg (socket, &msg_cp, more ? ZMQ_SNDMORE : 0);
}


int php_zmq_device(php_zmq_device_object *intern TSRMLS_DC)
{
	void *capture_sock;
	php_zmq_socket_object *front, *back;

	zmq_msg_t msg;
#if ZMQ_VERSION_MAJOR >= 3
	int more;
#else
	int64_t more;
#endif

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0
	int label;
	size_t labelsz = sizeof(label);
#endif

	size_t moresz;
	zmq_pollitem_t items [2];

	int rc = zmq_msg_init (&msg);

	if (rc != 0) {
		return -1;
	}

	front = (php_zmq_socket_object *)zend_object_store_get_object(intern->front TSRMLS_CC);
	back = (php_zmq_socket_object *)zend_object_store_get_object(intern->back TSRMLS_CC);

	items [0].socket = front->socket->z_socket;
	items [0].fd = 0;
	items [0].events = ZMQ_POLLIN;
	items [0].revents = 0;
	items [1].socket = back->socket->z_socket;
	items [1].fd = 0;
	items [1].events = ZMQ_POLLIN;
	items [1].revents = 0;

	capture_sock = NULL;
	if (intern->capture) {
		php_zmq_socket_object *capture = (php_zmq_socket_object *)zend_object_store_get_object(intern->capture TSRMLS_CC);
		capture_sock = capture->socket->z_socket;
	}

	while (1) {

		rc = zmq_poll(&items [0], 2, intern->timeout);
		if (rc < 0) {
			zmq_msg_close (&msg);
			return -1;
		}

		if (rc == 0 && intern->has_callback)
		{
			/* Invoke idle callback */
			if (!php_zmq_invoke_idle_callback (intern TSRMLS_CC)) {
				zmq_msg_close (&msg);
				return 0;
			}
			continue;
		}

		if (items [0].revents & ZMQ_POLLIN) {
			while (1) {

				rc = zmq_recvmsg(items [0].socket, &msg, 0);
				if (rc == -1) {
					zmq_msg_close (&msg);
					return -1;
				}

				moresz = sizeof(more);
				rc = zmq_getsockopt(items [0].socket, ZMQ_RCVMORE, &more, &moresz);
				if (rc < 0) {
					zmq_msg_close (&msg);
					return -1;
				}

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0
				labelsz = sizeof(label);

				rc = zmq_getsockopt(items [0].socket, ZMQ_RCVLABEL, &label, &labelsz);
				if(rc < 0) {
					zmq_msg_close (&msg);
					return -1;
				}

				rc = zmq_sendmsg (items [1].socket, &msg, label ? ZMQ_SNDLABEL : (more ? ZMQ_SNDMORE : 0));
				more = more | label;
#else
				if (capture_sock) {
					rc = s_capture_message (capture_sock, &msg, more);

					if (rc == -1) {
						zmq_msg_close (&msg);
						return -1;
					}
				}
				rc = zmq_sendmsg (items [1].socket, &msg, more ? ZMQ_SNDMORE : 0);
#endif
				if (rc == -1) {
					zmq_msg_close (&msg);
					return -1;
				}

				if (!more)
					break;
			}
		}

		if (items [1].revents & ZMQ_POLLIN) {
			while (1) {
				rc = zmq_recvmsg(items [1].socket, &msg, 0);
				if (rc == -1) {
					zmq_msg_close (&msg);
					return -1;
				}

				moresz = sizeof (more);
				rc = zmq_getsockopt(items [1].socket, ZMQ_RCVMORE, &more, &moresz);
				if (rc < 0) {
					zmq_msg_close (&msg);
					return -1;
				}

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0
				labelsz = sizeof(label);
				rc = zmq_getsockopt(items [1].socket, ZMQ_RCVLABEL, &label, &labelsz);
				if (rc < 0) {
					zmq_msg_close (&msg);
					return -1;
				}

				rc = zmq_sendmsg (items [0].socket, &msg, label ? ZMQ_SNDLABEL : (more ? ZMQ_SNDMORE : 0));
				more = more | label;
#else
				if (capture_sock) {
					rc = s_capture_message (capture_sock, &msg, more);

					if (rc == -1) {
						zmq_msg_close (&msg);
						return -1;
					}
				}
				rc = zmq_sendmsg (items [0].socket, &msg, more ? ZMQ_SNDMORE : 0);
#endif
				if (rc == -1) {
					zmq_msg_close (&msg);
					return -1;
				}

				if (!more)
					break;
			}
		}
	}
	zmq_msg_close (&msg);
	return 0;
}

