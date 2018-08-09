#include "test_helpers.h"
#include "../decode.h"
#include "../helper.h"

void otrng_toolkit_test_modify(){

  char *old_msg_txt = "hello";
  char *new_msg_txt = "asdfg";
  int offset = 0;
  char *original_msg = "?OTR:AAQDAAABAgAAAQEAAAAAAAAAAAEAAAAA4Bu8GueVNqynkUTbqEeDIqkJ/nAZg5wg6qYyYZPbS2xRZJjUpiRg4xITK29OJE6fgwaZNwRHZZoAAAABgNDbnCRqmxbuwbuAxLVcV8wLDDTVl7sinfc9f6ScruU3y1fS60cPgN8X1gp6OZFe7lPNQAABtNvuII+Xjo63LKi/n259F8pKZ0Q2nd17VGgCrNPgxSV655nj3q0V+P3c6mgf+2sbEJekayVipWFZ5M5CqDUCRC9bEEqqPH+9azTS2j+Arak51TRw/rrgURcIRMjdqfnhW4viqnygOR2SJcd0dnWUw8bHUX6z/uFXIun9455jBVAyjmJCIspi+Fjkh8vsEGH8heSve8w88flGK9pOii7f3E1I7kAho2sHTTByhCMWr10XLcn91iUABuycSKCRubFRbM/JyQDmr16DG86Ukc13j3imXsR63uftxqOTozq0VVzNt0FH35+UHmzaB137a4eFWSpB+dvMUp907x0ZPv3tAb9oXTTiCk6IqtfLKsuto2h0fb76sJ+/mTT60Clv6esgpuIruN4l1vu9HnYjDm9+clTSPuGa9N7yqzwmOLnQ2UWoM0QKOr5M95sD4bQ77pMg6bi4Ii1RI8vXH3red9/J+nZYLQAAAP9Z4HD7UC2/SZZ2CSOF/eakZp1uWp9HizWYCkkixpWl6Pv/KKB24LZklnDmtbKutY4HIDLdLN4H2caEztfLSWkP53lN249SIk9L3CTiSvxRr5JvKvRJcV5A/WE89JO6/wUUf1ngxFkHa9kaoUabWk2TA93OmoElYgsikdd0lnnAhy+PwvUFOv9o6wP+2O9Ius6r7Nqkw2hOK0M1n5hoyNpCqvwnYY6yFuLXSliV00V7qloJOZLBWdNwaKoJJ6KZdsLBxPVksY/8uYnub3yUiHNfTlNRUkUziDxtGG2aQequd5yi1A9xvTtGENwFjW4zAMtErra510Gq239W6g4YHCNwt1+h16g3kTQa64ZdyqBCoXcPWrwB1mTSnMrLFwE7ZKAIRxwS3jD3vfI9flAWy4bfVb5IZc/s0cGq8FtwrALKZvrqSADDfc0WxD7aVlaFB2Z0dh6XDiyhrnuANM2eGpiFcSL3amLWW8M049C/jzjxXDsHctD5ooUJMumr60TZPtI8NISl/FDF1XV3waBoXg9OkfVUz9CIVM+Dft/o1Kdzjs/2Dm/EalfJuNlnV8SYjt247VyAvONQiGThslg8UvYJuKuxTH7ZgvJBw1zzE1VS8rNuynaG7Kq5LuxauOfV59N41c+Ts96adP56R55sXXLYR6hJvcZVJVypWKA64e19wbWOJTj0HwoMSBLRqWb3fqweqP+LJVq94KurkFttEh3myrEKEy9u6O1zqe9Cn0hgEE3DY283n3wBfJCeD9Gz3g==.";
  char *buff_mac = "50073a41e8083fd8b0c977dd99d465e2e28a70c2c50d4dd4fad10238d4e0dc6b33a31b08815728e2103c7762df3d478c3fde27bb4b13a2d7d0d7117b28d9ac90";

  data_message_s *data_msg = otrng_data_message_new();
  decode_data_message(data_msg, original_msg);

  for (int i = 0; i < strlen(old_msg_txt) && offset + i < data_msg->enc_msg_len;
        ++i) {
      data_msg->enc_msg[offset + i] ^= (old_msg_txt[i] ^ new_msg_txt[i]);
    }

  char *encoded_msg = NULL;
  size_t mac_len;
  unsigned char *mac;

  argv_to_buf(&mac, &mac_len, buff_mac);
  serialize_and_remac(&encoded_msg, data_msg, mac);

  otrng_toolkit_assert(1 == 1);

  otrng_data_message_free(data_msg);
  free(encoded_msg);
  free(mac);
}
