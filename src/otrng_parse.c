#include <stdio.h>
#include "parse.h"
#include "readotr.h"

int main(int argc, char **argv) {
  char *original_msg = NULL;
  original_msg = readotr(stdin);

  data_message_s *data_msg = otrng_data_message_new();
  otrng_header_s *header_msg = malloc(sizeof(otrng_header_s));

  int result = parse(data_msg, header_msg, original_msg);

  printf("Data message:\n");
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

  uint8_t pubkey[ED448_POINT_BYTES] = {0};
  otrng_ec_point_encode(pubkey, data_msg->ecdh);
  printf("\tECDH: ");
  for(int i=0; i < ED448_POINT_BYTES; i++) {
    printf("%02x", pubkey[i]);
  }
  printf("\n");

  size_t dh_size;
  unsigned char *dh_dump;
  gcry_mpi_print(GCRYMPI_FMT_USG, NULL, 0, &dh_size, data_msg->dh);
  dh_dump = malloc(dh_size);
  gcry_mpi_print(GCRYMPI_FMT_USG, dh_dump, dh_size, NULL, data_msg->dh);
  printf("\tDH: ");
  for(int i=0; i < dh_size; i++) {
    printf("%02x", dh_dump[i]);
  }
  free(dh_dump);
  printf("\n");
  
  printf("\tNonce: ");
  for(int i=0; i < DATA_MSG_NONCE_BYTES; i++) {
    printf("%02x", data_msg->nonce[i]);
  }
  printf("\n");

  printf("\tEncrypted message: ");
  for(int i=0; i < data_msg->enc_msg_len; i++) {
    printf("%02x", data_msg->enc_msg[i]);
  }
  printf("\n");

  printf("\tMAC: ");
  for(int i=0; i < DATA_MSG_MAC_BYTES; i++) {
    printf("%02x", data_msg->mac[i]);
  }
  printf("\n");

  free(header_msg);
  otrng_data_message_free(data_msg);
  return result;
}
