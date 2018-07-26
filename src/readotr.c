#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *data;
  size_t len;
  size_t alloclen;
} Buffer;

static void buf_new(Buffer *bufp) {
  bufp->data = NULL;
  bufp->len = 0;
  bufp->alloclen = 0;
}

static void buf_put(Buffer *bufp, const char *str, size_t len) {
  while (bufp->len + len + 1 > bufp->alloclen) {
    char *newdata = realloc(bufp->data, bufp->alloclen + 1024);
    if (!newdata) {
      fprintf(stderr, "Out of memory!\n");
      exit(1);
    }
    bufp->data = newdata;
    bufp->alloclen += 1024;
  }
  memmove(bufp->data + bufp->len, str, len);
  bufp->len += len;
  bufp->data[bufp->len] = '\0';
}

static void buf_putc(Buffer *bufp, char c) { buf_put(bufp, &c, 1); }

char *readotr(FILE *stream) {
  int seen = 0;
  const char header[] = "?OTR";
  int headerlen = strlen(header);
  Buffer buf;

  int is_plaintext = 0;
  buf_new(&buf);

  while (seen < headerlen) {
    int c = fgetc(stream);
    if (c == EOF)
      return NULL;
    else if (c == header[seen])
      seen++;
    else if (c == header[0])
      seen = 1;
    else {
      buf_putc(&buf, c);
      is_plaintext = 1;
      break;
    }
  }

  if (!is_plaintext)
    buf_put(&buf, header, headerlen);

  /* Look for the trailing '.' */
  while (1) {
    int c = fgetc(stream);
    if (c == EOF)
      break;
    buf_putc(&buf, c);
    if (c == '.')
      break;
  }

  return buf.data;
}
