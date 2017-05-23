#include <stdio.h>
#include <string.h>

#include <libotr4/otrv4.h>
#include <libotr4/b64.h>
#include <libotr4/constants.h>
#include <libotr4/data_message.h>

typedef struct {
   int type;
   int version;
   int sender_instance_tag;
   int receiver_instance_tag;
   char nonce[DATA_MSG_NONCE_BYTES];
   ec_point_t our_ecdh;
   dh_public_key_t our_dh;
   uint8_t * ciphertext;
   int ciphertext_len;
   char mac[DATA_MSG_MAC_BYTES];
} encoded_msg_t;

int
parse(encoded_msg_t *dst, const char * src, const int src_len);

int
parse(encoded_msg_t * dst, const char * src, const int src_len) {
    if (NULL == src) {
        return 1;
    }

    if (src_len > strlen(src)) {
        return 1;
    }

    int otr_type = (int) get_message_type(src);
    if (otr_type != IN_MSG_OTR_ENCODED) {
        return 1;
    }

    size_t dec_len = 0;
    uint8_t *decoded = NULL;
    int err = otrl_base64_otr_decode(src, &decoded, &dec_len);
    if (err)
       return 1;


    otrv4_header_t header;
    if (!extract_header(&header, decoded, dec_len)) {
        free(decoded);
	return 1;
    }

    if (header.type != OTR_DATA_MSG_TYPE) {
        return 1;
    }

    dst->type = header.type;
    dst->version = header.version;

    data_message_t * data = NULL;
    data = malloc(sizeof(data_message_t));
    if (!data) {
	return 1;
    }

    if (!data_message_deserialize(data, decoded, dec_len)) {
       free(data);
       free(decoded);
       return 1;
    }

    dst->sender_instance_tag = data->sender_instance_tag;
    dst->receiver_instance_tag = data->receiver_instance_tag;
    memcpy(dst->nonce, data->nonce, DATA_MSG_NONCE_BYTES);
    dst->our_ecdh[0] = data->our_ecdh[0];
    dst->our_dh = data->our_dh;
    // CHECK
    dst->ciphertext = malloc(data->enc_msg_len);
    if (!dst->ciphertext) {
	return 1;
    }

    // XXX: check where old mackeys are deser
    memcpy(dst->ciphertext, data->enc_msg, data->enc_msg_len);
    dst->ciphertext_len = data->enc_msg_len;

    //for (unsigned int i = 0; i<data->enc_msg_len; i++) {
    //printf("%x \n", data->enc_msg[i]);
    //}
    //printf("%lu \n", data->enc_msg_len);

    //printf("sec%x \n", *dst->ciphertext);
    //printf("sec%d \n", dst->ciphertext_len);

    memcpy(dst->mac, data->mac, DATA_MSG_MAC_BYTES);

    free(decoded);
    free(data);

//typedef struct {
//	uint8_t flags;
//	uint32_t ratchet_id;
//	uint32_t message_id;
//} data_message_t;
    return 0;
}
