#include <stdio.h>
#include <string.h>

#include <libotr/b64.h>
#include <libotr-ng/constants.h>
#include <libotr-ng/data_message.h>
#include <libotr-ng/dh.h>
#include <libotr-ng/otrng.h>

#include "parse.h"

encoded_msg_t *encoded_message_new() {
  encoded_msg_t *ret = malloc(sizeof(encoded_msg_t));
  if (!ret)
    return NULL;

  ret->b64_msg = NULL;
  ret->b64_msg_len = 0;
  ret->ciphertext = NULL;
  ret->ciphertext_len = 0;
  return ret;
}

void encoded_message_destroy(encoded_msg_t *enc_msg) {
  enc_msg->b64_msg_len = 0;
  free(enc_msg->b64_msg);
  enc_msg->b64_msg = NULL;

  enc_msg->ciphertext_len = 0;
  free(enc_msg->ciphertext);
  enc_msg->ciphertext = NULL;

  otrng_dh_mpi_release(enc_msg->our_dh);
}

void encoded_message_free(encoded_msg_t *enc_msg) {
  if (!enc_msg)
    return;

  encoded_message_destroy(enc_msg);

  free(enc_msg);
}

int parse(data_message_s *body_msg, otrng_header_s *header_msg, const char *original_msg) {

  size_t decoded_msg_len = 0;
  uint8_t *decoded_msg = NULL;
  otrl_base64_otr_decode(original_msg, &decoded_msg, &decoded_msg_len);
  printf("Dec len: %zu\n", decoded_msg_len);
  printf("dst len: %zu\n", sizeof(body_msg));
  if (!otrng_extract_header(header_msg, decoded_msg, decoded_msg_len)) {
    puts("extract");
    return 1;
  }
  if (header_msg->type != DATA_MSG_TYPE) {
    puts("tipo da msg");
    return 1;
  }

  printf("Dec len: %zu\n", decoded_msg_len);
  size_t read = 0;
  if (!otrng_data_message_deserialize(body_msg, decoded_msg, decoded_msg_len, &read)) {
    puts("deserialize");
    return 1;
  }

  return 0;
}
