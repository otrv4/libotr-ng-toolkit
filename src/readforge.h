#include <string.h>

#include <libotr-ng/data_message.h>
#include <libotr-ng/key_management.h>
#include <libotr-ng/random.h>
#include <libotr-ng/shake.h>

#include "decode.h"
#include "helper.h"

int readforge(char **encoded_data_msg, char *raw_ratchet_key, char *raw_msg,
              uint8_t *new_txt_msg);
