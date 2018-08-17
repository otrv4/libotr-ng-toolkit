#include <libotr-ng/otrng.h>

#include "../decode.c"
#include "test_helpers.h"

void otrng_toolkit_test_parse_data_message() {
  return;
//  const char *msg =
//      "?OTR:AAQDHKKD8mktib4AAAAAAQAAAAQAAAAA3tx0zejuaJ/"
//      "lluHxdK+xETw2t9nxWJgjbZWjiDHD6ibwJdyURAJenucUz9pHMkrwxfEpldE+"
//      "sr2AAAABgINwoW3ufscly5eMIqj+"
//      "HxuayAKNFr0woDbJX203VcHqmI29zC6GbVMwXS4HV8jMxtIulwpX1V/"
//      "biQa0mQRqfdRLCnKHtrkhPly212rZzajHUF34TGaznfW/rB68+VELAYy9P9gEg/"
//      "Vjup7qDBd7JWlIXYbrKt5vqfXlgyKWNlLUQrRc8ppwzrP5jnPh+"
//      "dB5tcEXvx7nISAC3Hjlt83JmEGIDuSqzi4K4WdeNwB9wfU90ITaEdt+"
//      "1lqeYcd9XBfLIxQhJFyqFrYURt/1dC0DyhIGHCi95GTtnOp8qTlzp69/egWDYg/"
//      "SCLDKMiAA3RSliUMlEsXQZNNOTvY5oVsZir4P4ur5bo+mACgLkS+"
//      "zt78p6saLIEYDRwIgnKJ2GSN3Tqkij4Xz4O297Ug3YzUn/mg9pFmAXkPbJwFH/"
//      "929cz88HznqENfPIcVbFyJfGsFmXIJc2wWROLhLCtgy4F20ShwH4aWwdEA/"
//      "vqi9E2dxsL2XSGbG60zNTEVb+"
//      "Q9BQMawm6pWppRz2kQ9Tpr80Km9sTO8zonbZwLtwwAAAP8hxmJj8/"
//      "HHIm1KPYKa3SFHEeJFwbgvHOqFTNNeEdmwhw/"
//      "nF1JBFfqZh7R2sjFYfYoxa28Njs4osVm4UsrPPbFhZQzkifL/gIL+M8yZTLgLdd/3w/"
//      "tlNj2+RLjYiwk6aQ1PFGYj/"
//      "iIKbYRwtKtLwm2o2ruKCsj8G0D9G3HumiW7SPNEjuzav7KUFOigY80dd/"
//      "2Gp2aq8Jd1oTrxICDJFlStKgWGki+M8gZeYUngVoBJNv+ZSzr64iT3mEwVXbPT+"
//      "12TYeJNJHLWbZ6fOt6lNlT37ZFYURzgD3XEdd884aZeUQlkdFln+XA4Cut4/"
//      "DM1XiWMlKBQpecVOtHwShQ2MtKopKH/bDcpMNLoC3tF0EkF4SLYPLxt/TZU/"
//      "iDljTf3Lnv7NTUCte43qBl8Q4BOOVjfAzJRDQUiPECRESpbRcysg20XklPJJAyXfhvQByjW6"
//      "6Df3JUQU7wEvvG2BEqSuMGq1XLNS9xAhW9NUNBizwg/"
//      "dMplb6j3hqVIwMUshgO7RooM6RtxYHS6+BnEVolr5ksd2EIHgxrxH2ER+X9EKZkFM/"
//      "BmpHqcB4VvSUUNquzo3N2uhxl1P6Qo14kY9fh3Uac=.";
//  data_message_s *data_msg = otrng_data_message_new();
//  otrng_header_s *header_msg = malloc(sizeof(otrng_header_s));
//  if (!header_msg) {
//    return;
//  }
//
//  uint8_t nonce[DATA_MSG_NONCE_BYTES] = {
//      0xaa, 0x56, 0xa6, 0x94, 0x73, 0xda, 0x44, 0x3d, 0x4e, 0x9a, 0xfc, 0xd0,
//      0xa9, 0xbd, 0xb1, 0x33, 0xbc, 0xce, 0x89, 0xdb, 0x67, 0x02, 0xed, 0xc3,
//  };
//  uint8_t mac[DATA_MSG_MAC_BYTES] = {
//      0xa8, 0xa4, 0xa1, 0xff, 0x6c, 0x37, 0x29, 0x30, 0xd2, 0xe8, 0x0b,
//      0x7b, 0x45, 0xd0, 0x49, 0x05, 0xe1, 0x22, 0xd8, 0x3c, 0xbc, 0x6d,
//      0xfd, 0x36, 0x54, 0xfe, 0x20, 0xe5, 0x8d, 0x37, 0xf7, 0x2e, 0x7b,
//      0xfb, 0x35, 0x35, 0x02, 0xb5, 0xee, 0x37, 0xa8, 0x19, 0x7c, 0x43,
//      0x80, 0x4e, 0x39, 0x58, 0xdf, 0x03, 0x32, 0x51, 0x0d, 0x05, 0x22,
//      0x3c, 0x40, 0x91, 0x11, 0x2a, 0x5b, 0x45, 0xcc, 0xac,
//  };
//
//  g_assert_cmpint(decode_header(header_msg, msg), ==, 0);
//  g_assert_cmpint(decode_data_message(data_msg, msg), ==, 0);
//  g_assert_cmpint(header_msg->type, ==, DATA_MSG_TYPE);
//  g_assert_cmpint(header_msg->version, ==, 4);
//  g_assert_cmpint(data_msg->sender_instance_tag, ==, 480412658);
//  g_assert_cmpint(data_msg->receiver_instance_tag, ==, 1764592062);
//  otrng_toolkit_assert_cmpmem(data_msg->nonce, nonce, DATA_MSG_NONCE_BYTES);
//  otrng_toolkit_assert(otrng_ec_point_valid(data_msg->ecdh) == 1);
//  // TODO: this segfaults
//  // otrng_toolkit_assert(otrng_dh_mpi_valid(data_msg->dh) == 1);
//  otrng_toolkit_assert_cmpmem(data_msg->mac, mac, DATA_MSG_MAC_BYTES);
//
//  otrng_data_message_free(data_msg);
//  free(header_msg);
}

