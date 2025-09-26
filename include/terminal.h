#include <termios.h>

#ifndef TERMINAL_H
#define TERMINAL_H

#define CTRL_KEY(k) ((k) & 0x1f)

enum appState {
	STATE_WELCOME,
	STATE_VISUALIZATION,
    STATE_RUN
};

struct Config {
    int screenrows;
    int screencols;
    int headerrow;
    int cx, cy;

    int coloff;
    int rowoff;

    enum appState state;
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