#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "terminal.h"
#include "input.h"
#include "init.h"
#include "algorithms.h"
#include "heap.h"
#include "cell.h"
#include "grid.h"
#include "menu.h"

void dashMoveCursor(int key) {
    switch (key) {
        case ARROW_UP:

            if (Con.state == VISUALIZATION && Con.cy != 0) {
                Con.cy--;
            }
            break;
        case ARROW_DOWN:

            if (Con.state == VISUALIZATION && Con.cy != Con.screenrows - 1) { 
                Con.cy++;
            }
            break;
        case ARROW_RIGHT:

            if (Con.state == MENU) M.selection = (M.selection + 1) % M.algoCount;

            if (Con.state == VISUALIZATION && Con.cx != Con.screencols - 1) {
                Con.cx++;
            }
            break;
        case ARROW_LEFT:
            if (Con.state == MENU) M.selection = (M.selection - 1 + M.algoCount) % M.algoCount;

            if (Con.state == VISUALIZATION && Con.cx != 0) {
                Con.cx--;
            }
            break;
    }
}

void dashProcessKeypress() {
    int c = dashReadKey();

    struct Cell *curr_cell = &g->cells[Con.cy][Con.cx];
    
    switch (c) {
        case ('q'):
            freeGrid(g);

            write(STDOUT_FILENO, CLEAR_SCRN, 4); // Clear screen.
            write(STDOUT_FILENO, HOME_CURSOR, 3); 
            write(STDOUT_FILENO, "\x1b[3J", 4); // Clear scrollback buffer.
            write(STDOUT_FILENO, RESET_F, 4); 
            write(STDOUT_FILENO, SHOW_CURSOR, 6); 
            exit(0);
            break;
        
        if (Con.state == RUN) break; // Dodge af.

        case 'c':
            freeGrid(g);
            g = initGrid(g, Con.screenrows, Con.screencols);
            g->end_cell = NULL;
            g->start_cell = NULL;

            break;
        
        // Enter is a carriage return in raw mode.
        case ('\r'):
            if (Con.state == MENU) {
                Con.state = VISUALIZATION;

                Con.cy = 5; // why is this here?
                Con.cx = 37;
                break;
 
            }
            if (Con.state == VISUALIZATION && g->end_cell != NULL && g->start_cell != NULL) {
                Con.state = RUN;
                break;

            }
            break;

        case (' '):
            // Place start, end and barrier cells one by one.
            if (Con.state == VISUALIZATION) handleSpacePress(curr_cell);
            break;

        case 'r':
            // r press removes starts/ends or non-permanent barriers at cursor location.
            if (Con.state == VISUALIZATION) handleRPress(curr_cell);
            break;

        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_RIGHT:
        case ARROW_LEFT:
            dashMoveCursor(c);
            break;
    }
}

void handleSpacePress(struct Cell *curr_cell) {
    /* Handles a space press, by updating start, end and then barrier cells in that order. */

    bool isPermBarrier = (curr_cell->type == PERMANENT_BARRIER);

    // If no start cell, init one.
    if ((g->start_cell == NULL) && (!isPermBarrier)) {
        g->start_cell = curr_cell;

        g->start_cell->type = START;
        g->start_cell->ch = 'S';
        return;
    } 

    // If no end cell, init one.
    if ((g->end_cell == NULL) && (curr_cell->type != START) && (!isPermBarrier)) {
        g->end_cell = curr_cell;

        g->end_cell->type = END;
        g->end_cell->ch = 'E';
        return;
    }
    
    // Make anything that isn't start/end cell a border thereafter.
    if (curr_cell->type != START && curr_cell->type != END && (!isPermBarrier)) {
        curr_cell->type = BARRIER;
        curr_cell->ch = ' ';
        return;
    }
}

void handleRPress(struct Cell *curr_cell) {
    /* Handles an r press, by updating start and end cells, and then barrier cells in that order. */

    if (curr_cell->type == START) {
        curr_cell->type = EMPTY;
        curr_cell->ch = ' ';
        g->start_cell = NULL;
        return;

    } else if (curr_cell->type == END) {
        curr_cell->type = EMPTY;
        curr_cell->ch = ' ';
        g->end_cell = NULL; 
        return;

    } else if (curr_cell->type == BARRIER) {
        curr_cell->type = EMPTY;
        curr_cell->ch = ' ';
        return;
    }
}