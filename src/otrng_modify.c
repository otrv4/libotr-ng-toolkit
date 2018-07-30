#include "decode.h"
#include "helper.h"
#include "readotr.h"

static int char_to_hex(char c) {
  if (c >= '0' && c <= '9')
    return (c - '0');
  if (c >= 'a' && c <= 'f')
    return (c - 'a' + 10);
  if (c >= 'A' && c <= 'F')
    return (c - 'A' + 10);
  return -1;
}

int argv_to_uncoded(unsigned char **uncoded, int *uncoded_len, char *arg) {
  *uncoded = NULL;
  *uncoded_len = 0;

  int len = strlen(arg);
  if (len % 2) {
    fprintf(stderr, "Argument ``%s'' must have even length.\n", arg);
    return 1;
  }
  unsigned char *buf = malloc(len / 2);
  if (buf == NULL && len > 0) {
    fprintf(stderr, "Out of memory!\n");
    return 1;
  }

  for (int i = 0; i < len / 2; ++i) {
    int hi = char_to_hex(arg[2 * i]);
    int lo = char_to_hex(arg[2 * i + 1]);
    if (hi < 0 || lo < 0) {
      free(buf);
      fprintf(stderr, "Illegal hex char in argument ``%s''.\n", arg);
      return 1;
    }
    buf[i] = (hi << 4) + lo;
  }
  *uncoded = buf;
  *uncoded_len = len / 2;
  return 0;
}

int main(int argc, char **argv) {
  int result = 0;

  int mac_len;
  unsigned char *mac;

  if (argc != 6) {
    puts("Incorrect number of arguments");
    return 1;
  }

  result = argv_to_uncoded(&mac, &mac_len, argv[1]);

  if (result != 0) {
    puts("An error ocurred!");
    return result;
  }

  if (mac_len != 64) {
    puts("Wrong MAC size");
    return 1;
  }

  char *old_msg_txt = argv[2];
  char *new_msg_txt = argv[3];
  int offset = strtol(argv[4], NULL, 10);

  if (strlen(old_msg_txt) != strlen(new_msg_txt)) {
    puts("Old message text size must be equal to new message text size");
    return 1;
  }

  char *original_msg = argv[5];

  if (original_msg == NULL) {
    puts("Missing a data message");
    return 1;
  }

  int message_type = otrng_get_message_type(original_msg);

  if (message_type != MSG_OTR_ENCODED) {
    puts("The OTR message is not an otr encoded message");
    return 1;
  }

  otrng_header_s *header_msg = malloc(sizeof(otrng_header_s));
  if (!header_msg) {
    return 1;
  }

  result = decode_header(header_msg, original_msg);

  if (result != 0) {
    puts("Error on decode header of message");
    return 1;
  }

  if (header_msg->type != DATA_MSG_TYPE) {
    puts("Message is not a data message");
    return 1;
  }

  data_message_s *data_msg = otrng_data_message_new();
  result = decode_data_message(data_msg, original_msg);

  if (result != 0) {
    puts("Error decoding data message");
    return 1;
  }

  for (int i = 0; i < strlen(old_msg_txt) && offset + 1 < data_msg->enc_msg_len;
       i++) {
    data_msg->enc_msg[offset + i] ^= (old_msg_txt[i] ^ new_msg_txt[i]);
  }

  // - Recalculate the MAC tag with the revealed MAC key associated with this
  //   message. The new tag is attached to the data message, replacing the old
  //   value.

  otrng_data_message_free(data_msg);
  return result;
}
