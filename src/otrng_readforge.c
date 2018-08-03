#include <stdio.h>
#include <string.h>

#include <libotr-ng/data_message.h>
#include <libotr-ng/key_management.h>
#include <libotr-ng/random.h>
#include <libotr-ng/shake.h>

#include "decode.h"
#include "helper.h"

static uint8_t usage_message_key = 0x16;

int decrypt_data_message(uint8_t *plain, const msg_enc_key_p enc_key,
                         const data_message_s *msg) {

  int err = crypto_stream_xor(plain, msg->enc_msg, msg->enc_msg_len, msg->nonce,
                              enc_key);

  if (err) {
    fprintf(stderr, "Error on decrypt!\n");
    return 1;
  }
  return 0;
}

int encrypt_data_message(data_message_s *data_msg, const uint8_t *msg,
                         size_t msg_len, const msg_enc_key_p enc_key) {

  uint8_t *enc_msg = malloc(msg_len);

  int err = crypto_stream_xor(enc_msg, msg, msg_len, data_msg->nonce, enc_key);

  if (err) {
    fprintf(stderr, "Error on encrypt!\n");
    free(enc_msg);
    return 1;
  }

  data_msg->enc_msg_len = msg_len;
  data_msg->enc_msg = enc_msg;

  return 0;
}

void arg_to_buf(uint8_t **dst, size_t *written, char *arg) {
  uint8_t *buf;
  *dst = 0;
  *written = 0;
  size_t size = strlen(arg);

  if (size % 2) {
    fprintf(stderr, "Argument ``%s'' must have even length.\n", arg);
    return;
  }

  buf = malloc(size / 2);
  if (buf == NULL) {
    fprintf(stderr, "Out of memory!\n");
    return;
  }

  char *b = malloc(2);
  char *end;
  for (int i = 0; i < size / 2; i++) {
    strncpy(b, arg, 2);
    arg += 2;
    buf[i] = (int)strtol(b, &end, 16);
    if (*end) {
      fprintf(stderr, "Error when trying to convert key!\n");
      return;
    }
  }
  free(b);

  *dst = buf;
  *written = size / 2;
}

int main(int argc, char **argv) {
  uint8_t *new_txt_msg = NULL;
  size_t new_txt_msg_len = 0;

  if (argc == 4) {
    new_txt_msg = (uint8_t *)argv[3];
    new_txt_msg_len = strlen(argv[3]);
  }

  size_t len_chain_key;
  uint8_t *chain_key;
  char *original_msg = argv[2];

  argv_to_buf(&chain_key, &len_chain_key, argv[1]);

  if (len_chain_key != CHAIN_KEY_BYTES) {
    fprintf(stderr, "Chain key with the wrong size");
    return 1;
  }

  msg_enc_key_p enc_key;
  memset(enc_key, 0, sizeof(enc_key));

  shake_256_kdf1(enc_key, sizeof(msg_enc_key_p), usage_message_key, chain_key,
                 64);

  data_message_s *data_msg = otrng_data_message_new();
  if (decode_data_message(data_msg, original_msg)) {
    fprintf(stderr, "Error decoding message");
    return 1;
  }

  uint8_t *plain = malloc(data_msg->enc_msg_len);
  if (!plain) {
    return 1;
  }

  decrypt_data_message(plain, enc_key, data_msg);
  printf("Decrypted message: %s\n", plain);

  free(plain);

  if (new_txt_msg != NULL) {
    encrypt_data_message(data_msg, new_txt_msg, new_txt_msg_len, enc_key);

    uint8_t *serialized_msg = NULL;
    size_t serialized_msg_len = 0;

    if (!otrng_data_message_body_asprintf(&serialized_msg, &serialized_msg_len,
                                          data_msg)) {
      fprintf(stderr, "Error on serialization of new data message!");
      return 1;
    }
    uint8_t *serialialized_msg_with_mac =
        malloc(serialized_msg_len + DATA_MSG_MAC_BYTES);

    memcpy(serialialized_msg_with_mac, serialized_msg, serialized_msg_len);
    free(serialized_msg);

    otrng_data_message_authenticator(
        serialialized_msg_with_mac + serialized_msg_len, DATA_MSG_MAC_BYTES,
        data_msg->mac, serialialized_msg_with_mac, serialized_msg_len);

    char *encoded_data_msg = otrl_base64_otr_encode(
        serialialized_msg_with_mac, serialized_msg_len + DATA_MSG_MAC_BYTES);

    printf("New data message: %s\n", encoded_data_msg);
    free(serialialized_msg_with_mac);
  }
  otrng_data_message_free(data_msg);
  return 0;
}
