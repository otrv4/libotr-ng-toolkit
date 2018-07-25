#include <stdio.h>
#include "parse.h"
#include "readotr.h"
#include "help_functions.h"

int main(int argc, char **argv) {
  char *original_msg = NULL;
  original_msg = readotr(stdin);

  int message_type = otrng_get_message_type(original_msg);
  int result = 1;

if(message_type == MSG_QUERY_STRING){
    printf("QUERY STRING: ");
    for(int i = 0; i < strlen(original_msg); i++){
      printf("%c", original_msg[i]);
    }
  } else if (message_type == MSG_OTR_ENCODED) {
    data_message_s *data_msg = otrng_data_message_new();
    otrng_header_s *header_msg = malloc(sizeof(otrng_header_s));

    result = parse_data_message(data_msg, header_msg, original_msg);
    print_data_message(header_msg, data_msg);

    free(header_msg);
    otrng_data_message_free(data_msg);
  } else if (message_type == MSG_OTR_ERROR) {
    printf("OTR ERROR: ");
    const char *unreadable_msg_error = "Unreadable message";
    const char *not_in_private_error = "Not in private state message";
    const char *encryption_error = "Encryption error";
    const char *malformed_error = "Malformed message";
    char *error_msg = original_msg + strlen(ERROR_PREFIX);

  if (strncmp(error_msg, "ERROR_1:", 8) == 0) {
      printf("%s\n", unreadable_msg_error);
    } else if (strncmp(error_msg, "ERROR_2:", 8) == 0) {
      printf("%s\n", not_in_private_error);
    } else if (strncmp(error_msg, "ERROR_3:", 8) == 0) {
      printf("%s\n", encryption_error);
    } else if (strncmp(error_msg, "ERROR_4:", 8) == 0) {
      printf("%s\n", malformed_error);
    }
  }

  
  return result;
}
