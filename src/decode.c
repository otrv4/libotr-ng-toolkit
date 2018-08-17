#include "decode.h"

/* Dump an unsigned int to a FILE * */
void dump_int(FILE *stream, const char *title, unsigned int val) {
  fprintf(stream, "%s: %u\n", title, val);
}

/* Dump data to a FILE * */
void dump_data(FILE *stream, const char *title, const unsigned char *data,
               size_t datalen) {
  size_t i;
  fprintf(stream, "%s: ", title);
  for (i = 0; i < datalen; ++i) {
    fprintf(stream, "%02x", data[i]);
  }
  fprintf(stream, "\n");
}

/* Dump an mpi to a FILE * */
void dump_mpi(FILE *stream, const char *title, gcry_mpi_t val)
{
    size_t plen;
    unsigned char *d;

    gcry_mpi_print(GCRYMPI_FMT_USG, NULL, 0, &plen, val);
    d = malloc(plen);
    gcry_mpi_print(GCRYMPI_FMT_USG, d, plen, NULL, val);
    dump_data(stream, title, d, plen);
    free(d);
}

void dump_data_message(data_message_s *data_msg) {
  if (data_msg->flags >= 0) {
    dump_int(stdout, "\tFlags", data_msg->flags);
  }

  dump_int(stdout, "\tSender instance", data_msg->sender_instance_tag);
  dump_int(stdout, "\tReceiver instance", data_msg->receiver_instance_tag);

  dump_int(stdout, "\tPrevious chain key number", data_msg->previous_chain_n);
  dump_int(stdout, "\tRatchet id", data_msg->ratchet_id);
  dump_int(stdout, "\tMessage id", data_msg->message_id);
  // TODO: add the ecdh
  //dump_mpi(stdout, "\tPublic DH Key", data_msg->dh);
  // TODO: check all of this
  dump_data(stdout, "\tNonce", data_msg->nonce, 64);
  dump_data(stdout, "\tEncrypted message", data_msg->enc_msg, data_msg->enc_msg_len);
  dump_data(stdout, "\tMAC", data_msg->mac, 64);

  // TODO: is missing to deserialize the old mac keys
  otrng_data_message_free(data_msg);
}

int decode_encoded_message(const char *message) {
  size_t dec_len = 0;
  uint8_t *decoded = NULL;
  if (otrl_base64_otr_decode(message, &decoded, &dec_len)) {
    return 1;
  }

  otrng_header_s header;
  if (!otrng_extract_header(&header, decoded, dec_len)) {
    free(decoded);
    return 1;
  }

  free(decoded);

  switch (header.type) {
    //dump_int(stdout, "\tVersion", &(header.version));
  case IDENTITY_MSG_TYPE:
  case AUTH_R_MSG_TYPE:
  case AUTH_I_MSG_TYPE:
  case NON_INT_AUTH_MSG_TYPE:
  case DATA_MSG_TYPE:
    printf("\n");
    data_message_s *data_msg = otrng_data_message_new();
    size_t read = 0;
    if (!otrng_data_message_deserialize(data_msg, decoded, dec_len,
                                        &read)) {
      printf("Invalid Data Message\n\n");
      return 1;
    }
    printf("Data Message:\n");
    dump_data_message(data_msg);
    printf("\n");
  default:
    return 1;
  }
  return 0;
}

int decode_identity_message(dake_identity_message_p identity_msg,
                            const char *original_msg) {

  size_t decoded_msg_len = 0;
  uint8_t *decoded_msg = NULL;
  if (otrl_base64_otr_decode(original_msg, &decoded_msg, &decoded_msg_len)) {
    return 1;
  }

  if (!otrng_dake_identity_message_deserialize(identity_msg, decoded_msg,
                                               decoded_msg_len)) {
    return 1;
  }
  free(decoded_msg);
  return 0;
}

int decode_auth_r_message(dake_auth_r_p auth_r_msg, const char *original_msg) {
  size_t decoded_msg_len = 0;
  uint8_t *decoded_msg = NULL;
  if (otrl_base64_otr_decode(original_msg, &decoded_msg, &decoded_msg_len)) {
    free(decoded_msg);
    return 1;
  }
  if (!otrng_dake_auth_r_deserialize(auth_r_msg, decoded_msg,
                                     decoded_msg_len)) {
    return 1;
  }
  free(decoded_msg);
  return 0;
}

int decode_auth_i_message(dake_auth_i_p auth_i_msg, const char *original_msg) {
  size_t decoded_msg_len = 0;
  uint8_t *decoded_msg = NULL;
  if (otrl_base64_otr_decode(original_msg, &decoded_msg, &decoded_msg_len)) {
    return 1;
  }
  if (!otrng_dake_auth_i_deserialize(auth_i_msg, decoded_msg,
                                     decoded_msg_len)) {
    return 1;
  }
  free(decoded_msg);
  return 0;
}
