#include <stdio.h>

#include <libotr-ng/constants.h>
#include <libotr-ng/otrng.h>

#include "helper.h"

void print_hex(uint8_t data[], int data_len) {
  for (int i = 0; i < data_len; i++) {
    printf("%02x", data[i]);
  }
  printf("\n");
}

void print_string(char *data, int data_len) {
  for (int i = 0; i < data_len; i++) {
    printf("%c", data[i]);
  }
  printf("\n");
}

void print_data_message(otrng_header_s *header_msg, data_message_s *data_msg) {
  printf("DATA MESSAGE:\n");
  printf("\tType: %02x\n", header_msg->type);
  printf("\tVersion: %04x\n", header_msg->version);
  printf("\tSender instance tag: %d\n", data_msg->sender_instance_tag);
  printf("\tReceiver instance tag: %d\n", data_msg->receiver_instance_tag);

  if (data_msg->flags == 1) {
    printf("\tFlags: IGNORE_UNREADABLE \n");
  } else {
    printf("\tFlags: \n");
  }

  printf("\tPrevious chain n#: %d\n", data_msg->previous_chain_n);
  printf("\tRatchet id: %d\n", data_msg->ratchet_id);
  printf("\tMessage_id: %d\n", data_msg->message_id);

  uint8_t ecdh[ED448_POINT_BYTES] = {0};
  otrng_ec_point_encode(ecdh, data_msg->ecdh);
  printf("\tECDH: ");
  print_hex(ecdh, ED448_POINT_BYTES);

  size_t dh_size;
  unsigned char *dh_dump;
  gcry_mpi_aprint(GCRYMPI_FMT_USG, &dh_dump, &dh_size, data_msg->dh);
  printf("\tDH: ");
  print_hex(dh_dump, dh_size);
  free(dh_dump);

  printf("\tNonce: ");
  print_hex(data_msg->nonce, DATA_MSG_NONCE_BYTES);

  printf("\tEncrypted message: ");
  print_hex(data_msg->enc_msg, data_msg->enc_msg_len);

  printf("\tMAC: ");
  print_hex(data_msg->mac, DATA_MSG_MAC_BYTES);

  free(header_msg);
  otrng_data_message_free(data_msg);
}

void print_error_msg(char *data) {
  printf("OTR ERROR: ");
  const char *unreadable_msg_error = "Unreadable message";
  const char *not_in_private_error = "Not in private state message";
  const char *encryption_error = "Encryption error";
  const char *malformed_error = "Malformed message";
  char *error_msg = data + strlen(ERROR_PREFIX);

  if (strncmp(error_msg, "ERROR_1:", 8) == 0) {
    printf("%s\n", unreadable_msg_error);
  } else if (strncmp(error_msg, "ERROR_2:", 8) == 0) {
    printf("%s\n", not_in_private_error);
  } else if (strncmp(error_msg, "ERROR_3:", 8) == 0) {
    printf("%s\n", encryption_error);
  } else if (strncmp(error_msg, "ERROR_4:", 8) == 0) {
    printf("%s\n", malformed_error);
  }
}

void print_plaintext_formated(char *data, int data_len) {
  static const char tag_base[] = {
      '\x20', '\x09', '\x20', '\x20', '\x09', '\x09', '\x09', '\x09', '\x20',
      '\x09', '\x20', '\x09', '\x20', '\x09', '\x20', '\x20', '\0'};

  size_t tag_length = WHITESPACE_TAG_BASE_BYTES + WHITESPACE_TAG_VERSION_BYTES;
  size_t chars = data_len - tag_length;
  char *found_at = strstr(data, tag_base);
  string_p buff = malloc(chars + 1);

  size_t bytes_before_tag = found_at - data;
  if (!bytes_before_tag) {
    memcpy(buff, data + tag_length, chars);
  } else {
    memcpy(buff, data, bytes_before_tag);
    memcpy(buff, data + bytes_before_tag, chars - bytes_before_tag);
  }

  print_string(buff, strlen(buff));
}
