#include <stdio.h>
#include <string.h>

#include <libotr-ng/data_message.h>
#include <libotr-ng/key_management.h>
#include <libotr-ng/random.h>
#include <libotr-ng/shake.h>

#include "decode.h"
#include "helper.h"

static uint8_t usage_message_key = 0x16;

int main(int argc, char **argv) {
  uint8_t *new_txt_msg = NULL;
  size_t new_txt_msg_len = 0;

  if (argc == 4) {
    new_txt_msg = (uint8_t *)argv[3];
    new_txt_msg_len = strlen(argv[3]);
  }

  msg_enc_key_p enc_key;
  size_t len_given_key;
  uint8_t *given_key;
  char *original_msg = argv[2];

  argv_to_buf(&given_key, &len_given_key, argv[1]);

  if (len_given_key == CHAIN_KEY_BYTES) {

    memset(enc_key, 0, sizeof(enc_key));
    shake_256_kdf1(enc_key, sizeof(msg_enc_key_p), usage_message_key, given_key,
                   64);
  } else if (len_given_key == ENC_KEY_BYTES) {
    memcpy(enc_key, given_key, len_given_key);
  } else {
    fprintf(stderr, "Key with wrong size");
  }

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
    if (!serialialized_msg_with_mac) {
      return 1;
    }

    memcpy(serialialized_msg_with_mac, serialized_msg, serialized_msg_len);
    free(serialized_msg);

    char *encoded_data_msg = NULL;
    serialize_and_remac(&encoded_data_msg, serialialized_msg_with_mac,
                        serialized_msg_len, data_msg->mac);

    printf("New data message: %s\n", encoded_data_msg);
    free(serialialized_msg_with_mac);
  }
  otrng_data_message_free(data_msg);
  return 0;
}
