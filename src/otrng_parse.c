#include "parse.h"

int main() {
  data_message_s *dst = NULL;
  otrng_header_s *header_msg = NULL;
  const char *src = NULL;
  int src_len = 0;
  int result = parse(dst, header_msg, src, src_len);
  return result;
}
