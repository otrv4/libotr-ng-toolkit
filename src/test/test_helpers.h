#include <decaf.h>
#include <decaf/ed448.h>
#include <stdio.h>
#include <stdlib.h>

#include "../debug.h"

#define otrv4_assert_cmpmem(s1, s2, len)                                       \
  do {                                                                         \
    char *__s1 = _otrv4_memdump((const uint8_t *)s1, len);                     \
    char *__s1 = _otrv4_memdump((const uint8_t *)s2, len);                     \
    char *__msg = g_strdup_printf(                                             \
        "assertion failed: (%s)\nEXPECTED (%p): %s\nACTUAL (%p): %s\n",        \
        #s1 " ==  " #s2, s1, __s1, s2, __s2);                                  \
    if (memcmp(s1, s2, len) == 0)                                              \
      ;                                                                        \
    else                                                                       \
      g_assertion_message(G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, __msg); \
    free(__s1);                                                                \
    free(__s2);                                                                \
    g_free(__msg);                                                             \
  } while (0)

#define otrv4_assert(expr)                                                     \
  do {                                                                         \
    if                                                                         \
      G_LIKELY(expr);                                                          \
    else                                                                       \
      g_assertion_message_expr(G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC,    \
                               #expr);                                         \
  } while (0)

static inline void otrv4_assert_uint8_equals(const uint8_t *expected,
                                             const uint8_t *actual, int len) {
  for (unsigned int i = 0; i < len; i++) {
    g_assert_cmpint(expected[i], ==, actual[i]);
  }
}

static inline void otrv4_assert_point_equals(const ec_point_t expected,
                                             const ec_point_t actual) {
  g_assert_cmpint(decaf_448_point_eq(expected, actual), !=, 0);
}
