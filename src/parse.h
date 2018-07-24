#include <stdio.h>
#include <string.h>

#include <libotr/b64.h>

#include <libotr-ng/constants.h>
#include <libotr-ng/data_message.h>
#include <libotr-ng/dh.h>
#include <libotr-ng/otrng.h>

typedef struct {
  uint8_t *b64_msg;
  size_t b64_msg_len;
  int type;
  int version;
  int sender_instance_tag;
  int receiver_instance_tag;
  ec_point_p our_ecdh;
  dh_public_key_p our_dh;
  char nonce[DATA_MSG_NONCE_BYTES];
  uint8_t *ciphertext;
  int ciphertext_len;
  char mac[DATA_MSG_MAC_BYTES];
} encoded_msg_t;

int parse(data_message_s *body_msg, otrng_header_s *header_msg, const char *original_msg);
encoded_msg_t *encoded_message_new();

void encoded_message_destroy(encoded_msg_t *enc_msg);

void encoded_message_free(encoded_msg_t *enc_msg);
