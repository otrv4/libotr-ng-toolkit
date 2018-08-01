#include <stdio.h>

#include <libotr-ng/dake.h>

#include "decode.h"
#include "helper.h"
#include "readotr.h"

int main(int argc, char **argv) {
  char *original_msg = NULL;
  original_msg = readotr(stdin);

  int message_type = otrng_get_message_type(original_msg);
  int result = 1;

  if (message_type == MSG_PLAINTEXT) {
    printf("PLAIN TEXT: ");
    print_string(original_msg, strlen(original_msg));

  } else if (message_type == MSG_TAGGED_PLAINTEXT) {
    printf("PLAIN TEXT WITH WHITESPACE TAGS: ");
    print_plaintext_formated(original_msg, strlen(original_msg));

  } else if (message_type == MSG_QUERY_STRING) {
    printf("QUERY STRING: ");
    print_string(original_msg, strlen(original_msg));

  } else if (message_type == MSG_OTR_ENCODED) {
    otrng_header_s *header_msg = malloc(sizeof(otrng_header_s));

    if (!header_msg) {
      return 1;
    }

    result = decode_header(header_msg, original_msg);

    if (header_msg->type == IDENTITY_MSG_TYPE) {
      dake_identity_message_p identity_msg;
      result = decode_identity_message(identity_msg, original_msg);
      print_identity_message(header_msg, identity_msg);

    } else if (header_msg->type == AUTH_R_MSG_TYPE) {
      dake_auth_r_p auth_r_msg;
      result = decode_auth_r_message(auth_r_msg, original_msg);
      print_auth_r(header_msg, auth_r_msg);

    } else if (header_msg->type == AUTH_I_MSG_TYPE) {
      dake_auth_i_p auth_i_msg;
      result = decode_auth_i_message(auth_i_msg, original_msg);
      print_auth_i(header_msg, auth_i_msg);

    } else if (header_msg->type == DATA_MSG_TYPE) {
      data_message_s *data_msg = otrng_data_message_new();
      result = decode_data_message(data_msg, original_msg);
      print_data_message(header_msg, data_msg);
      otrng_data_message_free(data_msg);

    } else {
      printf("Error while trying to parse encoded message\n");
      return 1;
    }

    free(header_msg);
  } else if (message_type == MSG_OTR_ERROR) {
    printf("OTR ERROR: ");
    print_string(original_msg, strlen(original_msg));

  } else {
    printf("Error: not valid OTRv4 message!\n");
    return 1;
  }

  return result;
}
