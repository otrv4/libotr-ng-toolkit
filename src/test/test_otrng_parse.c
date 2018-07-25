#include <glib.h>
#include <stdbool.h>
#include <string.h>

#include <libotr-ng/otrng.h>

#include "../parse.c"
#include "test_helpers.h"

void otrng_toolkit_test_parse_data_message() {
  const char *msg = "?OTR:AAQDHKKD8mktib4AAAAAAQAAAAQAAAAA3tx0zejuaJ/lluHxdK+xETw2t9nxWJgjbZWjiDHD6ibwJdyURAJenucUz9pHMkrwxfEpldE+sr2AAAABgINwoW3ufscly5eMIqj+HxuayAKNFr0woDbJX203VcHqmI29zC6GbVMwXS4HV8jMxtIulwpX1V/biQa0mQRqfdRLCnKHtrkhPly212rZzajHUF34TGaznfW/rB68+VELAYy9P9gEg/Vjup7qDBd7JWlIXYbrKt5vqfXlgyKWNlLUQrRc8ppwzrP5jnPh+dB5tcEXvx7nISAC3Hjlt83JmEGIDuSqzi4K4WdeNwB9wfU90ITaEdt+1lqeYcd9XBfLIxQhJFyqFrYURt/1dC0DyhIGHCi95GTtnOp8qTlzp69/egWDYg/SCLDKMiAA3RSliUMlEsXQZNNOTvY5oVsZir4P4ur5bo+mACgLkS+zt78p6saLIEYDRwIgnKJ2GSN3Tqkij4Xz4O297Ug3YzUn/mg9pFmAXkPbJwFH/929cz88HznqENfPIcVbFyJfGsFmXIJc2wWROLhLCtgy4F20ShwH4aWwdEA/vqi9E2dxsL2XSGbG60zNTEVb+Q9BQMawm6pWppRz2kQ9Tpr80Km9sTO8zonbZwLtwwAAAP8hxmJj8/HHIm1KPYKa3SFHEeJFwbgvHOqFTNNeEdmwhw/nF1JBFfqZh7R2sjFYfYoxa28Njs4osVm4UsrPPbFhZQzkifL/gIL+M8yZTLgLdd/3w/tlNj2+RLjYiwk6aQ1PFGYj/iIKbYRwtKtLwm2o2ruKCsj8G0D9G3HumiW7SPNEjuzav7KUFOigY80dd/2Gp2aq8Jd1oTrxICDJFlStKgWGki+M8gZeYUngVoBJNv+ZSzr64iT3mEwVXbPT+12TYeJNJHLWbZ6fOt6lNlT37ZFYURzgD3XEdd884aZeUQlkdFln+XA4Cut4/DM1XiWMlKBQpecVOtHwShQ2MtKopKH/bDcpMNLoC3tF0EkF4SLYPLxt/TZU/iDljTf3Lnv7NTUCte43qBl8Q4BOOVjfAzJRDQUiPECRESpbRcysg20XklPJJAyXfhvQByjW66Df3JUQU7wEvvG2BEqSuMGq1XLNS9xAhW9NUNBizwg/dMplb6j3hqVIwMUshgO7RooM6RtxYHS6+BnEVolr5ksd2EIHgxrxH2ER+X9EKZkFM/BmpHqcB4VvSUUNquzo3N2uhxl1P6Qo14kY9fh3Uac=.";
  data_message_s *data_msg = otrng_data_message_new();
  otrng_header_s *header_msg = malloc(sizeof(otrng_header_s));

  g_assert_cmpint(parse(data_msg, header_msg, msg), ==, 0);
  g_assert_cmpint(header_msg->type, ==, DATA_MSG_TYPE);
  g_assert_cmpint(header_msg->version, ==, OTRNG_ALLOW_V4);
  g_assert_cmpint(data_msg->sender_instance_tag, ==, 480412658);
  g_assert_cmpint(data_msg->receiver_instance_tag, ==, 1764592062);
  g_assert_cmpint(sizeof(data_msg->nonce), ==, DATA_MSG_NONCE_BYTES);
  otrng_assert(true == otrng_ec_point_valid(data_msg->ecdh));
  //otrng_assert(true == otrng_dh_mpi_valid(data_msg->dh));
  g_assert_cmpint(sizeof(data_msg->mac), ==, DATA_MSG_MAC_BYTES);


  otrng_data_message_free(data_msg);
  free(header_msg);
}
