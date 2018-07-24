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

int parse(encoded_msg_t *dst, const char *src, const int src_len);
encoded_msg_t *encoded_message_new();

void encoded_message_destroy(encoded_msg_t *enc_msg);

void encoded_message_free(encoded_msg_t *enc_msg);
/* begins */
// TODO: this whole section was copied and pasted from libotr-ng in order to
// have this project compiling this need to be changed. Prabably the API of
// libotr-ng needs to change.
int message_contains_tag(const string_p message);
int message_is_query(const string_p message);
int get_message_type(const string_p message);
int otrng_deserialize_uint16(uint16_t *n, const uint8_t *buffer, size_t buflen,
                             size_t *nread);

int otrng_deserialize_uint8(uint8_t *n, const uint8_t *buffer, size_t buflen,
                            size_t *nread);
int extract_header(otrng_header_s *dst, const uint8_t *buffer,
                   const size_t bufflen);
/* ends */
