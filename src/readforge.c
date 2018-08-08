#include <string.h>

#include <libotr-ng/data_message.h>
#include <libotr-ng/key_management.h>
#include <libotr-ng/random.h>
#include <libotr-ng/shake.h>

#include "decode.h"
#include "helper.h"

int readforge(uint8_t **plain_text, char **encoded_data_msg,
              char *raw_ratchet_key, char *raw_msg, uint8_t *new_txt_msg) {
  size_t len_given_key;
  uint8_t *given_key;
  argv_to_buf(&given_key, &len_given_key, raw_ratchet_key);

  msg_enc_key_p enc_key;
  if (len_given_key == CHAIN_KEY_BYTES) {
    memset(enc_key, 0, sizeof(enc_key));
    shake_256_kdf1(enc_key, sizeof(msg_enc_key_p), usage_message_key, given_key,
                   64);
  } else if (len_given_key == ENC_KEY_BYTES) {
    memcpy(enc_key, given_key, len_given_key);
  } else {
    fprintf(stderr, "Key with wrong size");
    return 1;
  }

  data_message_s *data_msg = otrng_data_message_new();
  if (decode_data_message(data_msg, raw_msg)) {
    fprintf(stderr, "Error decoding message");
    return 1;
  }

  *plain_text = malloc(data_msg->enc_msg_len);
  if (!plain_text) {
    return 1;
  }

  decrypt_data_message(*plain_text, enc_key, data_msg);

  if (new_txt_msg != NULL) {
    encrypt_data_message(data_msg, new_txt_msg, sizeof(new_txt_msg), enc_key);

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
      fprintf(stderr, "Memory error");
      return 1;
    }

    memcpy(serialialized_msg_with_mac, serialized_msg, serialized_msg_len);
    free(serialized_msg);

    serialize_and_remac(encoded_data_msg, serialialized_msg_with_mac,
                        serialized_msg_len, data_msg->mac);

    free(serialialized_msg_with_mac);
  }
  otrng_data_message_free(data_msg);

  return 0;
}
