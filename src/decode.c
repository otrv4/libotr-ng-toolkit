#include "decode.h"

int decode_header(otrng_header_s *header_msg, const char *original_msg) {
  size_t decoded_msg_len = 0;
  uint8_t *decoded_msg = NULL;
  if (otrl_base64_otr_decode(original_msg, &decoded_msg, &decoded_msg_len)) {
    return 1;
  }

  if (!otrng_extract_header(header_msg, decoded_msg, decoded_msg_len)) {
    return 1;
  }
  free(decoded_msg);
  return 0;
}

int decode_data_message(data_message_s *body_msg, const char *original_msg) {

  size_t decoded_msg_len = 0;
  uint8_t *decoded_msg = NULL;
  if (otrl_base64_otr_decode(original_msg, &decoded_msg, &decoded_msg_len)) {
    return 1;
  }

  size_t read = 0;
  if (!otrng_data_message_deserialize(body_msg, decoded_msg, decoded_msg_len,
                                      &read)) {
    return 1;
  }

  free(decoded_msg);
  return 0;
}

int decode_identity_message(dake_identity_message_p identity_msg,
                            const char *original_msg) {

  size_t decoded_msg_len = 0;
  uint8_t *decoded_msg = NULL;
  if (otrl_base64_otr_decode(original_msg, &decoded_msg, &decoded_msg_len)) {
    return 1;
  }

  if (!otrng_dake_identity_message_deserialize(identity_msg, decoded_msg,
                                               decoded_msg_len)) {
    return 1;
  }
  free(decoded_msg);
  return 0;
}

int decode_auth_r_message(dake_auth_r_p auth_r_msg, const char *original_msg) {
  size_t decoded_msg_len = 0;
  uint8_t *decoded_msg = NULL;
  if (otrl_base64_otr_decode(original_msg, &decoded_msg, &decoded_msg_len)) {
    free(decoded_msg);
    return 1;
  }
  if (!otrng_dake_auth_r_deserialize(auth_r_msg, decoded_msg,
                                     decoded_msg_len)) {
    return 1;
  }
  free(decoded_msg);
  return 0;
}

int decode_auth_i_message(dake_auth_i_p auth_i_msg, const char *original_msg) {
  size_t decoded_msg_len = 0;
  uint8_t *decoded_msg = NULL;
  if (otrl_base64_otr_decode(original_msg, &decoded_msg, &decoded_msg_len)) {
    return 1;
  }
  if (!otrng_dake_auth_i_deserialize(auth_i_msg, decoded_msg,
                                     decoded_msg_len)) {
    return 1;
  }
  free(decoded_msg);
  return 0;
}
