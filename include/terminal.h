#include <termios.h>

#ifndef TERMINAL_H
#define TERMINAL_H

#define CTRL_KEY(k) ((k) & 0x1f)

#define TXT_RED "\x1b[31m"
#define TXT_GREEN "\x1b[32m"
#define TXT_BLUE "\x1b[36m"

#define BG_BLACK "\x1b[40m"
#define BG_PINK "\x1b[45m"
#define BG_BLUE "\x1b[46m"
#define BG_WHITE "\x1b[47m"

#define CLEAR_SCRN "\x1b[2J"
#define CLEAR_SCROLLBACK_BUF "\x1b[3J"

#define HOME_CURSOR "\x1b[H"
#define HIDE_CURSOR "\x1b[?25l"
#define SHOW_CURSOR "\x1b[?25h"
#define RESET_F "\x1b[0m"

#define DISABLE_TERMINAL_AUTOWRAP  "\x1b[?7l"



// Move this.
enum appState {
	MENU,
	VISUALIZATION,
    RUN
};

/* LINUX TERMINAL DEPENDANT */

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