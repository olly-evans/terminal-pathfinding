#ifndef INIT_H
#define INIT_H

struct Config {
    int screenrows;
    int screencols;
    int headerrow;
    int cx, cy;

    int coloff;
    int rowoff;

    int cellsSearched;

    enum appState state;
    struct termios termiosOrig;
};

extern struct Config Con;

void init();
struct Grid* initGrid(struct Grid *g, int rows, int cols);
void freeGrid(struct Grid *g);

#endif