void otrng_toolkit_test_parse_identity_message() {
  return;
  const char *msg =
      "?OTR:AAQ16j7KWgAAAAAAAAAEAAHqPspaAAIAEOQKxW36YA3xat70+FogpP+"
      "58B0x9sEFeMpsEFeM35Vq01InkAmEHE4HLUWRgymjS7aOX0G6aoz4gAAEAAAAAzM0AAAFAAA"
      "AAFtx1G30j7wBCbrDMb8gTNFDkNiqqbUV6fLCjErpQ9CjpYEZybd8jAl2go2i5pjhZ+"
      "eVO2kIxyF567MCV4BU/Z5utiN5lT9JDWXkpZgTQpas/IKYrSAJAe0awXskxQoKrAA/"
      "pbTasCXLLDWSyqYQXgqo1gIQNgByMJLIwvH7daO8WcznLC2OAKvizY2MN2nWGn8ZNr2L7ZX+"
      "m+BlLFvC19DwVuqP7K5a2PP/"
      "NhBdcgAAAAGAjGBp2urSLgeuyMxWBDyrLdDijIph5cocjsEBT9I2Xk4tmbz9zNDxk9a/"
      "G5tlti/Qmn5ApkMVO7Zw1l7/eoHkD3w/nkYHo7oXrwLcAI7pzgaPY7Yln+HgD1jA/"
      "4TdA5GQpAFvlNcz+wKM69c2PCAuPxgwuYBIEhXeRlolZ4A3Ekz6Um7TsPEDhlTeG/"
      "rjj8fbc+Ezmbe0filEfchYh7Y150N0ufwtA0HD2eAfp9L1CYAO/"
      "1Iwgri9v7togUltozUI+h9xyED/"
      "Pya3up6LYeNO1G9BsIZHdep9hB4RATOo1VQ3kGW3wAtqH4gKQ/"
      "1L94IpD5WKKIZFuQpDVurB1tjr3DB9LtJbrq6ePnA/"
      "xroDB07uLzwYoYpOx1ydAz9m1iweqIMvfAaGfiii+yWx2olo/"
      "KzoqcysEEZwRCKBGjostHgXGJ0OrWWsvB/lFOD/V4go4wihzkzc6vCoG51xYIYxK1OkOC/"
      "MtWZa3c6KArc3tUUcp1Orbs7sYvpNZWBHm1rt.";

  dake_identity_message_p identity_msg;
  int result = decode_identity_message(identity_msg, msg);
  otrng_toolkit_assert(result == 0);

  g_assert_cmpint(identity_msg->sender_instance_tag, ==, 3929983578);
  g_assert_cmpint(identity_msg->receiver_instance_tag, ==, 0);
  otrng_dake_identity_message_destroy(identity_msg);
}

