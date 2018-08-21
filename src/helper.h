#include <stdio.h>

#include <goldilocks/point_448.h>

#include <libotr-ng/constants.h>
#include <libotr-ng/otrng.h>

#ifndef HELPER_H
#define HELPER_H

static const uint8_t usage_message_key = 0x16;

int encrypt_data_message(data_message_s *data_msg, const char *msg,
                         size_t msg_len, const msg_enc_key_p enc_key);
int decrypt_data_message(uint8_t *plain, const msg_enc_key_p enc_key,
                         const data_message_s *msg);
void serialize_and_remac(char **encoded_data_msg, data_message_s *data_msg,
                         uint8_t *new_mac);
void calculate_mac_key(msg_mac_key_p mac_key, unsigned char *buff);

// int modify_message(data_message_s *data_msg, char *original_msg,
//                   char *old_msg_txt, char *new_msg_txt, int offset);
#endif
