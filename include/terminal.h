#include <termios.h>

#ifndef TERMINAL_H
#define TERMINAL_H

#define CTRL_KEY(k) ((k) & 0x1f)

typedef struct lrow {
    int size;
    char *chars;
} lrow;

struct Config {
    int screenrows;
    int screencols;
    
    int cx, cy;
    int ex, ey;

    lrow *row;
    int numrows;

    struct termios termiosOrig;
};

extern struct Config Con;

void die(char *s);
void disableRawMode();
void enableRawMode();
int dashReadKey();
int getCursorPosition(int *rows, int *cols);
int getWindowSize(int *rows, int *cols);

#endif