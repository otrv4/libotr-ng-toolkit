#include "parse.h"

int main() {
  encoded_msg_t *dst = NULL;
  char *src = NULL;
  int src_len = 0;
  int result = parse(dst, src, src_len);
  return result;
}
