#include "helper.h"

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
  int result = 1;

  int mac_len;
  unsigned char *mac;

  result = argv_to_uncoded(&mac, &mac_len, argv[1]);

  if (mac_len != 64) {
    puts("Wrong MAC size");
    result = 1;
  }
  return result;
}
