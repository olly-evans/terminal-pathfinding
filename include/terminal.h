#include <termios.h>

#ifndef TERMINAL_H
#define TERMINAL_H

#define CTRL_KEY(k) ((k) & 0x1f)


struct dashConfig {
    int dashrows;
    int dashcols;
    int cx, cy;
    struct termios termiosOrig;
};

extern struct dashConfig dashCon;

void die(char *s);
void disableRawMode();
void enableRawMode();
char dashReadKey();
int getCursorPosition(int *rows, int *cols);
int getWindowSize(int *rows, int *cols);

#endif