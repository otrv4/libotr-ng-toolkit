noinst_LTLIBRARIES = libotr_ng_toolkit.la

libotr_ng_toolkit_la_SOURCES = parse.c helper.c read_otr.c readforge.c
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
