PHP_ARG_WITH(zeromq, whether to enable ZeroMQ support,
[  --with-zeromq[=DIR]       Enable Zero Message Queue support. DIR is the prefix to libzmq installation directory.], yes)

if test "$PHP_ZEROMQ" != "no"; then

	AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  if test -z "$PKG_CONFIG"; then
    AC_MSG_RESULT([pkg-config not found])
    AC_MSG_ERROR([Please reinstall the pkg-config distribution])
  fi
	
	ORIG_PKG_CONFIG_PATH=$PKG_CONFIG_PATH

  AC_MSG_CHECKING(libzmq installation)
  if test "$PHP_ZEROMQ" = "yes"; then
    export PKG_CONFIG_PATH=/usr/lib/pkgconfig:/usr/local/lib/pkgconfig:/opt/lib/pkgconfig:/opt/local/lib/pkgconfig
  else
    export PKG_CONFIG_PATH=$PHP_ZEROMQ:$PHP_ZEROMQ/lib/pkgconfig
  fi
	
	if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists libzmq; then
	  PHP_ZEROMQ_LIBS=`$PKG_CONFIG libzmq --libs`
	  PHP_ZEROMQ_INCS=`$PKG_CONFIG libzmq --cflags`
	  
	  PHP_EVAL_LIBLINE($PHP_ZEROMQ_LIBS, ZEROMQ_SHARED_LIBADD)
    PHP_EVAL_INCLINE($PHP_TYRANT_INCS)
    
    AC_MSG_RESULT([yes])
	else
	  AC_MSG_ERROR(Unable to find libzmq installation)
	fi
	
	dnl PHP_ADD_LIBRARY_WITH_PATH(uuid, /usr/lib, ZEROMQ_SHARED_LIBADD)
	
	AC_CHECK_HEADERS([stdint.h],[php_zeromq_have_stdint=yes; break;])
  if test $php_zeromq_have_stdint != "yes"; then
    AC_MSG_ERROR(Unable to find stdint.h)
  fi
  

  PHP_SUBST(ZEROMQ_SHARED_LIBADD)
  PHP_NEW_EXTENSION(zeromq, zeromq.c, $ext_shared)
  PKG_CONFIG_PATH="$ORIG_PKG_CONFIG_PATH"
fi

