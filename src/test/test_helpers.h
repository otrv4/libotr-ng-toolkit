#include <stdlib.h>
#include <stdio.h>
#include <decaf.h>
#include <decaf/ed448.h>

static inline void
otrv4_assert_point_equals(const ec_point_t expected, const ec_point_t actual)
{
	g_assert_cmpint(decaf_448_point_eq(expected, actual), !=, 0);
}
