#include <stdio.h>
#include <string.h>

#include <libotr/b64.h>
#include <libotr-ng/constants.h>
#include <libotr-ng/data_message.h>
#include <libotr-ng/dh.h>
#include <libotr-ng/otrng.h>

#include "parse.h"

int parse(data_message_s *body_msg, otrng_header_s *header_msg, const char *original_msg) {

  size_t decoded_msg_len = 0;
  uint8_t *decoded_msg = NULL;
  if (otrl_base64_otr_decode(original_msg, &decoded_msg, &decoded_msg_len)) {
    return 1;
  };

  if (!otrng_extract_header(header_msg, decoded_msg, decoded_msg_len)) {
    return 1;
  }

  if (header_msg->type != DATA_MSG_TYPE) {
    return 1;
  }

  size_t read = 0;
  if (!otrng_data_message_deserialize(body_msg, decoded_msg, decoded_msg_len, &read)) {
    return 1;
  }

  return 0;
}
