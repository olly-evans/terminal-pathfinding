#include <stdlib.h>
#include <string.h>

#include "abuf.h"
#include "terminal.h"

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

void abAppendCentered(struct abuf *ab, char *s) {
    int len = strlen(s);
    if (len > Con.screencols) len = Con.screencols;
    int intro_padding = (Con.screencols - len) / 2;
    
    // move cursor padding to the right...
    while (intro_padding--) abAppend(ab, " ", 1);
    abAppend(ab, s, len);
}