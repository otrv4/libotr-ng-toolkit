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

int otrng_toolkit_parse_encoded_message(const char *message);

#endif
