/*It takes three inputs: the chain key,
  the OTRv4 message and a new plain text message (optional). If a new
  message is included, the original text is replaced with the new message and
  a new MAC tag is attached to the data message.

  To achieve this:
  - Decrypt the data message with the corresponding message key derived from
    the given chain key.
  - If a new message is given, replace the message with that one, encrypt it
    and create its mac accordingly. */
#include <stdio.h>
#include <string.h>

#include <libotr-ng/data_message.h>
#include <libotr-ng/key_management.h>
#include <libotr-ng/random.h>
#include <libotr-ng/shake.h>

#include "decode.h"
#include "helper.h"

// static uint8_t usage_message_key = 0x16;

int decrypt_data_message(uint8_t *plain, const msg_enc_key_p enc_key,
                         const data_message_s *msg) {

  int err = crypto_stream_xor(plain, msg->enc_msg, msg->enc_msg_len, msg->nonce,
                              enc_key);

  if (err) {
    return 1;
  }
  return 0;
}

int encrypt_data_message(data_message_s *data_msg, const uint8_t *message,
                         const msg_enc_key_p enc_key) {

  random_bytes(data_msg->nonce, sizeof(data_msg->nonce));

  size_t msg_len = sizeof(message);
  uint8_t *enc_msg = malloc(msg_len);

  int err =
      crypto_stream_xor(enc_msg, message, msg_len, data_msg->nonce, enc_key);

  if (err) {
    free(enc_msg);
    return 1;
  }

  data_msg->enc_msg_len = msg_len;
  data_msg->enc_msg = enc_msg;

  msg_mac_key_p mac_key = {0};
  otrng_data_message_authenticator(data_msg->mac, sizeof(msg_mac_key_p),
                                   mac_key, data_msg->enc_msg,
                                   data_msg->enc_msg_len);

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

  printf("Argc size: %d\n", argc);
  if (argc == 4) {
    new_txt_msg = (uint8_t *)argv[3];
  }

  size_t len_chain_key;
  uint8_t *chain_key;
  char *original_msg = argv[2];

  arg_to_buf(&chain_key, &len_chain_key, argv[1]);

  if (len_chain_key != CHAIN_KEY_BYTES) {
    puts("Chain key with the wrong size");
    return 1;
  }

  //  printf("ratchet: %s\n", argv[1]);

  msg_enc_key_p enc_key;
  memset(enc_key, 0, sizeof(enc_key));

  shake_256_kdf1(enc_key, sizeof(msg_enc_key_p), 0x16, chain_key, 64);

  /*printf("\n");
  printf("encryption: ");
  for (int i = 0; i < sizeof(enc_key); i++) {
    printf("%02x", enc_key[i]);
  }
  printf("\n");*/

  data_message_s *data_msg = otrng_data_message_new();
  if (decode_data_message(data_msg, original_msg)) {
    puts("Error decoding message");
    return 1;
  }

  uint8_t *plain = malloc(data_msg->enc_msg_len);
  if (!plain) {
    return 1;
  }

  decrypt_data_message(plain, enc_key, data_msg);

  printf("Decrypted message: %s\n", plain);

  data_message_s *enc_data_msg = otrng_data_message_new();
  if (new_txt_msg != NULL) {
    printf("The text: %s\n", new_txt_msg);
    encrypt_data_message(enc_data_msg, new_txt_msg, enc_key);
  }

  free(plain);
  return 0;
}
