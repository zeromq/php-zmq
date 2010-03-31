/*
   +----------------------------------------------------------------------+
   | PHP Version 5 / ZeroMQ 	     	     	     	     	          |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Mikko Koppanen                                    |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Mikko Kopppanen <mkoppanen@php.net>                          |
   +----------------------------------------------------------------------+
*/

#ifndef _PHP_ZEROMQ_H_
# define _PHP_ZEROMQ_H_

#define PHP_ZEROMQ_EXTNAME "zeromq"
#define PHP_ZEROMQ_EXTVER "@PACKAGE_VERSION@"

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef ZTS
# include "TSRM.h"
#endif

#include "php.h"

extern zend_module_entry zeromq_module_entry;
#define phpext_zeromq_ptr &zeromq_module_entry

#endif /* _PHP_ZEROMQ_H_ */