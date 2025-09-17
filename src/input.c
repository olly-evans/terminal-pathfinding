#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "terminal.h"
#include "input.h"
#include "output.h"

void dashMoveCursor(int key) {
    switch (key) {
        case ARROW_UP:
            if (Con.cy != 0) {
                Con.cy--;
            }
            break;
        case ARROW_DOWN:
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
        
        case (' '): 
            // answer is use one button, if not start, make start, elif not end. make end.
            // then one button to remove them too.

            int placedE = 0;
            int placedS = 0;

            getCursorPosition(&row, &col);
            // Cursor 1-indexed, must subtract one to align with grid.
            // also want to be able to hold down button and arrow key for drawing hashtags.

            struct Cell *curr_cell = &g->cells[row-1][col-1];
            

            if (g->start_cell == NULL) {
                // make this the start cell!
                g->start_cell = curr_cell;

                g->start_cell->type = START;
                g->start_cell->buf = 'S';
            } else {
                // then make start_cell.buf = ' '.
                // make new start cell.
                g->start_cell->type = EMPTY;
                g->start_cell->buf = ' ';

                curr_cell->type = START;
                curr_cell->buf = 'S';
            }

            // if (end_cell == NULL) {

            //     end_cell = curr_cell;
            //     end_cell->type = END;
            //     end_cell->buf = 'E';
            // } else {
            //     // then make end_cell.buf = ' '.
            //     // make new end cell.
            //     end_cell->type = EMPTY;
            //     end_cell->buf = ' ';

            //     curr_cell->type = START;
            //     curr_cell->buf = 'S';
            // }

            break;
            // make space make a barrier too why not.

            

        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_RIGHT:
        case ARROW_LEFT:
            dashMoveCursor(c);
            break;

    }
}