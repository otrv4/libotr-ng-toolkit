check_PROGRAMS = test

test_SOURCES = test.c

test_CFLAGS = $(AM_CFLAGS) $(GLIB_CFLAGS) @LIBGCRYPT_CFLAGS@
test_LDFLAGS = $(AM_LDFLAGS) $(GLIB_LIBS) @LIBGCRYPT_LIBS@
test_LDADD = $(top_srcdir)/src/libotrv4_parse.la
