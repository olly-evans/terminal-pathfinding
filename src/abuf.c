#include <stdlib.h>
#include <string.h>

#include "abuf.h"

void abAppend(struct abuf *ab, char *s, int len) {
    // Get more mem to add len onto the end of &ab.b.
    char *new = realloc(ab->b, ab->len + len);
    if (new == NULL) return;

    // Copy s to the end of buffer.
    memcpy(&new[ab->len], s, len);
    ab->b = new;
    ab->len += len;
}

void abFree(struct abuf *ab) {
    free(ab->b);
}