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

ZEND_EXTERN_MODULE_GLOBALS(php_zmq)

static
zend_bool s_invoke_device_cb (php_zmq_device_cb_t *cb, uint64_t current_ts TSRMLS_DC)
{
	zend_bool retval = 0;
	zval **params[1];
	zval *retval_ptr = NULL;

	params [0]          = &cb->user_data;
	cb->fci.params      = params;
	cb->fci.param_count = 1;

	/* Call the cb */
	cb->fci.no_separation  = 1;
	cb->fci.retval_ptr_ptr = &retval_ptr;

	if (zend_call_function(&(cb->fci), &(cb->fci_cache) TSRMLS_CC) == FAILURE) {
		if (!EG(exception)) {
			char *buf = php_zmq_printable_func (&(cb->fci), &(cb->fci_cache) TSRMLS_CC);

			zend_throw_exception_ex(php_zmq_device_exception_sc_entry_get (), 0 TSRMLS_CC, "Failed to invoke callback %s()", buf);
			efree (buf);
		}
	}
	if (retval_ptr) {
		convert_to_boolean(retval_ptr);
		if (Z_BVAL_P(retval_ptr)) {
			retval = 1;
		}
		zval_ptr_dtor(&retval_ptr);
	}
	cb->scheduled_at = current_ts + cb->timeout;
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

static
int s_calculate_timeout (php_zmq_device_object *intern TSRMLS_DC)
{
	int timeout = -1;
	uint64_t current = php_zmq_clock (ZMQ_G (clock_ctx));

	/* Do we have timer? */
	if (intern->timer_cb.initialized && intern->timer_cb.timeout) {
		/* This is when we need to launch timer */
		timeout = (int) (intern->timer_cb.scheduled_at - current);

		/* If we are tiny bit late, make sure it's asap */
		if (timeout <= 0) {
			return 1 * PHP_ZMQ_TIMEOUT;
		}
	}

	/* Do we have idle callback? */
	if (intern->idle_cb.initialized && intern->idle_cb.timeout) {
		/* Do we need to reduce next timing? */
		int idle_timeout = (int) (intern->idle_cb.scheduled_at - current);

		/* Might happen if we get scheduled tiny bit late */
		if (idle_timeout <= 0) {
			return 1 * PHP_ZMQ_TIMEOUT;
		}

		if (timeout == -1 || idle_timeout < timeout)
			timeout = idle_timeout;
	}

	if (timeout > 0)
		timeout *= PHP_ZMQ_TIMEOUT;

	return timeout;
}


zend_bool php_zmq_device (php_zmq_device_object *intern TSRMLS_DC)
{
	int errno_;
	uint64_t last_message_received;
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
		return 0;
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

	last_message_received = php_zmq_clock (ZMQ_G (clock_ctx));

	intern->timer_cb.scheduled_at = last_message_received + intern->timer_cb.timeout;
	intern->idle_cb.scheduled_at  = last_message_received + intern->idle_cb.timeout;

	while (1) {
		uint64_t current_ts = 0;

		/* Calculate poll_timeout based on idle / timer cb */
		int timeout = s_calculate_timeout (intern TSRMLS_CC);

		rc = zmq_poll(&items [0], 2, timeout);
		if (rc < 0) {
			errno_ = errno;
			zmq_msg_close (&msg);
			errno = errno_;
			return 0;
		}

		current_ts = php_zmq_clock (ZMQ_G (clock_ctx));

		if (rc > 0)
			last_message_received = current_ts;

		/* Do we have a timer callback? */
		if (intern->timer_cb.initialized && intern->timer_cb.timeout > 0) {
			/* Is it timer to call the timer ? */
			if (intern->timer_cb.scheduled_at <= current_ts) {
				if (!s_invoke_device_cb (&intern->timer_cb, current_ts TSRMLS_CC)) {
					zmq_msg_close (&msg);
					return 1;
				}
			}
		}

		/* Do we have a idle callback? */
		if (rc == 0 && intern->idle_cb.initialized && intern->idle_cb.timeout > 0) {
			/* Is it timer to call the idle callback ? */
			if ((current_ts - last_message_received) >= intern->idle_cb.timeout &&
				intern->idle_cb.scheduled_at <= current_ts) {
				if (!s_invoke_device_cb (&intern->idle_cb, current_ts TSRMLS_CC)) {
					zmq_msg_close (&msg);
					return 1;
				}
			}
			continue;
		}

		if (items [0].revents & ZMQ_POLLIN) {
			while (1) {

				rc = zmq_recvmsg(items [0].socket, &msg, 0);
				if (rc == -1) {
					errno_ = errno;
					zmq_msg_close (&msg);
					errno = errno_;
					return 0;
				}

				moresz = sizeof(more);
				rc = zmq_getsockopt(items [0].socket, ZMQ_RCVMORE, &more, &moresz);
				if (rc < 0) {
					errno_ = errno;
					zmq_msg_close (&msg);
					errno = errno_;
					return 0;
				}

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0
				labelsz = sizeof(label);

				rc = zmq_getsockopt(items [0].socket, ZMQ_RCVLABEL, &label, &labelsz);
				if (rc < 0) {
					errno_ = errno;
					zmq_msg_close (&msg);
					errno = errno_;
					return 0;
				}

				rc = zmq_sendmsg (items [1].socket, &msg, label ? ZMQ_SNDLABEL : (more ? ZMQ_SNDMORE : 0));
				more = more | label;
#else
				if (capture_sock) {
					rc = s_capture_message (capture_sock, &msg, more);

					if (rc == -1) {
						errno_ = errno;
						zmq_msg_close (&msg);
						errno = errno_;
						return 0;
					}
				}
				rc = zmq_sendmsg (items [1].socket, &msg, more ? ZMQ_SNDMORE : 0);
#endif
				if (rc == -1) {
					errno_ = errno;
					zmq_msg_close (&msg);
					errno = errno_;
					return 0;
				}

				if (!more)
					break;
			}
		}

		if (items [1].revents & ZMQ_POLLIN) {
			while (1) {
				rc = zmq_recvmsg(items [1].socket, &msg, 0);
				if (rc == -1) {
					errno_ = errno;
					zmq_msg_close (&msg);
					errno = errno_;
					return 0;
				}

				moresz = sizeof (more);
				rc = zmq_getsockopt(items [1].socket, ZMQ_RCVMORE, &more, &moresz);
				if (rc < 0) {
					errno_ = errno;
					zmq_msg_close (&msg);
					return errno_;
				}

#if ZMQ_VERSION_MAJOR == 3 && ZMQ_VERSION_MINOR == 0
				labelsz = sizeof(label);
				rc = zmq_getsockopt(items [1].socket, ZMQ_RCVLABEL, &label, &labelsz);
				if (rc < 0) {
					errno_ = errno;
					zmq_msg_close (&msg);
					errno = errno_;
					return 0;
				}

				rc = zmq_sendmsg (items [0].socket, &msg, label ? ZMQ_SNDLABEL : (more ? ZMQ_SNDMORE : 0));
				more = more | label;
#else
				if (capture_sock) {
					rc = s_capture_message (capture_sock, &msg, more);

					if (rc == -1) {
						errno_ = errno;
						zmq_msg_close (&msg);
						errno = errno_;
						return 0;
					}
				}
				rc = zmq_sendmsg (items [0].socket, &msg, more ? ZMQ_SNDMORE : 0);
#endif
				if (rc == -1) {
					errno_ = errno;
					zmq_msg_close (&msg);
					errno = errno_;
					return 0;
				}

				if (!more)
					break;
			}
		}
	}
	zmq_msg_close (&msg);
	return 0;
}

