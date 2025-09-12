#include <stdlib.h>
#include <unistd.h>

#include "terminal.h"
#include "input.h"

void dashMoveCursor(char key) {
    switch (key) {
        case 'w':
            if (dashCon.cy != 0) {
                dashCon.cy--;
            }
            break;
        case 's':
            if (dashCon.cy != dashCon.dashrows - 1) {
                dashCon.cy++;
            }
            break;
        case 'd':
            if (dashCon.cx != dashCon.dashcols - 1) {
                dashCon.cx++;
            }
            break;
        case 'a':
            if (dashCon.cx != 0) {
                dashCon.cx--;
            }
            break;
    }
}

void dashProcessKeypress() {
    char c = dashReadKey();

    switch (c) {
        case (CTRL_KEY('q')):
            write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen.
            write(STDOUT_FILENO, "\x1b[H", 3); // Cursor home.
            write(STDOUT_FILENO, "\x1b[3J", 4); // Clear Scrollback buffer
            exit(0);
            break;

        case 'w':
        case 's':
        case 'd':
        case 'a':
            dashMoveCursor(c);
            break;

    }
}