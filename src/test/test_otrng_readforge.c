#include "../helper.c"
#include "../readforge.c"
#include "test_helpers.h"

void otrng_toolkit_test_read_and_forge_ratchet_key() {
  char *ratchet_key =
      "e67646f68b88c76f247ad0725759274399d512870ac8b44def5e3d30d66e357e69d87ea7"
      "0564e190511d89454d65ef5c2bef69170de01ec9cd97087af592754b";
  char *msg =
      "?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAEAAAAA4Bu8GueVNqynkUTbqEeDIqkJ/"
      "nAZg5wg6qYyYZPbS2xRZJjUpiRg4xITK29OJE6fgwaZNwRHZZoAAAABgNDbnCRqmxbuwbuAx"
      "LVcV8wLDDTVl7sinfc9f6ScruU3y1fS60cPgN8X1gp6OZFe7lPNQAABtNvuII+Xjo63LKi/"
      "n259F8pKZ0Q2nd17VGgCrNPgxSV655nj3q0V+P3c6mgf+"
      "2sbEJekayVipWFZ5M5CqDUCRC9bEEqqPH+9azTS2j+Arak51TRw/"
      "rrgURcIRMjdqfnhW4viqnygOR2SJcd0dnWUw8bHUX6z/"
      "uFXIun9455jBVAyjmJCIspi+"
      "Fjkh8vsEGH8heSve8w88flGK9pOii7f3E1I7kAho2sHTTByhCMWr10XLcn91iUABuycSKCRu"
      "bFRbM/"
      "JyQDmr16DG86Ukc13j3imXsR63uftxqOTozq0VVzNt0FH35+UHmzaB137a4eFWSpB+"
      "dvMUp907x0ZPv3tAb9oXTTiCk6IqtfLKsuto2h0fb76sJ+/"
      "mTT60Clv6esgpuIruN4l1vu9HnYjDm9+"
      "clTSPuGa9N7yqzwmOLnQ2UWoM0QKOr5M95sD4bQ77pMg6bi4Ii1RI8vXH3red9/"
      "J+nZYLQAAAAhV8HH6Ri38BeXAcEVLQdWb5AGLlvync+NYz/"
      "EwX0xqsg+nwkVcmoOn9zImEQKA9PEtYv+I0WbqCVbQk1ZMnGFIYYf/lcfqNOg=.";

  char *encoded_data_msg = NULL;
  char *plain_text = NULL;

  readforge(&plain_text, &encoded_data_msg, ratchet_key, msg, NULL);
  otrng_toolkit_assert_cmpmem(plain_text, "dummy", strlen(plain_text));
  otrng_toolkit_assert(encoded_data_msg == NULL);
  free(plain_text);
  free(encoded_data_msg);
}

