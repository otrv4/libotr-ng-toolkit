#include <string.h>

#include <libotr-ng/key_management.h>
#include <libotr-ng/shake.h>

#include "helper.h"

static uint8_t usage_mac_key = 0x17;

int main(int argc, char **argv) {
  if (argc != 2) {
    return 1;
  }

  unsigned char *argbuf;
  size_t argbuflen;
  argv_to_buf(&argbuf, &argbuflen, argv[1]);

  msg_mac_key_p mac_key;
  memset(mac_key, 0, sizeof(msg_mac_key_p));

  shake_256_kdf1(mac_key, sizeof(msg_mac_key_p), usage_mac_key, argbuf,
                 sizeof(msg_enc_key_p));

  print_hex(mac_key, sizeof(msg_mac_key_p));

  return 0;
}
