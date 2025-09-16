#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "terminal.h"
#include "input.h"

void dashMoveCursor(int key) {
    switch (key) {
        case ARROW_UP:
            if (Con.cy != 0) {
                Con.cy--;
            }
            break;
        case ARROW_DOWN:
            // -2 to account for bar at bottom. Not done yet.
            if (Con.cy != Con.screenrows - 1) { 
                Con.cy++;
            }
            break;
        case ARROW_RIGHT:
            if (Con.cx != Con.screencols - 1) {
                Con.cx++;
            }
            break;
        case ARROW_LEFT:
            if (Con.cx != 0) {
                Con.cx--;
            }
            break;
    }
}

void dashProcessKeypress() {
    int c = dashReadKey();
    int row;
    int col;
    
    switch (c) {
        case (CTRL_KEY('q')):
            write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen.
            write(STDOUT_FILENO, "\x1b[H", 3); // Cursor home.
            write(STDOUT_FILENO, "\x1b[3J", 4); // Clear scrollback buffer.
            exit(0);
            break;
        
        case ('e'):
            getCursorPosition(&row, &col);

        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_RIGHT:
        case ARROW_LEFT:
            dashMoveCursor(c);
            break;

    }
}