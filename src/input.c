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
    struct Cell *curr_cell = &g->cells[Con.cy][Con.cx];


    switch (c) {
        case (CTRL_KEY('q')):
            write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen.
            write(STDOUT_FILENO, "\x1b[H", 3); // Cursor home.
            write(STDOUT_FILENO, "\x1b[3J", 4); // Clear scrollback buffer.
            exit(0);
            break;
        
        case (' '): 
            

            // If no start cell, init one.
            if (g->start_cell == NULL) {
                g->start_cell = curr_cell;

                g->start_cell->type = START;
                g->start_cell->ch = 'S';
                break;
            } 

            // If no end cell, init one.
            if (g->end_cell == NULL && curr_cell->type != START) {
                g->end_cell = curr_cell;

                g->end_cell->type = END;
                g->end_cell->ch = 'E';
                break;
            }
            
            // Make anything that isn't start/end cell a border thereafter.
            if (curr_cell->type != START && curr_cell->type != END) {
                curr_cell->type = BORDER;
                curr_cell->ch = '#';
                break;
            }
            break;
            
        case 'r':
            
            if (curr_cell->type == START) {
                curr_cell->type = EMPTY;
                curr_cell->ch = ' ';
                g->start_cell = NULL;
                break;
            } else if (curr_cell->type == END) {
                curr_cell->type = EMPTY;
                curr_cell->ch = ' ';
                g->end_cell = NULL;
                break;
            }
            

        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_RIGHT:
        case ARROW_LEFT:
            dashMoveCursor(c);
            break;

    }
}