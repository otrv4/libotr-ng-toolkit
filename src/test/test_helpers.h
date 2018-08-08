#include <stdio.h>
#include <stdlib.h>

#include "../debug.h"

#ifndef TEST_HELPERS
#define TEST_HELPERS
#define otrng_toolkit_assert(expr)                                             \
  do {                                                                         \
    if                                                                         \
      G_LIKELY(expr);                                                          \
    else                                                                       \
      g_assertion_message_expr(G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC,    \
                               #expr);                                         \
  } while (0)

static inline void otrng_assert_uint8_equals(const uint8_t *expected,
                                             const uint8_t *actual, int len) {
  for (unsigned int i = 0; i < len; i++) {
    g_assert_cmpint(expected[i], ==, actual[i]);
  }
}

#define otrng_toolkit_assert_cmpmem(s1, s2, len)                               \
  do {                                                                         \
    const uint8_t *_s1_evaled = (uint8_t *)(s1);                               \
    const uint8_t *_s2_evaled = (uint8_t *)(s2);                               \
    const size_t _len_evaled = (len);                                          \
    char *__s1 = _otrng_memdump(_s1_evaled, _len_evaled);                      \
    char *__s2 = _otrng_memdump(_s2_evaled, _len_evaled);                      \
    char *__msg = g_strdup_printf(                                             \
        "assertion failed: (%s)\n\n%s (%p): %s\n\n%s (%p): %s\n",              \
        #s1 " ==  " #s2, #s1, _s1_evaled, __s1, #s2, _s2_evaled, __s2);        \
    if ((_s1_evaled == NULL && _s2_evaled == NULL) ||                          \
        memcmp(_s1_evaled, _s2_evaled, _len_evaled) == 0)                      \
      ;                                                                        \
    else                                                                       \
      g_assertion_message(G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, __msg); \
    free(__s1);                                                                \
    free(__s2);                                                                \
    g_free(__msg);                                                             \
  } while (0)
#endif
