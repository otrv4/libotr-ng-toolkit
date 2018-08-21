SUBDIRS = src src/test
ACLOCAL_AMFLAGS = -I m4

@CODE_COVERAGE_RULES@

bin_PROGRAMS = otrng_parse otrng_mackey

COMMON_LD = src/libotr_ng_toolkit.la @LIBS@ @LIBOTR_LIBS@
COMMON_FLAGS = @LIBOTRNG_CFLAGS@ @LIBOTR_CFLAGS@

otrng_parse_SOURCES = src/otrng_parse.c
otrng_parse_LDADD = $(COMMON_LD)
otrng_parse_CFLAGS = $(COMMON_FLAGS)

otrng_mackey_SOURCES = src/otrng_mackey.c
otrng_mackey_LDADD = $(COMMON_LD)
otrng_mackey_CFLAGS = $(COMMON_FLAGS)

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
