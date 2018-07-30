#include <string.h>

#include <libotr-ng/key_management.h>
#include <libotr-ng/shake.h>

#include "helper.h"

#define hash_update goldilocks_shake256_update
#define hash_final goldilocks_shake256_final
#define hash_destroy goldilocks_shake256_destroy

static uint8_t usage_mac_key = 0x17;

void argv_to_buf(unsigned char **dst, size_t *written, char *arg) {
  unsigned char *buf;
  *dst = NULL;
  *written = 0;
  size_t size = strlen(arg);

  if (size % 2) {
    fprintf(stderr, "Argument ``%s'' must have even length.\n", arg);
    return;
  }

  buf = malloc(size / 2);
  if (buf == NULL) {
    fprintf(stderr, "Out of memory!\n");
    return;
  }

  char *b = malloc(2);
  for (int i = 0; i < size / 2; i++) {
    printf("arg: %s\n", arg);
    printf("arg len: %zu\n", strlen(arg));
    strncpy(b, arg, 2);
    arg += 2;
    buf[i] = (int)strtol(b, NULL, 16);
    printf("%s -> %d\n", b, buf[i]);
  }
  free(b);

  *dst = buf;
  *written = size / 2;
}

void shake_256_kdf1(uint8_t *dst, size_t dstlen, uint8_t usage,
                    const uint8_t *values, size_t valueslen) {
  goldilocks_shake256_ctx_p hd;
  hash_init_with_usage(hd, usage);

  hash_update(hd, values, valueslen);
  hash_final(hd, dst, dstlen);
  hash_destroy(hd);
}

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
