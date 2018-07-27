#include <stdio.h>

/*#include <goldilocks/common.h>*/
/*#include <goldilocks/point_448.h>*/

#include <libotr-ng/dake.h>

#include "helper.h"
#include "parse.h"
#include "readotr.h"

int main(int argc, char **argv) {
  char *original_msg = NULL;
  original_msg = readotr(stdin);

  int message_type = otrng_get_message_type(original_msg);
  int result = 1;

  if (message_type == MSG_PLAINTEXT) {
    printf("PLAIN TEXT: ");
    print_string(original_msg, strlen(original_msg));
  } else if (message_type == MSG_TAGGED_PLAINTEXT) {
    printf("PLAIN TEXT WITH WHITESPACE TAGS: ");
    print_plaintext_formated(original_msg, strlen(original_msg));
  } else if (message_type == MSG_QUERY_STRING) {
    printf("QUERY STRING: ");
    print_string(original_msg, strlen(original_msg));
  } else if (message_type == MSG_OTR_ENCODED) {
    otrng_header_s *header_msg = malloc(sizeof(otrng_header_s));
    result = parse_header(header_msg, original_msg);

    if (header_msg->type == IDENTITY_MSG_TYPE) {
      printf("IDENTITY MESSAGE:\n");
      printf("\tType: %x\n", header_msg->type);
      printf("\tVersion: %x\n", header_msg->version);

      dake_identity_message_p identity_msg;
      size_t decoded_msg_len = 0;
      uint8_t *decoded_msg = NULL;
      if (otrl_base64_otr_decode(original_msg, &decoded_msg,
                                 &decoded_msg_len)) {
        return 1;
      }

      if (!otrng_dake_identity_message_deserialize(identity_msg, decoded_msg,
                                                   decoded_msg_len)) {
        return 1;
      }

      printf("\tSender instance tag: %u\n", identity_msg->sender_instance_tag);
      printf("\tReceiver instance tag: %u\n",
             identity_msg->receiver_instance_tag);

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

      uint8_t ecdh[ED448_POINT_BYTES] = {0};
      otrng_ec_point_encode(ecdh, identity_msg->Y);
      printf("\tY: ");
      print_hex(ecdh, ED448_POINT_BYTES);

      size_t dh_size;
      unsigned char *dh_dump;

      if (gcry_mpi_aprint(GCRYMPI_FMT_USG, &dh_dump, &dh_size,
                          identity_msg->B)) {
        return 1;
      }

      printf("\tB: ");
      print_hex(dh_dump, dh_size);
      free(dh_dump);
      otrng_dake_identity_message_free(identity_msg);
    } else if (header_msg->type == AUTH_R_MSG_TYPE) {
      printf("AUTH-R MESSAGE:\n");
      printf("\tType: %x\n", header_msg->type);
      printf("\tVersion: %x\n", header_msg->version);

      dake_auth_r_p auth_r_msg;
      size_t decoded_msg_len = 0;
      uint8_t *decoded_msg = NULL;
      if (otrl_base64_otr_decode(original_msg, &decoded_msg,
                                 &decoded_msg_len)) {
        return 1;
      }
      if (!otrng_dake_auth_r_deserialize(auth_r_msg, decoded_msg,
                                         decoded_msg_len)) {
        return 1;
      }

      printf("\tSender instance tag: %u\n", auth_r_msg->sender_instance_tag);
      printf("\tReceiver instance tag: %u\n",
             auth_r_msg->receiver_instance_tag);

      // TODO: print profile
      printf("\tProfile:\n");
      printf("\t\tVersions: ");
      size_t n = strlen(auth_r_msg->profile->versions);
      print_string(auth_r_msg->profile->versions, n);

      printf("\t\tExpires: %lu\n", auth_r_msg->profile->expires);

      if (auth_r_msg->profile->dsa_key_len > 0) {
        printf("\t\tDSA Key: ");
        print_hex(auth_r_msg->profile->dsa_key,
                  auth_r_msg->profile->dsa_key_len);
      }

      if (auth_r_msg->profile->transitional_signature) {
        printf("\t\tTransitional Signature: ");
        print_hex(auth_r_msg->profile->transitional_signature,
                  sizeof(auth_r_msg->profile->transitional_signature));
      }

      uint8_t ecdh[ED448_POINT_BYTES] = {0};
      otrng_ec_point_encode(ecdh, auth_r_msg->X);
      printf("\tX: ");
      print_hex(ecdh, ED448_POINT_BYTES);

      size_t dh_size;
      unsigned char *dh_dump;

      if (gcry_mpi_aprint(GCRYMPI_FMT_USG, &dh_dump, &dh_size, auth_r_msg->A)) {
        return 1;
      }

      printf("\tA: ");
      print_hex(dh_dump, dh_size);
      // TODO: Need to print ring signature
      free(dh_dump);
      // TODO: Need to free auth_r_msg
    } else if (header_msg->type == AUTH_I_MSG_TYPE) {
      printf("AUTH-I MESSAGE:\n");
      printf("\tType: %x\n", header_msg->type);
      printf("\tVersion: %x\n", header_msg->version);

      dake_auth_i_p auth_i_msg;
      size_t decoded_msg_len = 0;
      uint8_t *decoded_msg = NULL;
      if (otrl_base64_otr_decode(original_msg, &decoded_msg,
                                 &decoded_msg_len)) {
        return 1;
      }
      if (!otrng_dake_auth_i_deserialize(auth_i_msg, decoded_msg,
                                         decoded_msg_len)) {
        return 1;
      }
      printf("\tSender instance tag: %u\n", auth_i_msg->sender_instance_tag);
      printf("\tReceiver instance tag: %u\n",
             auth_i_msg->receiver_instance_tag);

      /*printf("\tRing Signature Authentication:\n");*/
      /*printf("\t\tc1:");*/
      /*uint8_t c1[ED448_SCALAR_BYTES];*/
      /*goldilocks_448_scalar_decode_long(auth_i_msg->sigma->c1, c1,
       * ED448_SCALAR_BYTES);*/
      /*print_hex(c1, ED448_SCALAR_BYTES);*/
      /*printf("\t\tr1:\n");*/
      /*printf("\t\tc2:\n");*/
      /*printf("\t\tr2:\n");*/
      /*printf("\t\tc3:\n");*/
      /*printf("\t\tr3:\n");*/

      // TODO: Need to free auth_i_msg
    } else if (header_msg->type == DATA_MSG_TYPE) {
      data_message_s *data_msg = otrng_data_message_new();
      result = parse_data_message(data_msg, original_msg);
      print_data_message(header_msg, data_msg);
      otrng_data_message_free(data_msg);
    } else {
      printf("Error while trying to parse encoded message\n");
      return 1;
    }

    free(header_msg);
  } else if (message_type == MSG_OTR_ERROR) {
    print_error_msg(original_msg);
  } else {
    printf("Error: not valid OTRv4 message!\n");
    return 1;
  }

  return result;
}
