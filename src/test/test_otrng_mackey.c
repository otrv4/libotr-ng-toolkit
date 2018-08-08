#include "../helper.c"
#include "test_helpers.h"

void otrng_toolkit_test_calculate_mac_key() {
  char *aeskey =
      "e90645447da92df66fbdf3b399078c2e01b28b30c60b2df726ce4fd82ba03971";

  unsigned char *argbuf;
  size_t argbuflen;
  msg_mac_key_p mac_key;

  argv_to_buf(&argbuf, &argbuflen, aeskey);

  calculate_mac(mac_key, argbuf);
  otrng_toolkit_assert(mac_key != 0);
  free(argbuf);
}
