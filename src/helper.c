
#include <stdio.h>

#include <goldilocks/point_448.h>

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

void print_ECDH(char *title, goldilocks_448_point_s *point) {
  uint8_t ecdh[ED448_POINT_BYTES] = {0};
  otrng_ec_point_encode(ecdh, point);
  printf("%s", title);
  print_hex(ecdh, ED448_POINT_BYTES);
}

void print_DH(char *title, dh_public_key_p dh) {
  size_t dh_size;
  unsigned char *dh_dump;
  gcry_mpi_aprint(GCRYMPI_FMT_USG, &dh_dump, &dh_size, dh);
  printf("%s", title);
  print_hex(dh_dump, dh_size);
  free(dh_dump);
}

void print_ring_signature(ring_sig_p sigma) {
  printf("\tRing Signature Authentication:\n");
  printf("\t\tc1:");
  uint8_t c1[ED448_SCALAR_BYTES];

  goldilocks_448_scalar_decode_long(sigma->c1, c1, ED448_SCALAR_BYTES);
  print_hex(c1, ED448_SCALAR_BYTES);
  printf("\t\tr1:");
  uint8_t r1[ED448_SCALAR_BYTES];
  goldilocks_448_scalar_decode_long(sigma->r1, r1, ED448_SCALAR_BYTES);
  print_hex(r1, ED448_SCALAR_BYTES);
  printf("\t\tc2:");
  uint8_t c2[ED448_SCALAR_BYTES];
  goldilocks_448_scalar_decode_long(sigma->c2, c2, ED448_SCALAR_BYTES);
  print_hex(c2, ED448_SCALAR_BYTES);
  printf("\t\tr2:");
  uint8_t r2[ED448_SCALAR_BYTES];
  goldilocks_448_scalar_decode_long(sigma->r2, r2, ED448_SCALAR_BYTES);
  print_hex(r2, ED448_SCALAR_BYTES);
  printf("\t\tc3:");
  uint8_t c3[ED448_SCALAR_BYTES];
  goldilocks_448_scalar_decode_long(sigma->c3, c3, ED448_SCALAR_BYTES);
  print_hex(c3, ED448_SCALAR_BYTES);
  printf("\t\tr3:");
  uint8_t r3[ED448_SCALAR_BYTES];
  goldilocks_448_scalar_decode_long(sigma->r3, r3, ED448_SCALAR_BYTES);
  print_hex(r3, ED448_SCALAR_BYTES);
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

  print_ECDH("\tECDH: ", data_msg->ecdh);

  print_DH("\tDH: ", data_msg->dh);

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
  if (!buff) {
    // TODO: maybe this function should return a int to check status
    return;
  }

  size_t bytes_before_tag = found_at - data;
  if (!bytes_before_tag) {
    memcpy(buff, data + tag_length, chars);
  } else {
    memcpy(buff, data, bytes_before_tag);
    memcpy(buff, data + bytes_before_tag, chars - bytes_before_tag);
  }

  print_string(buff, strlen(buff));
}

void print_identity_message(dake_identity_message_p identity_msg) {
  printf("\tSender instance tag: %u\n", identity_msg->sender_instance_tag);
  printf("\tReceiver instance tag: %u\n", identity_msg->receiver_instance_tag);

  printf("\tProfile:\n");
  printf("\t\tVersions: ");
  size_t n = strlen(identity_msg->profile->versions);
  print_string(identity_msg->profile->versions, n);

  printf("\t\tExpires: %lu\n", identity_msg->profile->expires);

  if (identity_msg->profile->dsa_key_len > 0) {
    printf("\t\tDSA Key: ");
    print_hex(identity_msg->profile->dsa_key,
              identity_msg->profile->dsa_key_len);
  }

  if (identity_msg->profile->transitional_signature) {
    printf("\t\tTransitional Signature: ");
    print_hex(identity_msg->profile->transitional_signature,
              sizeof(identity_msg->profile->transitional_signature));
  }

  printf("\t\tSignature: ");
  print_hex(identity_msg->profile->signature, ED448_SIGNATURE_BYTES);

  print_ECDH("\tY: ", identity_msg->Y);

  print_DH("\tB: ", identity_msg->B);
}

void print_auth_r(dake_auth_r_p auth_r_msg) {
  printf("\tSender instance tag: %u\n", auth_r_msg->sender_instance_tag);
  printf("\tReceiver instance tag: %u\n", auth_r_msg->receiver_instance_tag);

  printf("\tProfile:\n");
  printf("\t\tVersions: ");
  size_t n = strlen(auth_r_msg->profile->versions);
  print_string(auth_r_msg->profile->versions, n);

  printf("\t\tExpires: %lu\n", auth_r_msg->profile->expires);

  if (auth_r_msg->profile->dsa_key_len > 0) {
    printf("\t\tDSA Key: ");
    print_hex(auth_r_msg->profile->dsa_key, auth_r_msg->profile->dsa_key_len);
  }

  if (auth_r_msg->profile->transitional_signature) {
    printf("\t\tTransitional Signature: ");
    print_hex(auth_r_msg->profile->transitional_signature,
              sizeof(auth_r_msg->profile->transitional_signature));
  }

  print_ECDH("\tX: ", auth_r_msg->X);

  print_DH("\tA: ", auth_r_msg->A);

  print_ring_signature(auth_r_msg->sigma);

  otrng_dake_auth_r_destroy(auth_r_msg);
}

void print_auth_i(dake_auth_i_p auth_i_msg) {
  printf("\tSender instance tag: %u\n", auth_i_msg->sender_instance_tag);
  printf("\tReceiver instance tag: %u\n", auth_i_msg->receiver_instance_tag);

  print_ring_signature(auth_i_msg->sigma);

  otrng_dake_auth_i_destroy(auth_i_msg);
}
