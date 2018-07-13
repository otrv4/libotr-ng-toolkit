#include <stdio.h>
#include <stdlib.h>
#include <gcrypt.h>

/* Implementation of SHA1-HMAC.  We're rolling our own just to
 * double-check that the calls libotr makes to libgcrypt are in fact
 * doing the right thing. */
void sha1hmac(unsigned char digest[20], unsigned char key[20],
	unsigned char *data, size_t datalen)
{
    unsigned char ipad[64], opad[64];
    size_t i;
    gcry_md_hd_t sha1;
    gcry_error_t err;
    unsigned char hash[20];

    memset(ipad, 0, 64);
    memset(opad, 0, 64);
    memmove(ipad, key, 20);
    memmove(opad, key, 20);
    for(i=0;i<64;++i) {
	ipad[i] ^= 0x36;
	opad[i] ^= 0x5c;
    }

    err = gcry_md_open(&sha1, GCRY_MD_SHA1, 0);
    if (err) {
	fprintf(stderr, "Error: %s\n", gcry_strerror(err));
	exit(1);
    }
    gcry_md_write(sha1, ipad, 64);
    gcry_md_write(sha1, data, datalen);
    memmove(hash, gcry_md_read(sha1, 0), 20);
    gcry_md_reset(sha1);
    gcry_md_write(sha1, opad, 64);
    gcry_md_write(sha1, hash, 20);
    memmove(digest, gcry_md_read(sha1, 0), 20);
    gcry_md_close(sha1);
}
