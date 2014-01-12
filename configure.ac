#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([dispensary], 1.0)
AC_CONFIG_SRCDIR([src/dispensary.c])
# Checks for programs.
AM_INIT_AUTOMAKE
AC_PROG_CC
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES(DEPS, [gtk+-2.0])
AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)
AC_CONFIG_FILES(Makefile src/Makefile)
# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([strstr])

AC_OUTPUT
