typedef struct {
   int type;
} datamsg;

datamsg parse(const char *msg);

datamsg
parse(const char *msg) {
    //char *otrtag;

    //otrtag = strstr(message, "?OTR");

    //if (!otrtag) {
    //   return OTRL_MSGTYPE_NOTOTR;
    //}

    datamsg parser = { .type = 3 };
    return parser;
}