void otrng_toolkit_test_read_and_forge_ratchet_key_new_msg() {
  char *ratchet_key =
      "e67646f68b88c76f247ad0725759274399d512870ac8b44def5e3d30d66e357e69d87ea7"
      "0564e190511d89454d65ef5c2bef69170de01ec9cd97087af592754b";
  char *msg =
      "?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAEAAAAA4Bu8GueVNqynkUTbqEeDIqkJ/"
      "nAZg5wg6qYyYZPbS2xRZJjUpiRg4xITK29OJE6fgwaZNwRHZZoAAAABgNDbnCRqmxbuwbuAx"
      "LVcV8wLDDTVl7sinfc9f6ScruU3y1fS60cPgN8X1gp6OZFe7lPNQAABtNvuII+Xjo63LKi/"
      "n259F8pKZ0Q2nd17VGgCrNPgxSV655nj3q0V+P3c6mgf+"
      "2sbEJekayVipWFZ5M5CqDUCRC9bEEqqPH+9azTS2j+Arak51TRw/"
      "rrgURcIRMjdqfnhW4viqnygOR2SJcd0dnWUw8bHUX6z/"
      "uFXIun9455jBVAyjmJCIspi+"
      "Fjkh8vsEGH8heSve8w88flGK9pOii7f3E1I7kAho2sHTTByhCMWr10XLcn91iUABuycSKCRu"
      "bFRbM/"
      "JyQDmr16DG86Ukc13j3imXsR63uftxqOTozq0VVzNt0FH35+UHmzaB137a4eFWSpB+"
      "dvMUp907x0ZPv3tAb9oXTTiCk6IqtfLKsuto2h0fb76sJ+/"
      "mTT60Clv6esgpuIruN4l1vu9HnYjDm9+"
      "clTSPuGa9N7yqzwmOLnQ2UWoM0QKOr5M95sD4bQ77pMg6bi4Ii1RI8vXH3red9/"
      "J+nZYLQAAAAhV8HH6Ri38BeXAcEVLQdWb5AGLlvync+NYz/"
      "EwX0xqsg+nwkVcmoOn9zImEQKA9PEtYv+I0WbqCVbQk1ZMnGFIYYf/lcfqNOg=.";
  /*char *expected_new_data_msg =*/
  /*"?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAEAAAAA4Bu8GueVNqynkUTbqEeDIqkJ/"*/
  /*"nAZg5wg6qYyYZPbS2xRZJjUpiRg4xITK29OJE6fgwaZNwRHZZoAAAABgNDbnCRqmxbuwbuAx"*/
  /*"LVcV8wLDDTVl7sinfc9f6ScruU3y1fS60cPgN8X1gp6OZFe7lPNQAABtNvuII+Xjo63LKi/"*/
  /*"n259F8pKZ0Q2nd17VGgCrNPgxSV655nj3q0V+P3c6mgf+"*/
  /*"2sbEJekayVipWFZ5M5CqDUCRC9bEEqqPH+9azTS2j+Arak51TRw/"*/
  /*"rrgURcIRMjdqfnhW4viqnygOR2SJcd0dnWUw8bHUX6z/"*/
  /*"uFXIun9455jBVAyjmJCIspi+"*/
  /*"Fjkh8vsEGH8heSve8w88flGK9pOii7f3E1I7kAho2sHTTByhCMWr10XLcn91iUABuycSKCRu"*/
  /*"bFRbM/"*/
  /*"JyQDmr16DG86Ukc13j3imXsR63uftxqOTozq0VVzNt0FH35+UHmzaB137a4eFWSpB+"*/
  /*"dvMUp907x0ZPv3tAb9oXTTiCk6IqtfLKsuto2h0fb76sJ+/"*/
  /*"mTT60Clv6esgpuIruN4l1vu9HnYjDm9+"*/
  /*"clTSPuGa9N7yqzwmOLnQ2UWoM0QKOr5M95sD4bQ77pMg6bi4Ii1RI8vXH3red9/"*/
  /*"J+nZYLQAAAAhU6GzjRi2OZ2L4gwM6kmAo6TJKhjsjf5/"*/
  /*"9KzGTCQTKt7UFXQQTkZE13sbHAUaCZlVzpBJttRyzlsF+qzkq2oKAmfxGa9sbQVA=.";*/
  char *encoded_data_msg = NULL;
  char *new_msg = "empty";
  char *plain_text;
  g_assert_cmpint(
      readforge(&plain_text, &encoded_data_msg, ratchet_key, msg, new_msg), ==,
      0);
  otrng_toolkit_assert_cmpmem(plain_text, "dummy", strlen(plain_text));
  /*g_assert_cmpstr(encoded_data_msg, ==, expected_new_data_msg);*/
  free(plain_text);
  free(encoded_data_msg);
}

void otrng_toolkit_test_read_and_forge_encryption_key() {
  char *encryption_key =
      "b1a3c6d10325881d4e4b5ea4461905c5d91058fde48158b85cfecfb23fbb5156";
  char *msg =
      "?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAEAAAAA4Bu8GueVNqynkUTbqEeDIqkJ/"
      "nAZg5wg6qYyYZPbS2xRZJjUpiRg4xITK29OJE6fgwaZNwRHZZoAAAABgNDbnCRqmxbuwbuAx"
      "LVcV8wLDDTVl7sinfc9f6ScruU3y1fS60cPgN8X1gp6OZFe7lPNQAABtNvuII+Xjo63LKi/"
      "n259F8pKZ0Q2nd17VGgCrNPgxSV655nj3q0V+P3c6mgf+"
      "2sbEJekayVipWFZ5M5CqDUCRC9bEEqqPH+9azTS2j+Arak51TRw/"
      "rrgURcIRMjdqfnhW4viqnygOR2SJcd0dnWUw8bHUX6z/"
      "uFXIun9455jBVAyjmJCIspi+"
      "Fjkh8vsEGH8heSve8w88flGK9pOii7f3E1I7kAho2sHTTByhCMWr10XLcn91iUABuycSKCRu"
      "bFRbM/"
      "JyQDmr16DG86Ukc13j3imXsR63uftxqOTozq0VVzNt0FH35+UHmzaB137a4eFWSpB+"
      "dvMUp907x0ZPv3tAb9oXTTiCk6IqtfLKsuto2h0fb76sJ+/"
      "mTT60Clv6esgpuIruN4l1vu9HnYjDm9+"
      "clTSPuGa9N7yqzwmOLnQ2UWoM0QKOr5M95sD4bQ77pMg6bi4Ii1RI8vXH3red9/"
      "J+nZYLQAAAAhV8HH6Ri38BeXAcEVLQdWb5AGLlvync+NYz/"
      "EwX0xqsg+nwkVcmoOn9zImEQKA9PEtYv+I0WbqCVbQk1ZMnGFIYYf/lcfqNOg=.";
  char *encoded_data_msg = NULL;
  char *plain_text;
  readforge(&plain_text, &encoded_data_msg, encryption_key, msg, NULL);
  otrng_toolkit_assert_cmpmem(plain_text, "dummy", strlen(plain_text));
  otrng_toolkit_assert(encoded_data_msg == NULL);
  free(plain_text);
  free(encoded_data_msg);
}

