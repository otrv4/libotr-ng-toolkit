#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([otrv4_toolkit], [0.0.1], [otrv4-dev@autonomia.digital])
AC_CONFIG_SRCDIR([src/otrng_parse.c])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([.])
AM_SILENT_RULES([no])

# Add debug support
AC_ARG_ENABLE(debug,
  AS_HELP_STRING(
    [--enable-debug],
    [enable debugging, default: no]),
    [case "${enableval}" in
      yes) debug=true ;;
      no)  debug=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
    esac],
    [debug=false])
AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
AM_COND_IF(DEBUG,
    AC_DEFINE(DEBUG, 1, [Define to 0 if this is a release build]),
    AC_DEFINE(DEBUG, 0, [Define to 1 or higher if this is a debug build]))

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AM_PROG_AR

dnl Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

dnl Checks for libraries.
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.18])
PKG_CHECK_MODULES([LIBGOLDILOCKS], [libgoldilocks >= 0.0.1])
PKG_CHECK_MODULES([LIBSODIUM], [libsodium >= 1.0.0])
AM_PATH_LIBGCRYPT(1:1.7.6,,AC_MSG_ERROR(libgcrypt 1.7.6 or newer is required.))
AM_PATH_LIBOTR(4.0.0,,AC_MSG_ERROR(libotr 4.x >= 4.0.0 is required.))
PKG_CHECK_MODULES([LIBOTRNG], [libotr-ng >= 0.0.1])

dnl Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h])

dnl Checks for typedefs, structures, and compiler characteristics.
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
AX_CFLAGS_GCC_OPTION([-Wformat])
AX_CFLAGS_GCC_OPTION([-Wfatal-errors])
AX_CODE_COVERAGE

dnl Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memchr memmove memset stpcpy strchr strstr])

AC_CACHE_SAVE

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile src/test/Makefile])
AC_OUTPUT
