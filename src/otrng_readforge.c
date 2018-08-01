/*It takes three inputs: the chain key,
  the OTRv4 message and a new plain text message (optional). If a new
  message is included, the original text is replaced with the new message and
  a new MAC tag is attached to the data message.

  To achieve this:
  - Decrypt the data message with the corresponding message key derived from
    the given chain key.
  - If a new message is given, replace the message with that one, encrypt it
    and create its mac accordingly. */
#include <libotr-ng/data_message.h>
#include <libotr-ng/key_management.h>
#include <libotr-ng/shake.h>
#include <stdio.h>
#include <string.h>

static uint8_t usage_message_key = 0x16;

int decrypt_data_msg(const msg_enc_key_p enc_key, const data_message_s *msg) {
  uint8_t *plain = malloc(msg->enc_msg_len);
  if (!plain) {
    return 1;
  }

  int err = crypto_stream_xor(plain, msg->enc_msg, msg->enc_msg_len, msg->nonce,
                              enc_key);

  if (err) {
    free(plain);
    return 1;
  }
  return 0;
}

void argv_to_buf(uint8_t **dst, size_t *written, char *arg) {
  uint8_t *buf;
  *dst = NULL;
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
  if (argc < 3) {
    puts("Wrong number of arguments");
    return 1;
  }

  char *chain_key = argv[2];
  char *original_msg = argv[3];
  // char *new_txt_msg = argv[4];
  size_t len;
  uint8_t *new_chain_key;
  argv_to_buf(&new_chain_key, &len, argv[2]);

  if (len != CHAIN_KEY_BYTES) {
    puts("Chain key with the wrong size");
    return 1;
  }

  msg_enc_key_p enc_key;
  memset(enc_key, 0, sizeof(enc_key));
  shake_256_kdf1(enc_key, sizeof(msg_enc_key_p), usage_message_key,
                 new_chain_key, CHAIN_KEY_BYTES);

  return 0;
}
