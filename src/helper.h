#include <stdio.h>

#include <goldilocks/point_448.h>

#include <libotr-ng/constants.h>
#include <libotr-ng/otrng.h>

void print_string(char *data, int data_len);
void print_data_message(otrng_header_s *header_msg, data_message_s *data_msg);
void print_error_msg(char *data);
void print_plaintext_formated(char *data, int data_len);
void print_identity_message(dake_identity_message_p identity_msg);
void print_auth_r(dake_auth_r_p auth_r_msg);
void print_auth_i(dake_auth_i_p auth_i_msg);