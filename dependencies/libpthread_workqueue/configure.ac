#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([libpthread_workqueue], [0.9.2])
LT_INIT
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CC
AC_CONFIG_FILES([Makefile])
AM_CONDITIONAL([LINUX], [test `uname` = 'Linux'])
ACX_PTHREAD()
AC_CHECK_LIB([rt], [clock_gettime])
LDFLAGS="$LDFLAGS $PTHREAD_LIBS"
CXXFLAGS="$CXXFLAGS $PTHREAD_CFLAGS"
AC_OUTPUT
