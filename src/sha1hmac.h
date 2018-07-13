#ifndef __SHA1HMAC_H__
#define __SHA1HMAC_H__
#include <stdlib.h>

/* Implementation of SHA1-HMAC.  We're rolling our own just to
 * double-check that the calls libotr makes to libgcrypt are in fact
 * doing the right thing. */
void sha1hmac(unsigned char digest[20], unsigned char key[20],
	unsigned char *data, size_t datalen);

#endif
