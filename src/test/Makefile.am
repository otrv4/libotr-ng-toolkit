check_PROGRAMS = test

test_SOURCES = test.c

test_CFLAGS = $(AM_CFLAGS) $(GLIB_CFLAGS) $(CODE_COVERAGE_CFLAGS) @LIBGOLDILOCKS_CFLAGS@ \
                                                                  @LIBGCRYPT_CFLAGS@ \
                                                                  @LIBOTRNG_CFLAGS@\
                                                                  @LIBOTR_CFLAGS@ \
                                                                  @LIBSODIUM_CFLAGS@
test_LDFLAGS = $(AM_LDFLAGS) $(GLIB_LIBS) $(CODE_COVERAGE_LIBS) @LIBGOLDILOCKS_LIBS@ \
                                                                @LIBGCRYPT_LIBS@ \
                                                                @LIBOTRNG_LIBS@ \
                                                                @LIBOTR_LIBS@ \
                                                                @LIBSODIUM_LIBS@
test_LDADD = $(top_srcdir)/src/libotr_ng_toolkit.la
