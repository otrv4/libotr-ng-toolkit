#include <stdio.h>
#include <string.h>

#include <libotr/b64.h>

#include <libotr-ng/constants.h>
#include <libotr-ng/data_message.h>
#include <libotr-ng/dh.h>
#include <libotr-ng/otrng.h>

int parse_data_message(data_message_s *body_msg, const char *original_msg);
int parse_header(otrng_header_s *header_msg, const char *original_msg);
