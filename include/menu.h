#ifndef MENU_H
#define MENU_H

typedef struct Menu {
    char **algorithms;
    int algoCount;
    int algoIdx;
} Menu;

extern struct Menu M;

void drawMenu();
void drawMenuItems(struct abuf *ab);

#endif