noinst_LTLIBRARIES = libotr_ng_toolkit.la

if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src -Wall -g -O0
else
  AM_CFLAGS =-I$(top_srcdir)/src -Wall -O3
endif


libotr_ng_toolkit_la_SOURCES = decode.c helper.c readotr.c readforge.c
libotr_ng_toolkit_la_CFLAGS = $(AM_CFLAGS) @LIBGOLDILOCKS_CFLAGS@ \
                                         @LIBGCRYPT_CFLAGS@ \
                                         @LIBSODIUM_CFLAGS@ \
                                         @LIBOTRNG_CFLAGS@ \
										 @LIBOTR_CFLAGS@
libotr_ng_toolkit_la_LDFLAGS = $(AM_LDFLAGS) @LIBGOLDILOCKS_LIBS@ \
                                           @LIBGCRYPT_LIBS@ \
                                           @LIBSODIUM_LIBS@ \
                                           @LIBOTRNG_LIBS@ \
										   @LIBOTR_LIBS@
