#include <libotr4/otrv4.h>
#include <libotr4/b64.h>

typedef struct {
   int type;
} encoded_msg_t;

int
parse(encoded_msg_t *dst, const char * src, const int src_len);

// the size
int
parse(encoded_msg_t * dst, const char * src, const int src_len) {
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

    dst->type = header.type;

    return 0;
}
