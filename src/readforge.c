#include <string.h>

#include <libotr-ng/data_message.h>
#include <libotr-ng/key_management.h>
#include <libotr-ng/random.h>
#include <libotr-ng/shake.h>

#include "decode.h"
#include "helper.h"

int read(char **plain_text, msg_enc_key_p enc_key, char *raw_ratchet_key,
         char *raw_msg, data_message_s *data_msg) {
  size_t len_given_key;
  uint8_t *given_key;
  argv_to_buf(&given_key, &len_given_key, raw_ratchet_key);

  if (len_given_key == CHAIN_KEY_BYTES) {
    memset(enc_key, 0, sizeof(msg_enc_key_p));
    shake_256_kdf1(enc_key, sizeof(msg_enc_key_p), usage_message_key, given_key,
                   64);
  } else if (len_given_key == ENC_KEY_BYTES) {
    memcpy(enc_key, given_key, len_given_key);
  } else {
    free(given_key);
    fprintf(stderr, "Key with wrong size");
    return 1;
  }
  free(given_key);

  uint8_t *plain = malloc(data_msg->enc_msg_len);
  if (!plain) {
    fprintf(stderr, "Out of memory");
    return 1;
  }

  decrypt_data_message(plain, enc_key, data_msg);

  uint8_t *pos = memchr(plain, 0, data_msg->enc_msg_len);
  if (!pos) {
    return 1;
  }

  size_t l = pos - plain + 1;
  *plain_text = malloc(l);
  if (!*plain_text) {
    return 1;
  }

  memcpy(*plain_text, plain, l);
  free(plain);

  // size_t l = strnlen((char*) plain, data_msg->enc_msg_len);
  //*plain_text = otrng_strndup((const char*) plain, l);

  /*printf("strlen -> %zu\n", strlen((char*)plain));*/
  /*printf("1 - sizeof plain_text %zu\n", sizeof(plain_text));*/
  /**plain_text = otrng_memdup((uint8_t*)(char*)plain, strlen((char*)plain));*/
  /*printf("2 - sizeof plain_text %zu\n", sizeof(plain_text));*/
  return 0;
}

int forge(char **encoded_data_msg, char *new_txt_msg, data_message_s *data_msg,
          msg_enc_key_p enc_key) {

  if (new_txt_msg != NULL) {
    encrypt_data_message(data_msg, new_txt_msg, sizeof(new_txt_msg), enc_key);

    /*uint8_t *serialized_msg = NULL;*/
    /*size_t serialized_msg_len = 0;*/

    /*if (!otrng_data_message_body_asprintf(&serialized_msg,
     * &serialized_msg_len,*/
    /*data_msg)) {*/
    /*fprintf(stderr, "Error on serialization of new data message!");*/
    /*return 1;*/
    /*}*/

    serialize_and_remac(encoded_data_msg, data_msg, data_msg->mac);
  }
  return 0;
}

int readforge(char **plain_text, char **encoded_data_msg, char *raw_ratchet_key,
              char *raw_msg, char *new_txt_msg) {

  data_message_s *data_msg = otrng_data_message_new();
  if (decode_data_message(data_msg, raw_msg)) {
    otrng_data_message_free(data_msg);
    fprintf(stderr, "Error decoding message");
    return 1;
  }

  msg_enc_key_p enc_key;

  if (read(plain_text, enc_key, raw_ratchet_key, raw_msg, data_msg)) {
    otrng_data_message_free(data_msg);
    fprintf(stderr, "Error reading message");
    return 1;
  }

  // 1) Extract TLVs from plain_text to add them back into the new encrypted msg
  free(data_msg->enc_msg);
  data_msg->enc_msg = NULL;

  if (forge(encoded_data_msg, new_txt_msg, data_msg, enc_key)) {
    otrng_data_message_free(data_msg);
    fprintf(stderr, "Error forging message");
    return 1;
  }

  otrng_data_message_free(data_msg);
  return 0;
}
