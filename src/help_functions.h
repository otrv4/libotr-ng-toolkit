#include <stdio.h>

#include <libotr-ng/constants.h>
#include <libotr-ng/otrng.h>

void print_string(char *data, int data_len);
void print_data_message(otrng_header_s *header_msg, data_message_s *data_msg);
void print_error_msg(char *data);