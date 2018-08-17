
#include <stdio.h>

#include <goldilocks/point_448.h>

#include <libotr-ng/constants.h>
#include <libotr-ng/otrng.h>
#include <libotr-ng/shake.h>
#include <libotr/b64.h>

#include "decode.h"
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
  otrng_ec_point_encode(ecdh, ED448_POINT_BYTES, point);
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

void print_identity_message(otrng_header_s *header_msg,
                            dake_identity_message_p identity_msg) {
  printf("IDENTITY MESSAGE:\n");
  printf("\tType: %x\n", header_msg->type);
  printf("\tVersion: %x\n", header_msg->version);
  printf("\tSender instance tag: %u\n", identity_msg->sender_instance_tag);
  printf("\tReceiver instance tag: %u\n", identity_msg->receiver_instance_tag);
  printf("\tProfile:\n");
  printf("\t\tVersions: ");
  size_t n = strlen(identity_msg->profile->versions);
  print_string(identity_msg->profile->versions, n);

  printf("\t\tExpires: %llu\n", identity_msg->profile->expires);

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

void print_auth_r(otrng_header_s *header_msg, dake_auth_r_p auth_r_msg) {
  printf("AUTH-R MESSAGE:\n");
  printf("\tType: %x\n", header_msg->type);
  printf("\tVersion: %x\n", header_msg->version);
  printf("\tSender instance tag: %u\n", auth_r_msg->sender_instance_tag);
  printf("\tReceiver instance tag: %u\n", auth_r_msg->receiver_instance_tag);

  printf("\tProfile:\n");
  printf("\t\tVersions: ");
  size_t n = strlen(auth_r_msg->profile->versions);
  print_string(auth_r_msg->profile->versions, n);

  printf("\t\tExpires: %llu\n", auth_r_msg->profile->expires);

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

void print_auth_i(otrng_header_s *header_msg, dake_auth_i_p auth_i_msg) {
  printf("AUTH-I MESSAGE:\n");
  printf("\tType: %x\n", header_msg->type);
  printf("\tVersion: %x\n", header_msg->version);
  printf("\tSender instance tag: %u\n", auth_i_msg->sender_instance_tag);
  printf("\tReceiver instance tag: %u\n", auth_i_msg->receiver_instance_tag);
  print_ring_signature(auth_i_msg->sigma);
  otrng_dake_auth_i_destroy(auth_i_msg);
}

void argv_to_buf(unsigned char **dst, size_t *written, char *arg) {
  unsigned char *buf;
  *dst = NULL;
  *written = 0;
  size_t size = strlen(arg);

  if (size % 2) {
    fprintf(stderr, "Argument ``%s'' must have even length.\n", arg);
    exit(1);
  }

  buf = malloc(size / 2);
  if (buf == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(1);
  }

  char *b = malloc(3);
  if (b == NULL) {
    fprintf(stderr, "Out of memory!\n");
    free(buf);
    exit(1);
  }

  char *end;
  for (int i = 0; i < size / 2; i++) {
    strncpy(b, arg, 2);
    b[2] = 0;
    arg += 2;
    buf[i] = (int)strtol(b, &end, 16);
    if (*end) {
      free(b);
      free(buf);
      fprintf(stderr, "Error when trying to convert key!\n");
      exit(1);
    }
  }

  *dst = buf;
  *written = size / 2;

  free(b);
}

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

int encrypt_data_message(data_message_s *data_msg, const char *msg,
                         size_t msg_len, const msg_enc_key_p enc_key) {

  uint8_t *enc_msg = malloc(msg_len);

  int err = crypto_stream_xor(enc_msg, (uint8_t *)msg, msg_len, data_msg->nonce,
                              enc_key);

  if (err) {
    fprintf(stderr, "Error on encrypt!\n");
    free(enc_msg);
    return 1;
  }

  data_msg->enc_msg_len = msg_len;
  data_msg->enc_msg = enc_msg;

  return 0;
}

void serialize_and_remac(char **encoded_data_msg, data_message_s *data_msg,
                         uint8_t *new_mac) {

  uint8_t *msg = NULL;
  size_t msg_len = 0;

  otrng_data_message_body_asprintf(&msg, &msg_len, data_msg);

  size_t encoded_data_msg_len = msg_len + DATA_MSG_MAC_BYTES;

  uint8_t *enc_msg = malloc(encoded_data_msg_len);
  if (!enc_msg) {
    fprintf(stderr, "Out of memory!\n");
    exit(1);
  }

  memcpy(enc_msg, msg, msg_len);
  free(msg);

  otrng_data_message_authenticator(enc_msg + msg_len, DATA_MSG_MAC_BYTES,
                                   new_mac, enc_msg, msg_len);

  *encoded_data_msg =
      otrl_base64_otr_encode(enc_msg, msg_len + DATA_MSG_MAC_BYTES);

  free(enc_msg);
}

void calculate_mac(msg_mac_key_p mac_key, unsigned char *buff) {

  memset(mac_key, 0, sizeof(msg_mac_key_p));

  shake_256_kdf1(mac_key, sizeof(msg_mac_key_p), usage_mac_key, buff,
                 sizeof(msg_enc_key_p));
}

// int modify_message(data_message_s *data_msg, char *original_msg,
//                   char *old_msg_txt, char *new_msg_txt, int offset) {
//
//  int result = decode_data_message(data_msg, original_msg);
//
//  if (result != 0) {
//    fprintf(stderr, "Error decoding data message");
//    otrng_data_message_free(data_msg);
//    return result;
//  }
//
//  for (int i = 0; i < strlen(old_msg_txt) && offset + i <
//  data_msg->enc_msg_len;
//       ++i) {
//    data_msg->enc_msg[offset + i] ^= (old_msg_txt[i] ^ new_msg_txt[i]);
//  }
//
//  return result;
//}
