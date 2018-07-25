#include <stdio.h>

#include <libotr-ng/constants.h>
#include <libotr-ng/otrng.h>

void print_hex(uint8_t data[], int data_len){
  for(int i=0; i < data_len; i++) {
    printf("%02x", data[i]);
  }
  printf("\n");
};

void print_data_message(otrng_header_s *header_msg, data_message_s *data_msg){
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

  uint8_t ecdh[ED448_POINT_BYTES] = {0};
  otrng_ec_point_encode(ecdh, data_msg->ecdh);
  printf("\tECDH: ");
  print_hex(ecdh, ED448_POINT_BYTES);

  size_t dh_size;
  unsigned char *dh_dump;
  gcry_mpi_print(GCRYMPI_FMT_USG, NULL, 0, &dh_size, data_msg->dh);
  dh_dump = malloc(dh_size);
  gcry_mpi_print(GCRYMPI_FMT_USG, dh_dump, dh_size, NULL, data_msg->dh);
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