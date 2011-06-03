PHP_ARG_WITH(zmq,     whether to enable 0MQ support,
[  --with-zmq[=DIR]   Enable 0MQ support. DIR is the prefix to libzmq installation directory.], yes)

if test "$PHP_ZMQ" != "no"; then

  AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  if test "x$PKG_CONFIG" = "xno"; then
    AC_MSG_RESULT([pkg-config not found])
    AC_MSG_ERROR([Please reinstall the pkg-config distribution])
  fi

  ORIG_PKG_CONFIG_PATH=$PKG_CONFIG_PATH

  AC_MSG_CHECKING(libzmq installation)
  if test "x$PHP_ZMQ" = "xyes"; then
    export PKG_CONFIG_PATH=/usr/lib/pkgconfig:/usr/local/lib/pkgconfig:/opt/lib/pkgconfig:/opt/local/lib/pkgconfig
  else
    export PKG_CONFIG_PATH="$PHP_ZMQ:$PHP_ZMQ/lib/pkgconfig"
  fi

  if $PKG_CONFIG --exists libzmq; then
    PHP_ZMQ_VERSION=`$PKG_CONFIG libzmq --modversion`

    AC_MSG_RESULT([found version $PHP_ZMQ_VERSION])
    PHP_ZMQ_LIBS=`$PKG_CONFIG libzmq --libs`
    PHP_ZMQ_INCS=`$PKG_CONFIG libzmq --cflags`

    PHP_EVAL_LIBLINE($PHP_ZMQ_LIBS, ZMQ_SHARED_LIBADD)
    PHP_EVAL_INCLINE($PHP_ZMQ_INCS)
  else
    AC_MSG_ERROR(Unable to find libzmq installation)
  fi

  AC_CHECK_HEADERS([stdint.h],[php_zmq_have_stdint=yes; break;])
  if test $php_zmq_have_stdint != "yes"; then
    AC_MSG_ERROR(Unable to find stdint.h)
  fi

  PHP_ADD_EXTENSION_DEP(zmq, spl)

  PHP_SUBST(ZMQ_SHARED_LIBADD)
  PHP_NEW_EXTENSION(zmq, zmq.c zmq_pollset.c, $ext_shared)
  PKG_CONFIG_PATH="$ORIG_PKG_CONFIG_PATH"
fi

