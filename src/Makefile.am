noinst_LTLIBRARIES = libotr_ng_parse.la

if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src -Wall -g -O0
else
  AM_CFLAGS =-I$(top_srcdir)/src -Wall -O3
endif


libotr_ng_parse_la_SOURCES = otrng_parse.c
libotr_ng_parse_la_CFLAGS = $(AM_CFLAGS) @LIBGOLDILOCKS_CFLAGS@
libotr_ng_parse_la_LDFLAGS = $(AM_LDFLAGS) @LIBGOLDILOCKS_LIBS@
