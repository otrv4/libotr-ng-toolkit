#include <stdio.h>

#include <libotr-ng/dake.h>

#include "parse.h"
#include "readotr.h"
#include "helper.h"

int main(int argc, char **argv) {
  char *original_msg = NULL;
  original_msg = readotr(stdin);

  int message_type = otrng_get_message_type(original_msg);
  int result = 1;
  #define WHITESPACE_TAG_BASE_BYTES 16
  #define WHITESPACE_TAG_VERSION_BYTES 8
  if(message_type == MSG_PLAINTEXT) {
    printf("PLAIN TEXT: ");
    print_string(original_msg, strlen(original_msg));
  } else if(message_type == MSG_TAGGED_PLAINTEXT) {
    printf("PLAIN TEXT WITH WHITESPACE TAGS: ");
    print_plaintext_formated(original_msg, strlen(original_msg));
  }else if(message_type == MSG_QUERY_STRING){
    printf("QUERY STRING: ");
    print_string(original_msg, strlen(original_msg));
  } else if (message_type == MSG_OTR_ENCODED) {
    otrng_header_s *header_msg = malloc(sizeof(otrng_header_s));
    result = parse_header(header_msg, original_msg);

    if (header_msg->type == 0x35) {
      printf("IDENTITY MESSAGE:\n");
      printf("\tType: %x\n", header_msg->type);
      printf("\tVersion: %x\n", header_msg->version);

      dake_identity_message_p identity_msg;
      size_t decoded_msg_len = 0;
      uint8_t *decoded_msg = NULL;
      if (otrl_base64_otr_decode(original_msg, &decoded_msg, &decoded_msg_len)) {
        return 1;
      }

      if (!otrng_dake_identity_message_deserialize(identity_msg, decoded_msg, decoded_msg_len)) {
        return 1;
      }

      printf("\tSender instance tag: %u\n", identity_msg->sender_instance_tag);
      printf("\tReceiver instance tag: %u\n", identity_msg->receiver_instance_tag);

      /*m->profile->long_term_pub_key (otrng_public_key_p)*/
      printf("\tProfile:\n");

      printf("\t\tVersions: ");
      size_t n = strlen(identity_msg->profile->versions);
      print_string(identity_msg->profile->versions, n);

      printf("\t\tExpires: %lu\n",identity_msg->profile->expires);

      if (identity_msg->profile->dsa_key_len > 0) {
        printf("\t\tDSA Key: ");
        print_hex(identity_msg->profile->dsa_key, identity_msg->profile->dsa_key_len);
      }

      if (identity_msg->profile->transitional_signature) {
        printf("\t\tTransitional Signature: ");
        print_hex(
                identity_msg->profile->transitional_signature,
                sizeof(identity_msg->profile->transitional_signature));
      }
      printf("\t\tSignature: ");
      print_hex(identity_msg->profile->signature,ED448_SIGNATURE_BYTES);

      uint8_t ecdh[ED448_POINT_BYTES] = {0};
      otrng_ec_point_encode(ecdh, identity_msg->Y);
      printf("\tY: ");
      print_hex(ecdh, ED448_POINT_BYTES);

      size_t dh_size;
      unsigned char *dh_dump;

      if (gcry_mpi_aprint(GCRYMPI_FMT_USG, &dh_dump, &dh_size, identity_msg->B)) {
        return 1;
      }

      printf("\tB: ");
      print_hex(dh_dump, dh_size);
      free(dh_dump);
      otrng_dake_identity_message_destroy(identity_msg);
    } else {
      data_message_s *data_msg = otrng_data_message_new();
      result = parse_data_message(data_msg, original_msg);
      print_data_message(header_msg, data_msg);
      otrng_data_message_free(data_msg);
    }

    free(header_msg);
  } else if (message_type == MSG_OTR_ERROR) {
    print_error_msg(original_msg);
  }

  return result;
}
