#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *data;
  size_t len;
  size_t malloc_len;
} Buffer;

static void buf_new(Buffer *bufp) {
  bufp->data = NULL;
  bufp->len = 0;
  bufp->malloc_len = 0;
}

static void buf_put(Buffer *bufp, const char *str, size_t len) {
  while (bufp->len + len + 1 > bufp->malloc_len) {
    char *newdata = realloc(bufp->data, bufp->malloc_len +
                                            1024); // TODO: why this constant?
    if (!newdata) {
      fprintf(stderr, "Out of memory!\n");
      exit(1);
    }
    bufp->data = newdata;
    bufp->malloc_len += 1024;
  }
  memmove(bufp->data + bufp->len, str, len);
  bufp->len += len;
  bufp->data[bufp->len] = '\0';
}

static void buf_putc(Buffer *bufp, char c) { buf_put(bufp, &c, 1); }

/* Read from the given stream until we see a complete OTRv4 DAKE
 * or a OTRv4 Data message.  Return a newly-allocated pointer to a copy of
 * this message, which the caller should free().  Returns NULL if no
 * such message could be found. */
// TODO: change name
// TODO: somewhere this is freeing what is not supposed. See stacktrace
char *readotr(FILE *stream) {
  int seen = 0;
  const char header[] = "?OTR";

  int headerlen = strlen(header);
  Buffer buf;

  while (seen < headerlen) {
    int c = fgetc(stream);
    if (c == EOF) {
      return NULL;
    } else if (c == header[seen]) {
      seen++;
    } else if (c == header[0]) {
      seen = 1;
    } else {
      seen = 0;
    }
  }

  buf_new(&buf);
  buf_put(&buf, header, headerlen);

  /* Look for the trailing '.' */
  while (1) {
    // TODO: change name as this can shadow
    int c = fgetc(stream);
    if (c == EOF) {
      break;
    }
    buf_putc(&buf, c);
    if (c == '.') {
      break;
    }
  }

  return buf.data;
}
