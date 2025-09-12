#include <stdlib.h>
#include <unistd.h>

#include "terminal.h"
#include "input.h"

void dashMoveCursor(char key) {
    switch (key) {
        case 'w':
            dashCon.cy--;
            break;
        case 's':
            dashCon.cy++;
            break;
        case 'd':
            dashCon.cx++;
            break;
        case 'a':
            dashCon.cx--;
            break;
    }
}

void dashProcessKeypress() {
    char c = dashReadKey();

    switch (c) {
        case (CTRL_KEY('q')):
            write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen.
            write(STDOUT_FILENO, "\x1b[H", 3); // Cursor home.
            write(STDOUT_FILENO, "\x1b[3J", 4); // Clear scrollback buffer
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