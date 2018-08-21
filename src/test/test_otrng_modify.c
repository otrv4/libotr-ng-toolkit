#include "../parse.h"
#include "../helper.h"
#include "../readforge.h"
#include "test_helpers.h"

void otrng_toolkit_test_modify() {
  return;
  //  char *old_msg_txt = "hello";
  //  char *new_msg_txt = "asdfg";
  //  int offset = 0;
  //  char *original_msg =
  //      "?OTR:"
  //      "AAQDAAABAgAAAQEAAAAAAAAAAAIAAAACh6nreccn9NeZxqtS2FZTDt3yWlvQS8EVPyQnJMtg"
  //      "do7jufww87CBNqkLQOU9KpBMorOIVpCuiFmAAAABgHF8Lp9+OG5XvhLwJ/"
  //      "s00ameYt+ZkZuVe+hIuhusVXTkACAa38r7JJzSiFXIPx35vrXcY+"
  //      "F076ysFmnH08mkwuMygtm2Kh0LOqbunpNPHE361PDSP6M1Y0bhYM2r/"
  //      "ZSXJ4+"
  //      "td8lk2wS0gnB69ZZuNtJ6Q1F071XfkTYZN1Z3oh2VvH6PlejWN2JGF1k8qVvAyC3vuXNos62"
  //      "edrNZVev8VG2vNovztr28cY24405o8K32MhaBMhfkk1VjYDKrcZ9yC6tpOV9gciqEPK5fHuz"
  //      "rt0MJGFKLSFr6o2nH79sWOjfQXAt7mzIpfO+dYN+"
  //      "mV5m0x71ViP6Q56OXure0joAncMnItnEm0Nh2od1vnEgaYKwAXejg+"
  //      "h3xAktExgqTfQEyCMpCWS4VgzOKrTkubu5m/IuQ8D7i/"
  //      "Ai1Jw9eojQO4p6xivCS0jN3TIk3WWsdJuEd0PlUEK1sNFTACpaGFuQ98MFUvWvQTlqAIjT7t"
  //      "hBQRYzHX4+aHvLwFrJ3fL4PkW+wzI4ZD4klZfk7ZyPA1ZsSmPUCJVJdfPKnVgAAAP+"
  //      "WOTHGcGBujO1wpT0eraa2+7tBQU+AguQXsbqOn3kOQvvR35T+"
  //      "DL2Ie7u7X8dnWytIOVWytJzFDeD0jER5tX63+"
  //      "WnIkQ51Q7vMQNqEsAH8pOXM0iZYoP15hwmj4ply2yFl5VC+"
  //      "kMTZZJfkZ6A2iMFA87tHVJLngu3TSI+OLeav66WzT82edQvs5cMcVSW5+i+"
  //      "NMBYfJP4ec1IFih9wdV7LeWRQoz882w4iTGFfoNEZgMnXRTYd2fQcjyus654fzMLntWepUqJ"
  //      "7zIKpxOBPF0f1r3sG3eu/"
  //      "0x2Bs2XoX6qNNPdONeGdAIqxR8DIucWjCbNf3lEUYELKxpKUMZddNoHu5mYKkMoVc5/"
  //      "h6sxxG0FuLYKH4ghSCTy+3KIzcQKs25x6gBRE4PKL/"
  //      "uCzAK3H59DPi4PSWy2JEAfSaYCZ8ofg.";
  //  char *buff_mac =
  //      "534b1b4e089a0ec41662979371a16c2add523e10b549f7bda9c20dfd5032473f";
  //  char *raw_enc_key =
  //      "f40ea18fc41cabbf982c41b42bf37d2a171f21070a68248b5157003a2f99df49";
  //  data_message_s *data_msg = otrng_data_message_new();
  //
  //  modify_message(data_msg, original_msg, old_msg_txt, new_msg_txt, offset);
  //
  //  char *encoded_msg = NULL;
  //  size_t mac_len;
  //  unsigned char *mac;
  //
  //  argv_to_buf(&mac, &mac_len, buff_mac);
  //  serialize_and_remac(&encoded_msg, data_msg, mac);
  //
  //  data_message_s *new_data_msg = otrng_data_message_new();
  //  decode_data_message(new_data_msg, encoded_msg);
  //
  //  // The following lines are here just to make an effetive test
  //  char *modified_txt = NULL;
  //  msg_enc_key_p enc_key;
  //
  //  read(&modified_txt, enc_key, raw_enc_key, encoded_msg, new_data_msg);
  //
  //  otrng_toolkit_assert_cmpmem(modified_txt, new_msg_txt,
  //  strlen(modified_txt));
  //
  //  otrng_data_message_free(data_msg);
  //
  //  otrng_data_message_free(new_data_msg);
  //  free(modified_txt);
}
