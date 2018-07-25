#include <stdio.h>
#include "parse.h"
#include "readotr.h"
#include "help_functions.h"

int main(int argc, char **argv) {
  char *original_msg = NULL;
  original_msg = readotr(stdin);

  data_message_s *data_msg = otrng_data_message_new();
  otrng_header_s *header_msg = malloc(sizeof(otrng_header_s));

  int result = parse_data_message(data_msg, header_msg, original_msg);
  print_data_message(header_msg, data_msg);
  
  free(header_msg);
  otrng_data_message_free(data_msg);
  return result;
}
