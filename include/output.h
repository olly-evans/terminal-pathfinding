#ifndef OUTPUT_H
#define OUTPUT_H
#include "abuf.h"

void dashRefreshScreen();
void dashDrawRows();
void dashAppendRow(char *s, size_t len);
void drawRows(struct abuf *ab);

#endif