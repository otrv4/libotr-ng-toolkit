#ifndef PARSE_H
#define PARSE_H

// TODO: define the return errors

int otrng_toolkit_parse_encoded_message(const char *message);

/* Dump data to a FILE */
void dump_data(FILE *stream, const char *title, const unsigned char *data,
               size_t datalen);
#endif
