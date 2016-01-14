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

#include "php_zmq.h"
#include "php_zmq_private.h"

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef HAVE_TIME_H
#  include <time.h>
#endif

#ifdef HAVE_SYS_TIME_H
#  include <sys/time.h>
#endif

#ifdef HAVE_MACH_MACH_TIME_H
#  include <mach/mach_time.h>
#endif

#if defined(PHP_WIN32)
#  include "win32/time.h"
#endif

static
uint64_t s_backup_clock ()
{
#if defined(HAVE_GETTIMEOFDAY)

	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (uint64_t) (((uint64_t) tv.tv_sec * 1000) + ((uint64_t) tv.tv_usec / 1000));

#endif

	php_error (E_ERROR, "Failed to get current time");
	return 0;
}

/*
	Systems supporting clock_gettime(CLOCK_MONOTONIC)
*/
#if defined(HAVE_CLOCK_GETTIME) && (defined(CLOCK_MONOTONIC_RAW) || defined(CLOCK_MONOTONIC))

struct _php_zmq_clock_ctx_t {};

php_zmq_clock_ctx_t *php_zmq_clock_init ()
{
	return
		malloc (sizeof (php_zmq_clock_ctx_t));
}

uint64_t php_zmq_clock (php_zmq_clock_ctx_t *clock_ctx)
{
	struct timespec ts;
#if defined(CLOCK_MONOTONIC_RAW)
	if (clock_gettime (CLOCK_MONOTONIC_RAW, &ts) == 0) {
#else
	if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0) {
#endif
		return (uint64_t) (((uint64_t) ts.tv_sec * 1000) + ((uint64_t) ts.tv_nsec / 1000000));
	}
	return
		s_backup_clock ();
}

/*
	Mac OS X
*/
#elif defined(HAVE_MACH_ABSOLUTE_TIME)

struct _php_zmq_clock_ctx_t {
	uint64_t scaling_factor;
};

php_zmq_clock_ctx_t *php_zmq_clock_init ()
{
	php_zmq_clock_ctx_t *ctx;
	mach_timebase_info_data_t info;

	if (mach_timebase_info (&info) != 0) {
		return NULL;
	}
	ctx = malloc (sizeof (php_zmq_clock_ctx_t));
	ctx->scaling_factor = (info.numer / info.denom);
	return ctx;
}

uint64_t php_zmq_clock (php_zmq_clock_ctx_t *ctx)
{
	return
		(mach_absolute_time () * ctx->scaling_factor) / 1000000;
}

/*
	Windows systems. Not using QueryPerformanceCounter because of:
	https://www.virtualbox.org/ticket/11951
*/
#elif defined(PHP_WIN32)

struct _php_zmq_clock_ctx_t {
	int      wrap_count;
	uint64_t last_ticks;
};

php_zmq_clock_ctx_t *php_zmq_clock_init ()
{
	return calloc (1, sizeof (php_zmq_clock_ctx_t));
}

static
uint64_t s_get_tick_count (php_zmq_clock_ctx_t *clock_ctx)
{
	uint64_t ticks = (uint64_t) GetTickCount ();

	/* Has the clock wrapped? */
	if (ticks < clock_ctx->last_ticks)
		++clock_ctx->wrap_count;

	clock_ctx->last_ticks = ticks;

	ticks += (uint64_t) clock_ctx->wrap_count * (uint64_t) MAXDWORD;
	return ticks;
}

uint64_t php_zmq_clock (php_zmq_clock_ctx_t *clock_ctx)
{
	return s_get_tick_count (clock_ctx);
}

#elif defined(HAVE_GETTIMEOFDAY)

struct _php_zmq_clock_ctx_t {};

php_zmq_clock_ctx_t *php_zmq_clock_init ()
{
	return malloc (sizeof (php_zmq_clock_ctx_t));
}

static
uint64_t s_get_tick_count (php_zmq_clock_ctx_t *clock_ctx)
{
	uint64_t ticks = (uint64_t) GetTickCount ();

	/* Has the clock wrapped? */
	if (ticks < clock_ctx->last_ticks)
		++clock_ctx->wrap_count;

	clock_ctx->last_ticks = ticks;

	ticks += (uint64_t) clock_ctx->wrap_count * MAX_DWORD;
	return ticks;
}

uint64_t php_zmq_clock (php_zmq_clock_ctx_t *clock_ctx)
{
	return s_backup_clock ();
}

#else
#  error "Cannot find a clock that would work on this platform. Please report a bug"
#endif

void php_zmq_clock_destroy (php_zmq_clock_ctx_t **clock_ctx)
{
	free (*clock_ctx);
}
