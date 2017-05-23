#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([otrv4_toolkit], [0.0.1], [strike@thoughtworks.com])
AC_CONFIG_SRCDIR([src/otr_parse.c])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
# maybe not
AM_PROG_AR

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Checks for libraries.
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.18])
PKG_CHECK_MODULES([LIBOTR4], [libotr4 >= 0.0.1])
PKG_CHECK_MODULES([LIBDECAF], [libdecaf >= 0.0.1])
AM_PATH_LIBGCRYPT(1:1.7.6,,AC_MSG_ERROR(libgcrypt 1.7.6 or newer is required.))

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_PROG_CC_STDC

AX_CFLAGS_GCC_OPTION([-Wall])
AX_CFLAGS_GCC_OPTION([-Werror])
AX_CFLAGS_GCC_OPTION([-Wfatal-errors])
AX_CODE_COVERAGE

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memchr memmove memset stpcpy strchr strstr])

AC_CACHE_SAVE

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile src/test/Makefile])
AC_OUTPUT

