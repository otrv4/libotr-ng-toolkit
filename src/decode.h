#include <stdio.h>
#include <string.h>

#include <libotr/b64.h>

#include <libotr-ng/constants.h>
#include <libotr-ng/data_message.h>
#include <libotr-ng/dh.h>
#include <libotr-ng/otrng.h>

#ifndef DECODE_H
#define DECODE_H

// TODO: if this are going to be exported, they should have the otrng_toolkit
// TODO: define the return errors

int decode_encoded_message(const char *message);

int decode_header(otrng_header_s *header_msg, const char *original_msg);
int decode_identity_message(dake_identity_message_p identity_msg,
                            const char *original_msg);
int decode_auth_r_message(dake_auth_r_p auth_r_msg, const char *original_msg);
int decode_auth_i_message(dake_auth_i_p auth_i_msg, const char *original_msg);
#endif
