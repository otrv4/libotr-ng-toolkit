#include <string.h>

#include "helper.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr,
            "Usage: %s aeskey\n"
            "Calculate and display the MAC key derived from a given AES key.\n",
            argv[0]);
    exit(1);
    printf("argv[1] %s\n", argv[1]);
  }

  unsigned char *argbuf;
  size_t argbuflen;
  argv_to_buf(&argbuf, &argbuflen, argv[1]);
  msg_mac_key_p mac_key;

  calculate_mac(mac_key, argbuf);
  print_hex(mac_key, sizeof(msg_mac_key_p));

  free(argbuf);
  return 0;
}
