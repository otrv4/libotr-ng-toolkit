#include <string.h>

#include <libotr-ng/key_management.h>
#include <libotr-ng/shake.h>

#include "helper.h"

#define hash_update goldilocks_shake256_update
#define hash_final goldilocks_shake256_final
#define hash_destroy goldilocks_shake256_destroy

static uint8_t usage_mac_key = 0x17;

static int ctoh(char c) {
  if (c >= '0' && c <= '9')
    return (c - '0');
  if (c >= 'a' && c <= 'f')
    return (c - 'a' + 10);
  if (c >= 'A' && c <= 'F')
    return (c - 'A' + 10);
  return -1;
}

void argv_to_buf(unsigned char **bufp, size_t *lenp, char *arg) {
  unsigned char *buf;
  size_t len, i;
  *bufp = NULL;
  *lenp = 0;
  len = strlen(arg);
  if (len % 2) {
    fprintf(stderr, "Argument ``%s'' must have even length.\n", arg);
    return;
  }
  buf = malloc(len / 2);
  if (buf == NULL && len > 0) {
    fprintf(stderr, "Out of memory!\n");
    return;
  }
  for (i = 0; i < len / 2; ++i) {
    int hi = ctoh(arg[2 * i]);
    int lo = ctoh(arg[2 * i + 1]);
    if (hi < 0 || lo < 0) {
      free(buf);
      fprintf(stderr, "Illegal hex char in argument ``%s''.\n", arg);
      return;
    }
    buf[i] = (hi << 4) + lo;
  }
  *bufp = buf;
  *lenp = len / 2;
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
