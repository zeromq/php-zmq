/*
+-----------------------------------------------------------------------------------+
|  ZMQ extension for PHP                                                            |
|  Copyright (c) 2010-2016, Mikko Koppanen <mkoppanen@php.net>                      |
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

#include "php_zmq.h"
#include "php_zmq_private.h"

#ifndef PHP_ZMQ_SHARED_CONTEXT_THREADS
# define PHP_ZMQ_SHARED_CONTEXT_THREADS 1
#endif

static
	void *s_ctx;

static
	int s_ctx_socket_count = 0;

static
	int s_ctx_pid = 0;

#ifdef ZTS
static
	MUTEX_T s_ctx_mutex;

static
zend_bool s_shared_ctx_init()
{
	if (!s_ctx) {
		s_ctx_mutex = tsrm_mutex_alloc();
		s_ctx_pid   = getpid();
		s_ctx       = zmq_init(PHP_ZMQ_SHARED_CONTEXT_THREADS);
	}
	return (s_ctx != NULL);
}

static
zend_bool s_shared_ctx_lock()
{
	if (!s_ctx_mutex) {
		return 0;
	}

	return tsrm_mutex_lock(s_ctx_mutex) == 0;
}

static
zend_bool s_shared_ctx_unlock()
{
	if (!s_ctx_mutex) {
		return 0;
	}
	return tsrm_mutex_unlock(s_ctx_mutex) == 0;
}

static
void s_shared_ctx_destroy()
{
	if (s_shared_ctx_lock()) {
		if (s_ctx && s_ctx_pid == getpid()) {
			MUTEX_T tmp_mutex = s_ctx_mutex;
			s_ctx_mutex = NULL;

			zmq_term(s_ctx);
			s_ctx     = NULL;
			s_ctx_pid = -1;

			tsrm_mutex_unlock(tmp_mutex);
			tsrm_mutex_free(tmp_mutex);

			s_ctx_mutex = NULL;
			s_ctx_pid   = -1;
			return;
		}
		else {
			s_shared_ctx_unlock();
		}
	}
}

#else

static
zend_bool s_shared_ctx_init()
{
	s_ctx = zmq_init(PHP_ZMQ_SHARED_CONTEXT_THREADS);
	s_ctx_pid = getpid();
	return (s_ctx != NULL);
}

static
zend_bool s_shared_ctx_lock()
{
	return 1;
}
static
zend_bool s_shared_ctx_unlock()
{
	return 1;
}

static
void s_shared_ctx_destroy() 
{
	if (s_ctx && s_ctx_pid == getpid()) {
		zmq_term(s_ctx);

		s_ctx     = NULL;
		s_ctx_pid = -1;
	}
}
#endif

zend_bool php_zmq_shared_ctx_init()
{
	return
		s_shared_ctx_init();
}

void php_zmq_shared_ctx_assign_to(php_zmq_context *context)
{
	if (s_shared_ctx_lock()) {
		context->z_ctx = s_ctx;
		s_shared_ctx_unlock();
	}
}

void php_zmq_shared_ctx_destroy()
{
	if (php_zmq_shared_ctx_socket_count() > 0) {
		php_error_docref(NULL, E_WARNING, "php_zmq_shared_ctx_socket_count() > 0, please report a bug");
	}
	s_shared_ctx_destroy();
}

int php_zmq_shared_ctx_socket_count()
{
	int value = 0;

	if (s_shared_ctx_lock()) {
		value = s_ctx_socket_count;
		s_shared_ctx_unlock();
	}
	return value;
}

void php_zmq_shared_ctx_socket_count_incr()
{
	if (s_shared_ctx_lock()) {
		s_ctx_socket_count++;
		s_shared_ctx_unlock();
	}
}

void php_zmq_shared_ctx_socket_count_decr()
{
	if (s_shared_ctx_lock()) {
		s_ctx_socket_count--;
		s_shared_ctx_unlock();
	}
}



