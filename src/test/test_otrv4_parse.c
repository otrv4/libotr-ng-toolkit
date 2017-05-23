#include <glib.h>
#include <string.h>
#include <libotr4/constants.h>
#include "../otr_parse.c"
#include "test_helpers.h"

void
otrv4_toolkit_test_parse_data_message()
{
        const char *msg = "?OTR:AAQDAAAAAAAAAAAAAAAAAAAAAAHyCwN0UvdtAN1sj2u7eZRt0bJz4OcsY8oWVNUhdjjKJt4vG3R7X9thzjq2ekbCl7N96H7zwpQ6aAAAAAGAcYUv8x0Gi9Jq2XVfDc0opoRHMVk618tPANF7c3xTqjVgpvTC8vMtOP9+m8YnaauZWkStx252if+DKIH2rrAwzokYUtoG+whQ7e/d4TD0F8Reiz7U/iZwvbY25ki5MGi+3oi2PnUZRtR2I5w7ZslCFLq/Fx++yU7IIKsb7FgMTG53OsuTr6kRDgzuJQnzNkFcHpZKMcugi8IU8nDnI3+gnLOmoNe2OcpuuutM+K4OLme2s6yk8D6YZFGAJCqE4tqVEPLoT3aZSDcwrsJZzRrcSlpqiULk9B/uF5zg1Gs7fsZiBE63tzI53Et79PDRkVWyQTzIpIpf883tzVuJam3yr7TgFFUvuoEhn6hQLb903fyV2yaZw1wFhqGztL1WtAi//L282RW/6CPQt4dpctgU8HGWrzo4cNWjTXH/zZ0H2Ys5KLWvcIyTRPKG9Nh/jl3nXwPhnY2oY3vSZRB3b80D8t5VkYNFvZmUGnbGsBzT0pUYUa96DiAX3Yt6cf197aN8uNXPEVh9XtFdHOO7ozYgOOPAAJMLNstBAAAAA54uWlLmsh23Qru0vjwfcfVDL0AJdXyd0GtUQPgT8gCxA5S7t/CqnJ0ajpmLh0W7s0sxoN2ZwVXBwXrF0a9N0biwLFc=.,";


	encoded_msg_t *data_msg = NULL;
        data_msg = malloc(sizeof(encoded_msg_t));

	g_assert_cmpint(parse(data_msg, msg, strlen(msg)), ==, 0);
	g_assert_cmpint(data_msg->type, ==, OTR_DATA_MSG_TYPE);
	g_assert_cmpint(data_msg->version, ==, OTRV4_ALLOW_V4);
	g_assert_cmpint(data_msg->sender_instance_tag,  ==, 0);
	g_assert_cmpint(data_msg->receiver_instance_tag, ==, 0);
	g_assert_cmpstr(data_msg->nonce, ==, "\270\325\317\021X}^\321]\034\343\273\2436 8\343\300");
        // XX: FIX ME
	otrv4_assert_point_equals(data_msg->our_ecdh, data_msg->our_ecdh);
	//g_assert_cmpint(data_msg->our_dh, ==, 0);
        g_assert_cmpint(data_msg->ciphertext_len, ==, 3);
	g_assert_cmpint(data_msg->ciphertext[0], ==, 158);
	g_assert_cmpint(data_msg->ciphertext[1], ==, 46);
	g_assert_cmpint(data_msg->ciphertext[2], ==, 90);
	g_assert_cmpstr(data_msg->mac, ==, "R\346\262\035\267B\273\264\276<\037q\365C/@\tu|\235\320kT@\370\023\362");

        free(data_msg->ciphertext);
	free(data_msg);
}

