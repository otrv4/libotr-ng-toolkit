#include <libotr-ng/otrng.h>

#include "parse.h"
#include "read_otr.h"

int otrng_toolkit_parse_message(char *msg) {
  int message_type;

  message_type = otrng_get_message_type(msg);

  switch (message_type) {
  case MSG_PLAINTEXT:
    printf("Plain text message:\n\t%s\n\n", msg);
    break;
  case MSG_TAGGED_PLAINTEXT:
    printf("OTRv4 Tagged plaintext message:\n\t%s\n\n", msg);
    break;
  case MSG_QUERY_STRING:
    printf("OTRv4 Query message: :\n\t%s\n\n", msg);
    break;
  case MSG_OTR_ERROR:
    printf("OTR Error:\n\t%s\n\n", msg);
    break;
  case MSG_OTR_ENCODED:
    if (!otrng_toolkit_parse_encoded_message(msg)) {
      return 0;
    };
  }

  if (otrng_toolkit_get_prekey_message_type(msg) == 1) {
    otrng_toolkit_parse_prekey_message(msg);
  }

  return 1;
}

static void usage(const char *progname) {
  fprintf(stderr,
          "Usage: %s\n"
          "Read Off-the-Record v4 (OTRv4) Deniable Key Exchange and/or Data "
          "messages from stdin\n"
          "and display their contents in a more readable format.\n",
          progname);
  exit(1);
}

int main(int argc, char **argv) {
  char *message = NULL;
  int result = 0;

  if (argc != 1) {
    usage(argv[0]);
  }

  while ((message = read_otr_message(stdin)) != NULL) {
    otrng_toolkit_parse_message(message);
    free(message);
  }

  return result;
}
