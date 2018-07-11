#include <stdio.h>
#include <stdlib.h>

#include "../debug.h"

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
