SUBDIRS = src src/test
ACLOCAL_AMFLAGS = -I m4

@CODE_COVERAGE_RULES@

noinst_HEADERS = src/decode.h src/readotr.h src/helper.h
bin_PROGRAMS = otrng_parse

COMMON_LD = $(libdir)/libotr-ng.la $(libdir)/libotr.la @LIBS@ @LIBGCRYPT_LIBS@ @LIBGOLDILOCKS_LIBS@
otrng_parse_SOURCES = src/otrng_parse.c src/decode.c src/readotr.c src/helper.c
otrng_parse_LDADD = $(COMMON_LD)

ci: test mem-check

test: check
	$(top_builddir)/src/test/test

VALGRIND_SUPPRESSIONS = \
	valgrind.supp

VALGRIND_ARGS = --track-origins=yes --quiet --error-exitcode=2 --leak-check=full --read-var-info=yes \
	--suppressions=$(VALGRIND_SUPPRESSIONS)

mem-check: check
	valgrind $(VALGRIND_ARGS) $(top_builddir)/src/test/test

coverage-check: test
	@make check-code-coverage

code-style:
	clang-format -style=llvm -i src/*.h src/*.c src/**/*.h src/**/*.c

code-style-doctor: code-style
	git diff --exit-code .
