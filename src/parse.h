#include <libotr-ng/otrng.h>
#include <libotr-ng/prekey_messages.h>

#ifndef PARSE_H
#define PARSE_H

// TODO: define the return errors

/* Dump data to a FILE */
void dump_data(FILE *stream, const char *title, const unsigned char *data,
               size_t datalen);
void argv_to_buf(unsigned char **dst, size_t *written, char *arg);

int otrng_toolkit_parse_encoded_message(const char *message);

int otrng_toolkit_get_prekey_message_type(const char *message);

int otrng_toolkit_parse_prekey_message(const char *message);

#endif
