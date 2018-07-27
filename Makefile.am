SUBDIRS = src src/test
ACLOCAL_AMFLAGS = -I m4

@CODE_COVERAGE_RULES@

noinst_HEADERS = src/decode.h src/readotr.h src/helper.h
bin_PROGRAMS = otrng_parse

COMMON_LD = /usr/local/lib/libotr-ng.la /usr/local/lib/libotr.la @LIBS@ @LIBGCRYPT_LIBS@ @LIBGOLDILOCKS_LIBS@

otrng_parse_SOURCES = src/otrng_parse.c src/decode.c src/readotr.c src/helper.c
otrng_parse_LDADD = $(COMMON_LD)

ci: test mem-check coverage-check install uninstall

test: check
	$(top_builddir)/src/test/test

mem-check: check
	valgrind --error-exitcode=2 --track-origins=yes --trace-children=yes --leak-check=full --suppressions=valgrind.supp $(top_builddir)/src/test/test

coverage-check: test
	@make check-code-coverage

code-style:
	clang-format -style=llvm -i src/*.h src/*.c src/**/*.h src/**/*.c
