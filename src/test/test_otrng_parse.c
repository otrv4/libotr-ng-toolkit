#include <glib.h>
#include <stdbool.h>
#include <string.h>

#include <libotr-ng/otrng.h>

#include "../parse.c"
#include "test_helpers.h"

void otrng_toolkit_test_parse_data_message() {
  const char *msg =
      "?OTR:"
      "AAQDAAAAAAAAAAAAAAAAAAAAAAHyCwN0UvdtAN1sj2u7eZRt0bJz4OcsY8oWVNUhdjjKJt4v"
      "G3R7X9thzjq2ekbCl7N96H7zwpQ6aAAAAAGAcYUv8x0Gi9Jq2XVfDc0opoRHMVk618tPANF7"
      "c3xTqjVgpvTC8vMtOP9+m8YnaauZWkStx252if+DKIH2rrAwzokYUtoG+whQ7e/"
      "d4TD0F8Reiz7U/iZwvbY25ki5MGi+3oi2PnUZRtR2I5w7ZslCFLq/"
      "Fx++yU7IIKsb7FgMTG53OsuTr6kRDgzuJQnzNkFcHpZKMcugi8IU8nDnI3+"
      "gnLOmoNe2OcpuuutM+"
      "K4OLme2s6yk8D6YZFGAJCqE4tqVEPLoT3aZSDcwrsJZzRrcSlpqiULk9B/"
      "uF5zg1Gs7fsZiBE63tzI53Et79PDRkVWyQTzIpIpf883tzVuJam3yr7TgFFUvuoEhn6hQLb9"
      "03fyV2yaZw1wFhqGztL1WtAi//L282RW/6CPQt4dpctgU8HGWrzo4cNWjTXH/"
      "zZ0H2Ys5KLWvcIyTRPKG9Nh/"
      "jl3nXwPhnY2oY3vSZRB3b80D8t5VkYNFvZmUGnbGsBzT0pUYUa96DiAX3Yt6cf197aN8uNXP"
      "EVh9XtFdHOO7ozYgOOPAAJMLNstBAAAAA54uWlLmsh23Qru0vjwfcfVDL0AJdXyd0GtUQPgT"
      "8gCxA5S7t/CqnJ0ajpmLh0W7s0sxoN2ZwVXBwXrF0a9N0biwLFc=.";

  data_message_s *data_msg = otrng_data_message_new();
  otrng_header_s *header_msg = malloc(sizeof(otrng_header_s));

  g_assert_cmpint(parse(data_msg, header_msg, msg, strlen(msg)), ==, 0);
  g_assert_cmpint(header_msg->type, ==, DATA_MSG_TYPE);
  g_assert_cmpint(header_msg->version, ==, OTRNG_ALLOW_V4);
  g_assert_cmpint(data_msg->sender_instance_tag, ==, 0);
  g_assert_cmpint(data_msg->receiver_instance_tag, ==, 0);
  /*g_assert_cmpstr(data_msg->nonce, ==,*/
  /*"\270\325\317\021X}^\321]\034\343\273\2436 8\343\300");*/
  otrng_assert(true == otrng_ec_point_valid(data_msg->ecdh));
  /*otrng_assert(true == otrng_dh_mpi_valid(data_msg->dh));*/

  /*g_assert_cmpstr(*/
  /*data_msg->mac, ==,*/
  /*"R\346\262\035\267B\273\264\276<\037q\365C/@\tu|\235\320kT@\370\023\362");*/

  otrng_data_message_free(data_msg);
  free(header_msg);
}