void otrng_toolkit_test_parse_auth_r_message() {
  return;
  const char *msg =
      "?OTR:AAQ2HKKD8mktib4AAAAEAAEcooPyAAIAEJ7HWugLaW5KhW5M2X8Wsa18P2RdU+"
      "hCC0X/uPtF1LbNMVPVQ2mq/q1SHPOC7La+DE65cRQ5/"
      "8JhAAAEAAAAAzM0AAAFAAAAAFtrcKUAgkfG3DHjFWUK8hk1Jf9wdOQ03xI10ZXiZzj21k6Wq"
      "0UAtbNrvMavetxfuEhrVGgu8ird+KF2X4ATcrtXttxBl8uol3S7gKP1J12GWRnpl3b7lL+"
      "rVcKt2q3Cxk5k6w9D+4btmjSpTCQxukxOmYORGAAWFCGKSTvKd1NXIxTSK+/"
      "SRaoJ606mW2TR6tlWjNZ8yGMaEQVZDTx2J0MH1Ju8wfUk8v+"
      "0lbR7awAAAAGAMvUK5YC3mzepve3LgFzcQ0w4m2BxBy/"
      "Z0LF8m8jkLMMwiklwVzcktpxD2NK7gltZCPCZP4D11IrjGuEeXip9h7168zXVixTSwmFgCev"
      "IA/fi2nlrsKkl/pGXnDTNiYejcH65PeXi/"
      "PgdxWCWMbQD1Bc1ZWn7HcfSPhDELRWq6tElCyE7cJ2pWde4drSGGF61OOmQGgT2cThBy6lju"
      "2V1NaoTv6LBO1ki+444/0jT09GUhfSoxAPTtYBjNyr54V5JpCW0N1uBwwuB0MMzfSO7V/"
      "XiwdorIREMmj2Xf/"
      "7N1r1zhLxxG6JZ4WwhahSbuArOVVwrKCvx4rI0XNvHS79MD53456gUtKan0NrDD/"
      "2Af2DVZeTEr2S6tzEkcFc421p6p4tlLy3stWk8rOUVsHoGD9ksHQ3EnUl77KE/"
      "t3yIU8ej3CrRntCbn/0fTiR7WkQ4kJa4UFHzrDK5ErbJ6/RlYP/R07NtwUxXF7iSrcg0zx/"
      "porBlmOtSup/"
      "D9DvO2HIzU52vtUnnlbl9QqjW7EZcRNj2AnCCX4pAnUAgeLqy2BmJmiYdReo47AfyvTt7VRu"
      "1Ce2DpMLPtD84NCxSGqzJt2QpcMGihSFpAmPewhe7uJM2hP9Ko00eXNYu7h/"
      "NQKtVf18YuMOdYXQc7UFeehfiLjUQjAK2OrGx76XqeSGDK7B+ZA1D10MuOASpIq4+"
      "qqcFMT6StCZWdRZ3qTDpKFBxsfVydNuxz0gV0wlhhlIjXIIoJ9LdwkSlvhLEgdJaWZcYtqcz"
      "Wsva9M3rJeURLLefxJewgSsBsitppTYYaoxgpRoQvnz6Z6dc3DbUZ5n6R5lFxssSMorV+"
      "T965uYCVoordt3K7lTOM85zeqBITE/"
      "bGLtzFGuMnzaEJnoKFJET0RZjgFyjQkvB+adNI9zA+"
      "uRivslUAX2P38Pvl4OIfnunkkZKdfDyTxY1FR4LiSX0LZ8w.";

  dake_auth_r_p auth_r_msg;
  int result = decode_auth_r_message(auth_r_msg, msg);
  otrng_toolkit_assert(result == 0);

  g_assert_cmpint(auth_r_msg->sender_instance_tag, ==, 480412658);
  g_assert_cmpint(auth_r_msg->receiver_instance_tag, ==, 1764592062);
  g_assert_cmpint(auth_r_msg->profile->expires, ==, 1533767845);
  g_assert_cmpint(auth_r_msg->profile->dsa_key_len, ==, 0);
  otrng_dake_auth_r_destroy(auth_r_msg);
}

void otrng_toolkit_test_parse_auth_i_message() {
  return;
  const char *msg =
      "?OTR:AAQ3aS2Jvhyig/"
      "IFhoIvacC5tLMc9aDQI7YyKZeksJfGXDnn5oPKtRFjXD849oObOtn1aUXQ4xwHiZDQsEDyeC"
      "y2F5fgOHNyb7aJB3r0s5wwhUmKmN7ljOAGwoMs2lnsnMm98AeeQRpG7lW/"
      "PR9kqst4OIFD53QHRO8Ho99iIaLCBCes04o0MfaNwhPJmjmcDbFY/"
      "7bpGyNxlnENXaXW9vPXDGFoWDJta/smyutsrs3myiQfBo84lR1DMj0nex/"
      "IJJOOdS2hCqA+"
      "ANaNwF3sGXQ74PvymOvAamBql8b7oxurROzVhLsKBzxYLngxtSUeAUhu6giZyllljXcDjy3X"
      "cE9ZcoxRHyl4/83E8l1+wXeGhVx44U0npPMI/"
      "q4ptIOM8Z0vCGAxSUtPodJ2abepqYTdsAnSYAssngz+kTuj/"
      "XCXVU2z4Lo8boDQetfrP0LJjk6fJtKh9Mq08z8=.";
  dake_auth_i_p auth_i_msg;
  int result = decode_auth_i_message(auth_i_msg, msg);
  otrng_toolkit_assert(result == 0);

  g_assert_cmpint(auth_i_msg->sender_instance_tag, ==, 1764592062);
  g_assert_cmpint(auth_i_msg->receiver_instance_tag, ==, 480412658);
  otrng_dake_auth_i_destroy(auth_i_msg);
}