void otrng_toolkit_test_read_and_forge_encryption_key_new_msg() {
  char *encryption_key =
      "b1a3c6d10325881d4e4b5ea4461905c5d91058fde48158b85cfecfb23fbb5156";
  char *msg =
      "?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAEAAAAA4Bu8GueVNqynkUTbqEeDIqkJ/"
      "nAZg5wg6qYyYZPbS2xRZJjUpiRg4xITK29OJE6fgwaZNwRHZZoAAAABgNDbnCRqmxbuwbuAx"
      "LVcV8wLDDTVl7sinfc9f6ScruU3y1fS60cPgN8X1gp6OZFe7lPNQAABtNvuII+Xjo63LKi/"
      "n259F8pKZ0Q2nd17VGgCrNPgxSV655nj3q0V+P3c6mgf+"
      "2sbEJekayVipWFZ5M5CqDUCRC9bEEqqPH+9azTS2j+Arak51TRw/"
      "rrgURcIRMjdqfnhW4viqnygOR2SJcd0dnWUw8bHUX6z/"
      "uFXIun9455jBVAyjmJCIspi+"
      "Fjkh8vsEGH8heSve8w88flGK9pOii7f3E1I7kAho2sHTTByhCMWr10XLcn91iUABuycSKCRu"
      "bFRbM/"
      "JyQDmr16DG86Ukc13j3imXsR63uftxqOTozq0VVzNt0FH35+UHmzaB137a4eFWSpB+"
      "dvMUp907x0ZPv3tAb9oXTTiCk6IqtfLKsuto2h0fb76sJ+/"
      "mTT60Clv6esgpuIruN4l1vu9HnYjDm9+"
      "clTSPuGa9N7yqzwmOLnQ2UWoM0QKOr5M95sD4bQ77pMg6bi4Ii1RI8vXH3red9/"
      "J+nZYLQAAAAhV8HH6Ri38BeXAcEVLQdWb5AGLlvync+NYz/"
      "EwX0xqsg+nwkVcmoOn9zImEQKA9PEtYv+I0WbqCVbQk1ZMnGFIYYf/lcfqNOg=.";
  /*char *expected_new_data_msg =*/
  /*"?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAEAAAAA4Bu8GueVNqynkUTbqEeDIqkJ/"*/
  /*"nAZg5wg6qYyYZPbS2xRZJjUpiRg4xITK29OJE6fgwaZNwRHZZoAAAABgNDbnCRqmxbuwbuAx"*/
  /*"LVcV8wLDDTVl7sinfc9f6ScruU3y1fS60cPgN8X1gp6OZFe7lPNQAABtNvuII+Xjo63LKi/"*/
  /*"n259F8pKZ0Q2nd17VGgCrNPgxSV655nj3q0V+P3c6mgf+"*/
  /*"2sbEJekayVipWFZ5M5CqDUCRC9bEEqqPH+9azTS2j+Arak51TRw/"*/
  /*"rrgURcIRMjdqfnhW4viqnygOR2SJcd0dnWUw8bHUX6z/"*/
  /*"uFXIun9455jBVAyjmJCIspi+"*/
  /*"Fjkh8vsEGH8heSve8w88flGK9pOii7f3E1I7kAho2sHTTByhCMWr10XLcn91iUABuycSKCRu"*/
  /*"bFRbM/"*/
  /*"JyQDmr16DG86Ukc13j3imXsR63uftxqOTozq0VVzNt0FH35+UHmzaB137a4eFWSpB+"*/
  /*"dvMUp907x0ZPv3tAb9oXTTiCk6IqtfLKsuto2h0fb76sJ+/"*/
  /*"mTT60Clv6esgpuIruN4l1vu9HnYjDm9+"*/
  /*"clTSPuGa9N7yqzwmOLnQ2UWoM0QKOr5M95sD4bQ77pMg6bi4Ii1RI8vXH3red9/"*/
  /*"J+nZYLQAAAAhU6GzjRi2OZ2L4gwM6kmAo6TJKhjsjf5/"*/
  /*"9KzGTCQTKt7UFXQQTkZE13sbHAUaCZlVzpBJttRyzlsF+qzkq2oKAmfxGa9sbQVA=.";*/
  char *encoded_data_msg = NULL;
  char *plain_text;
  char *new_msg = "empty";
  readforge(&plain_text, &encoded_data_msg, encryption_key, msg, new_msg);
  otrng_toolkit_assert_cmpmem(plain_text, "dummy", strlen(plain_text));
  /*g_assert_cmpstr(encoded_data_msg, ==, expected_new_data_msg);*/
  free(plain_text);
  free(encoded_data_msg);
}
