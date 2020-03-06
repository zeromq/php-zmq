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

/** {{{ char *php_zmq_libzmq_version()
*/
char *php_zmq_get_libzmq_version() 
{
	char *buffer = NULL;

	int major = 0, minor = 0, patch = 0;
	zmq_version(&major, &minor, &patch);

	spprintf(&buffer, 0, "%d.%d.%d", major, minor, patch);
	return buffer;
}
/* }}} */

/** {{{ zend_long php_zmq_libzmq_version_id()
*/
zend_long php_zmq_get_libzmq_version_id() 
{
	int major = 0, minor = 0, patch = 0;

	zmq_version(&major, &minor, &patch);
	return (major * 10000) + (minor * 100) + patch;
}
/* }}} */

/** {{{ char *php_zmq_printable_func()
*/
char *php_zmq_printable_func (zend_fcall_info *fci, zend_fcall_info_cache *fci_cache)
{
	char *buffer = NULL;

	if (fci->object) {
#if PHP_VERSION_ID < 70000
		spprintf (&buffer, 0, "%s::%s", fci->object->ce->name->val, fci_cache->function_handler->common.function_name);
#else
		spprintf (&buffer, 0, "%s::%s", fci->object->ce->name->val, ZSTR_VAL(fci_cache->function_handler->common.function_name));
#endif
	} else {
		if (Z_TYPE (fci->function_name) == IS_OBJECT) {
			spprintf (&buffer, 0, "%s", Z_OBJCE (fci->function_name)->name->val);
		}
		else {
			spprintf (&buffer, 0, "%s", Z_STRVAL (fci->function_name));
		}
	}
	return buffer;
}
/* }}} */
