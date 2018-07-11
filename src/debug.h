#ifndef DEBUG_H
#define DEBUG_H

#include <libotr-ng/str.h>
#include <stdlib.h>

static inline char *_otrng_memdump(const uint8_t *src, size_t len) {
  if (src == NULL) {
    return otrng_strndup("(NULL)", 6);
  }
  // each char is represented by "0x00, "
  size_t s = len * 6 + len / 8 + 2;
  char *buff = malloc(s);
  char *cursor = buff;
  int i = 0;

  for (i = 0; i < len; i++) {
    if (i % 8 == 0) {
      cursor += sprintf(cursor, "\n");
    }
    cursor += sprintf(cursor, "0x%02x, ", src[i]);
  }

  return buff;
}

#ifdef DEBUG
static inline void otrng_memdump(const uint8_t *src, size_t len) {
  printf("%s\n", _otrng_memdump(src, len));
}
#else
static inline void otrng_memdump(const uint8_t *src, size_t len) {}
#endif

#endif
