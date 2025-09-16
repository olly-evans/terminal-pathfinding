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
            if (Con.cy != Con.screenrows - 2) {
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

    switch (c) {
        case (CTRL_KEY('q')):
            write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen.
            write(STDOUT_FILENO, "\x1b[H", 3); // Cursor home.
            write(STDOUT_FILENO, "\x1b[3J", 4); // Clear scrollback buffer.
            exit(0);
            break;
        
        case ('e'):
            int row;
            int col;
            getCursorPosition(&row, &col);

            if (Con.ey != -1 && Con.ex != -1) Con.row[Con.ey].chars[Con.ex] = ' '; // Free old position.

            Con.row[row-1].chars[col-1] = 'E';

            Con.ey = row-1;
            Con.ex = col-1;
            break;

        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_RIGHT:
        case ARROW_LEFT:
            dashMoveCursor(c);
            break;

    }
}