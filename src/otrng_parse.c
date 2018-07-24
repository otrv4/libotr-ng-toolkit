#include <stdio.h>

#include "parse.h"


int main() {
  data_message_s *dst = NULL;
  otrng_header_s *header_msg = NULL;
  char *src = NULL;
  scanf("%s", src);
  printf("--> %s\n", src);
  int result = parse(dst, header_msg, src);

  printf("Data message:\n\n");
  printf("\tType: %d", header_msg->type);
  printf("\tVersion: %d", header_msg->version);
  return result;
}
