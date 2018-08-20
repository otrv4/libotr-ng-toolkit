#include "decode.h"

/* Dump an unsigned int to a FILE */
void dump_int(FILE *stream, const char *title, unsigned int val) {
  fprintf(stream, "%s: %u\n", title, val);
}

/* Dump a short int to a FILE */
void dump_short(FILE *stream, const char *title, unsigned short val) {
  fprintf(stream, "%s: %u\n", title, val);
}

/* Dump data to a FILE */
void dump_data(FILE *stream, const char *title, const unsigned char *data,
               size_t datalen) {
  size_t i;
  fprintf(stream, "%s: ", title);
  for (i = 0; i < datalen; ++i) {
    fprintf(stream, "%02x", data[i]);
  }
  fprintf(stream, "\n");
}

/* Dump an mpi to a FILE */
void dump_mpi(FILE *stream, const char *title, gcry_mpi_t val) {
  size_t plen;
  unsigned char *d;

  gcry_mpi_print(GCRYMPI_FMT_USG, NULL, 0, &plen, val);
  d = malloc(plen);
  gcry_mpi_print(GCRYMPI_FMT_USG, d, plen, NULL, val);
  dump_data(stream, title, d, plen);
  free(d);
}

/* Dump an scalar to a FILE */
void dump_scalar(FILE *stream, const char *title,
                 goldilocks_448_scalar_p scalar) {
  uint8_t ser_scalar[ED448_SCALAR_BYTES] = {0};
  otrng_ec_scalar_encode(ser_scalar, scalar);
  dump_data(stream, title, ser_scalar, ED448_SCALAR_BYTES);
}

/* Dump an point to a FILE */
void dump_point(FILE *stream, const char *title, goldilocks_448_point_p point) {
  uint8_t ser_point[ED448_POINT_BYTES] = {0};
  otrng_ec_point_encode(ser_point, ED448_POINT_BYTES, point);
  dump_data(stream, title, ser_point, ED448_POINT_BYTES);
}

/* Dump a client profile to a FILE * */
void dump_client_profile(FILE *stream, const char *title,
                         client_profile_p profile) {
  fprintf(stream, "%s: ", title);
  fprintf(stream, "\n");
  dump_int(stdout, "\t\tOwner instance", profile->sender_instance_tag);
  dump_point(stream, "\t\tPublic longterm key", profile->long_term_pub_key);
  dump_data(stream, "\t\tVersions", (unsigned char *)profile->versions,
            strlen(profile->versions));
  dump_int(stream, "\t\tExpiration", profile->expires);
  if (profile->dsa_key_len > 0) {
    dump_data(stream, "\t\tDSA key", profile->dsa_key, profile->dsa_key_len);
  }
  if (profile->transitional_signature) {
    dump_data(stream, "\t\tTransitional Signature",
              profile->transitional_signature, OTRv3_DSA_SIG_BYTES);
  }
  dump_data(stream, "\t\tEdDSA Signature", profile->signature,
            ED448_SIGNATURE_BYTES);
}

/* Dump a ring signature to a FILE */
void dump_ring_signature(FILE *stream, const char *title, ring_sig_p ring_sig) {
  fprintf(stream, "%s: ", title);
  fprintf(stream, "\n");
  dump_scalar(stream, "\t\tRSig C1", ring_sig->c1);
  dump_scalar(stream, "\t\tRSig R1", ring_sig->r1);
  dump_scalar(stream, "\t\tRSig C2", ring_sig->c2);
  dump_scalar(stream, "\t\tRSig R2", ring_sig->r2);
  dump_scalar(stream, "\t\tRSig C3", ring_sig->c3);
  dump_scalar(stream, "\t\tRSig R3", ring_sig->r3);
}

void dump_identity_message(dake_identity_message_p identity_msg) {
  dump_int(stdout, "\tSender instance", identity_msg->sender_instance_tag);
  dump_int(stdout, "\tReceiver instance", identity_msg->receiver_instance_tag);
  dump_client_profile(stdout, "\tClient Profile", identity_msg->profile);
  dump_point(stdout, "\tPublic ECDH Y key", identity_msg->Y);
  dump_mpi(stdout, "\tPublic DH B Key", identity_msg->B);
  otrng_dake_identity_message_destroy(identity_msg);
}

void dump_auth_r_message(dake_auth_r_p auth_r_msg) {
  dump_int(stdout, "\tSender instance", auth_r_msg->sender_instance_tag);
  dump_int(stdout, "\tReceiver instance", auth_r_msg->receiver_instance_tag);
  dump_client_profile(stdout, "\tClient Profile", auth_r_msg->profile);
  dump_point(stdout, "\tPublic ECDH X key", auth_r_msg->X);
  dump_mpi(stdout, "\tPublic DH A Key", auth_r_msg->A);
  dump_ring_signature(stdout, "\tRing Sig", auth_r_msg->sigma);
  otrng_dake_auth_r_destroy(auth_r_msg);
}

