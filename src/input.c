#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "terminal.h"
#include "input.h"
#include "init.h"
#include "welcome.h"
#include "algorithms.h"
#include "heap.h"
#include "cell.h"
#include "grid.h"

void dashMoveCursor(int key) {
    switch (key) {
        case ARROW_UP:
            // If on top datarow don't go above it.
            if (Con.state == STATE_WELCOME && Con.cy > Con.headerrow + 1) Con.cy--;

            if (Con.state == STATE_VISUALIZATION && Con.cy != 0) {
                Con.cy--;
            }
            break;
        case ARROW_DOWN:
            // If on bottom datarow don't go below that.
            if (Con.state == STATE_WELCOME && Con.cy < Con.headerrow + algos.algoCount - 1) Con.cy++;

            if (Con.state == STATE_VISUALIZATION && Con.cy != Con.screenrows - 1) { 
                Con.cy++;
            }
            break;
        case ARROW_RIGHT:
            if (Con.state == STATE_WELCOME && Con.cx != algos.tablewidth) {
                Con.cx++;
            }

            if (Con.state == STATE_VISUALIZATION && Con.cx != Con.screencols - 1) {
                Con.cx++;
            }
            break;
        case ARROW_LEFT:
            if (Con.state == STATE_WELCOME && Con.cx != 0) {
                Con.cx--;
            }

            if (Con.state == STATE_VISUALIZATION && Con.cx != 0) {
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
            write(STDOUT_FILENO, "\x1b[0m", 4); // Reset terminal text-styles.
            write(STDOUT_FILENO, "\x1b[?25h", 6); // Give user their cursor back.

            
            
            exit(0);
            break;

        if (Con.state == STATE_RUN) return; // Lower so below c eventaully, want screen clear post-run.

        case 'c':
            freeGrid(g);
            g = initGrid(g, Con.screenrows, Con.screencols);
            g->end_cell = NULL;
            g->start_cell = NULL;

            break;
        
        // Enter is a carriage return in raw mode.
        case ('\r'):
            if (Con.state == STATE_WELCOME) {
                Con.state = STATE_VISUALIZATION;

                // Bit dodge, can't be in the infinite loop.
                Con.cy = 5; // why is this here?
                Con.cx = 37;
                break;
 
            }
            if (Con.state == STATE_VISUALIZATION && g->end_cell != NULL && g->start_cell != NULL) {
                Con.state = STATE_RUN;
                break;

            }
            break;

        case (' '):
            // Place start, end and barrier cells one by one.
            if (Con.state == STATE_VISUALIZATION) handleSpacePress(curr_cell);
            break;

        case 'r':
            // r press removes starts/ends or non-permanent barriers at cursor location.
            if (Con.state == STATE_VISUALIZATION) handleRPress(curr_cell);
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
        curr_cell->ch = '#';
        return;
    }
}

void handleRPress(struct Cell *curr_cell) {
    /* Handles an r press, by updating start and end cells and then barrier cells in that order. */

    if (curr_cell->type == START) {
        curr_cell->type = EMPTY;
        curr_cell->ch = ' ';
        g->start_cell = NULL; // Remove start ptr.
        return;

    } else if (curr_cell->type == END) {
        curr_cell->type = EMPTY;
        curr_cell->ch = ' ';
        g->end_cell = NULL; // Remove end ptr.
        return;

    } else if (curr_cell->type == BARRIER) {
        curr_cell->type = EMPTY;
        curr_cell->ch = ' ';
        return;
    }
}