PHP_ARG_WITH(zeromq, whether to enable ZeroMQ support,
[  --with-zeromq[=DIR]       Enable Zero Message Queue support. DIR is the prefix to zeromq installation directory.], yes)

if test "$PHP_ZEROMQ" != "no"; then

	AC_MSG_CHECKING(zeromq installation directory)

	if test "$PHP_ZEROMQ" != "yes"; then
		if test -r "$PHP_ZEROMQ/include/zmq.h"; then
			PHP_ZEROMQ_PREFIX=$PHP_ZEROMQ
		fi
	else
		for i in /usr /usr/local /opt /opt/local; do
			test -r "$i/include/zmq.h" && PHP_ZEROMQ_PREFIX=$i && break
		done
	fi
	
	if test -z "$PHP_ZEROMQ_PREFIX"; then
    AC_MSG_ERROR(Unable to find zeromq installation)
  fi

  AC_MSG_RESULT(found in $PHP_ZEROMQ_PREFIX)

  PHP_ADD_LIBRARY_WITH_PATH(zmq, $PHP_ZEROMQ_PREFIX/lib, ZEROMQ_SHARED_LIBADD)
  PHP_ADD_INCLUDE($PHP_ZEROMQ_PREFIX/include)
  PHP_SUBST(ZEROMQ_SHARED_LIBADD)

  PHP_NEW_EXTENSION(zeromq, zeromq.c, $ext_shared)
fi