void dump_auth_i_message(dake_auth_i_p auth_i_msg) {
  dump_int(stdout, "\tSender instance", auth_i_msg->sender_instance_tag);
  dump_int(stdout, "\tReceiver instance", auth_i_msg->receiver_instance_tag);
  dump_ring_signature(stdout, "\tRing Sig", auth_i_msg->sigma);
  otrng_dake_auth_i_destroy(auth_i_msg);
}

void dump_non_interactive_auth_message(
    dake_non_interactive_auth_message_p non_int_auth_msg) {
  dump_int(stdout, "\tSender instance", non_int_auth_msg->sender_instance_tag);
  dump_int(stdout, "\tReceiver instance",
           non_int_auth_msg->receiver_instance_tag);
  dump_client_profile(stdout, "\tClient Profile", non_int_auth_msg->profile);
  dump_point(stdout, "\tPublic ECDH X key", non_int_auth_msg->X);
  dump_mpi(stdout, "\tPublic DH A Key", non_int_auth_msg->A);
  dump_ring_signature(stdout, "\tRing Sig", non_int_auth_msg->sigma);
  dump_int(stdout, "\tPrekey message ID", non_int_auth_msg->prekey_message_id);
  dump_data(stdout, "\t\tAuth MAC", non_int_auth_msg->auth_mac,
            DATA_MSG_MAC_BYTES);
  otrng_dake_non_interactive_auth_message_destroy(non_int_auth_msg);
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
  dump_point(stdout, "\tPublic ECDH Key", data_msg->ecdh);
  dump_mpi(stdout, "\tPublic DH Key", data_msg->dh);
  dump_data(stdout, "\tNonce", data_msg->nonce, DATA_MSG_NONCE_BYTES);
  dump_data(stdout, "\tEncrypted message", data_msg->enc_msg,
            data_msg->enc_msg_len);
  dump_data(stdout, "\tMAC", data_msg->mac, DATA_MSG_MAC_BYTES);

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

  printf("\nHeader: %d \n", header.type);
  switch (header.type) {
  case IDENTITY_MSG_TYPE:
    printf("Identity Message:\n");
    dake_identity_message_p identity_msg;
    if (!otrng_dake_identity_message_deserialize(identity_msg, decoded,
                                                 dec_len)) {
      printf("Invalid Identity Message\n\n");
      return 1;
    }
    dump_short(stdout, "\tVersion", header.version);
    dump_identity_message(identity_msg);
    printf("\n");

  case AUTH_R_MSG_TYPE:
    printf("Auth R Message:\n");
    dake_auth_r_p auth_r_msg;
    if (!otrng_dake_auth_r_deserialize(auth_r_msg, decoded, dec_len)) {
      printf("Invalid Auth R Message\n\n");
      return 1;
    }
    dump_short(stdout, "\tVersion", header.version);
    dump_auth_r_message(auth_r_msg);
    printf("\n");

  case AUTH_I_MSG_TYPE:
    printf("Auth I Message:\n");
    dake_auth_i_p auth_i_msg;
    if (!otrng_dake_auth_i_deserialize(auth_i_msg, decoded, dec_len)) {
      printf("Invalid Auth I Message\n\n");
      return 1;
    }
    dump_short(stdout, "\tVersion", header.version);
    dump_auth_i_message(auth_i_msg);
    printf("\n");

  case NON_INT_AUTH_MSG_TYPE:
    printf("Non-Interactive Auth Message:\n");
    dake_non_interactive_auth_message_p non_int_auth_msg;
    if (!otrng_dake_non_interactive_auth_message_deserialize(
            non_int_auth_msg, decoded, dec_len)) {
      printf("Invalid Auth I Message\n\n");
      return 1;
    }
    dump_short(stdout, "\tVersion", header.version);
    dump_non_interactive_auth_message(non_int_auth_msg);
    printf("\n");

  case DATA_MSG_TYPE:
    printf("Data Message:\n");
    data_message_s *data_msg = otrng_data_message_new();
    size_t read = 0;
    if (!otrng_data_message_deserialize(data_msg, decoded, dec_len, &read)) {
      otrng_data_message_free(data_msg);
      printf("Invalid Data Message\n\n");
      return 1;
    }
    dump_short(stdout, "\tVersion", header.version);
    dump_data_message(data_msg);
    printf("\n");

  default:
    return 1;
  }

  free(decoded);
  return 0;
}
