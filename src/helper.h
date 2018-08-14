#include <stdio.h>

#include <goldilocks/point_448.h>

#include <libotr-ng/constants.h>
#include <libotr-ng/otrng.h>

#ifndef HELPER_H
#define HELPER_H
static const uint8_t usage_mac_key = 0x17;
static const uint8_t usage_message_key = 0x16;

void print_hex(uint8_t data[], int data_len);
void print_string(char *data, int data_len);
void print_data_message(otrng_header_s *header_msg, data_message_s *data_msg);
void print_plaintext_formated(char *data, int data_len);
void print_identity_message(otrng_header_s *header_msg,
                            dake_identity_message_p identity_msg);
void print_auth_r(otrng_header_s *header_msg, dake_auth_r_p auth_r_msg);
void print_auth_i(otrng_header_s *header_msg, dake_auth_i_p auth_i_msg);
void argv_to_buf(unsigned char **dst, size_t *written, char *arg);
int encrypt_data_message(data_message_s *data_msg, const char *msg,
                         size_t msg_len, const msg_enc_key_p enc_key);
int decrypt_data_message(uint8_t *plain, const msg_enc_key_p enc_key,
                         const data_message_s *msg);
void serialize_and_remac(char **encoded_data_msg, data_message_s *data_msg,
                         uint8_t *new_mac);
void calculate_mac(msg_mac_key_p mac_key, unsigned char *buff);
int modify_message(data_message_s *data_msg, char *original_msg,
                   char *old_msg_txt, char *new_msg_txt, int offset);
#endif
