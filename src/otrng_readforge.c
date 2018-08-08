#include <stdio.h>
#include <string.h>

#include <libotr-ng/data_message.h>
#include <libotr-ng/key_management.h>
#include <libotr-ng/random.h>
#include <libotr-ng/shake.h>

#include "decode.h"
#include "helper.h"
#include "readforge.h"

int main(int argc, char **argv) {
  uint8_t *new_txt_msg = NULL;

  if (argc == 4) {
    new_txt_msg = (uint8_t *)argv[3];
  }

  char *original_msg = argv[2];
  char *mac_key = argv[1];

  char *encoded_data_msg = NULL;

  if (readforge(&encoded_data_msg, mac_key, original_msg, new_txt_msg)) {
    return 1;
  }

  if (encoded_data_msg) {
    printf("New data message: %s\n", encoded_data_msg);
  }

  return 0;
}
