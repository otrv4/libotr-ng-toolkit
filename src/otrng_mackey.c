#include <string.h>

#include "helper.h"
#include "parse.h"

static void usage(const char *progname) {
  fprintf(stderr,
          "Usage: %s encryption key\n"
          "Calculate and display the MAC key derived from a given encryption "
          "or chain key.\n",
          progname);
  exit(1);
}

int main(int argc, char **argv) {
  unsigned char *argbuf;
  size_t argbuflen;
  unsigned char mac_key[64];

  if (argc != 2) {
    usage(argv[0]);
  }

  argv_to_buf(&argbuf, &argbuflen, argv[1]);

  /* Enc keys are 32 bits long, so check for that */
  if (!argbuf) {
    usage(argv[0]);
  }

  if (argbuflen != 32) {
    fprintf(stderr, "The encryption key must be 32 hex chars long.\n");
    usage(argv[0]);
  }

  calculate_mac_key(mac_key, argbuf);

  dump_data(stdout, "Encryption key", argbuf, 32);
  dump_data(stdout, "MAC key", mac_key, 64);

  free(argbuf);
  fflush(stdout);
  return 0;
}
