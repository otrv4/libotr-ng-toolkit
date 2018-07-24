#include <stdio.h>
#include <string.h>

#include <libotr/b64.h>

#include "parse.h"
#include <libotr-ng/constants.h>
#include <libotr-ng/data_message.h>
#include <libotr-ng/dh.h>
#include <libotr-ng/otrng.h>

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

/* begins */
// TODO: this whole section was copied and pasted from libotr-ng in order to
// have this project compiling this need to be changed. Prabably the API of
// libotr-ng needs to change.
#define MSG_PLAINTEXT 1
#define MSG_TAGGED_PLAINTEXT 2
#define MSG_QUERY_STRING 3
#define MSG_OTR_ENCODED 4
#define MSG_OTR_ERROR 5
static const char tag_base[] = {'\x20', '\x09', '\x20', '\x20', '\x09', '\x09',
                                '\x09', '\x09', '\x20', '\x09', '\x20', '\x09',
                                '\x20', '\x09', '\x20', '\x20', '\0'};
static const string_p query_header = "?OTRv";
static const string_p otr_error_header = "?OTR Error:";
static const string_p otr_header = "?OTR:";
int message_contains_tag(const string_p message) {
  return strstr(message, tag_base) != NULL;
}
int message_is_query(const string_p message) {
  if (strstr(message, query_header) != NULL) {
    return otrng_true;
  }
  return otrng_false;
}
tstatic otrng_bool message_is_otr_encoded(const string_p message) {
  if (strstr(message, otr_header) != NULL) {
    return otrng_true;
  }
  return otrng_false;
}

tstatic otrng_bool message_is_otr_error(const string_p message) {
  if (strncmp(message, otr_error_header, strlen(otr_error_header)) == 0) {
    return otrng_true;
  }
  return otrng_false;
}

int get_message_type(const string_p message) {
  if (message_contains_tag(message)) {
    return MSG_TAGGED_PLAINTEXT;
  }
  if (message_is_query(message)) {
    return MSG_QUERY_STRING;
  } else if (message_is_otr_error(message)) {
    return MSG_OTR_ERROR;
  } else if (message_is_otr_encoded(message)) {
    return MSG_OTR_ENCODED;
  }

  return MSG_PLAINTEXT;
}
int otrng_deserialize_uint16(uint16_t *n, const uint8_t *buffer, size_t buflen,
                             size_t *nread) {
  if (buflen < sizeof(uint16_t)) {
    return 1;
  }

  *n = buffer[1] | buffer[0] << 8;

  if (nread != NULL) {
    *nread = sizeof(uint16_t);
  }
  return 0;
}

int otrng_deserialize_uint8(uint8_t *n, const uint8_t *buffer, size_t buflen,
                            size_t *nread) {
  if (buflen < sizeof(uint8_t)) {
    return 1;
  }

  *n = buffer[0];

  if (nread != NULL) {
    *nread = sizeof(uint8_t);
  }
  return 0;
}
int extract_header(otrng_header_s *dst, const uint8_t *buffer,
                   const size_t bufflen) {
  if (bufflen == 0) {
    return 1;
  }

  size_t read = 0;
  uint16_t version = 0;
  uint8_t type = 0;
  if (!otrng_deserialize_uint16(&version, buffer, bufflen, &read)) {
    return 1;
  }

  buffer += read;

  if (!otrng_deserialize_uint8(&type, buffer, bufflen - read, &read)) {
    return 1;
  }

  dst->version = OTRNG_ALLOW_NONE;
  if (version == 0x04) {
    dst->version = OTRNG_ALLOW_V4;
  } else if (version == 0x03) {
    dst->version = OTRNG_ALLOW_V3;
  }
  dst->type = type;

  return 0;
}
/* ends */
int parse(encoded_msg_t *dst, const char *src, const int src_len) {
  if (NULL == src) {
    return 1;
  }

  if (src_len <= 0) {
    return 1;
  }

  int otr_type = get_message_type(src);
  if (otr_type != MSG_OTR_ENCODED) {
    return 1;
  }

  int err = otrl_base64_otr_decode(src, &dst->b64_msg, &dst->b64_msg_len);
  if (err) {
    return 1;
  }

  otrng_header_s header;
  if (extract_header(&header, dst->b64_msg, dst->b64_msg_len)) {
    return 1;
  }

  if (header.type != DATA_MSG_TYPE) {
    return 1;
  }

  dst->type = header.type;
  dst->version = header.version;

  data_message_s *data = malloc(sizeof(data_message_s));
  if (!data) {
    return 1;
  }

  size_t read = 0;
  if (otrng_data_message_deserialize(data, dst->b64_msg, dst->b64_msg_len,
                                     &read)) {
    otrng_data_message_free(data);
    return 1;
  }

  dst->sender_instance_tag = data->sender_instance_tag;
  dst->receiver_instance_tag = data->receiver_instance_tag;
  *dst->our_ecdh = *data->ecdh;
  otrng_dh_init();
  dst->our_dh = otrng_dh_mpi_copy(data->dh);
  memcpy(dst->nonce, data->nonce, DATA_MSG_NONCE_BYTES);

  dst->ciphertext = malloc(data->enc_msg_len);
  if (!dst->ciphertext) {
    free(data);
    return 1;
  }

  // XXX: check where old mackeys are deser
  memcpy(dst->ciphertext, data->enc_msg, data->enc_msg_len);
  dst->ciphertext_len = data->enc_msg_len;
  memcpy(dst->mac, data->mac, DATA_MSG_MAC_BYTES);

  otrng_data_message_free(data);

  return 0;
}
