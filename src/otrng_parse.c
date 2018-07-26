#include <stdio.h>
#include "parse.h"
#include "readotr.h"
#include "helper.h"

int main(int argc, char **argv) {
  char *original_msg = NULL;
  original_msg = readotr(stdin);

  int message_type = otrng_get_message_type(original_msg);
  int result = 1;
  #define WHITESPACE_TAG_BASE_BYTES 16
  #define WHITESPACE_TAG_VERSION_BYTES 8
  if(message_type == MSG_PLAINTEXT) {
    printf("PLAIN TEXT: ");
    print_string(original_msg, strlen(original_msg));
  } else if(message_type == MSG_TAGGED_PLAINTEXT) {
    printf("PLAIN TEXT WITH WHITESPACE TAGS: ");
    print_plaintext_formated(original_msg, strlen(original_msg));
  }else if(message_type == MSG_QUERY_STRING){
    printf("QUERY STRING: ");
    print_string(original_msg, strlen(original_msg));
  } else if (message_type == MSG_OTR_ENCODED) {
    data_message_s *data_msg = otrng_data_message_new();
    otrng_header_s *header_msg = malloc(sizeof(otrng_header_s));

    result = parse_data_message(data_msg, header_msg, original_msg);
    print_data_message(header_msg, data_msg);

    free(header_msg);
    otrng_data_message_free(data_msg);
  } else if (message_type == MSG_OTR_ERROR) {
    print_error_msg(original_msg);
  }

  
  return result;
}
