#ifndef ABUF_H
#define ABUF_H

#define ABUF_INIT {NULL, 0}

struct abuf {
    char *b;
    int len;
};

void abAppend(struct abuf *ab, char *s, int len);
void abFree(struct abuf *ab);
void abAppendCentered(struct abuf *ab, char *s);

#endif