#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "terminal.h"
#include "input.h"
#include "output.h"

void dashMoveCursor(int key) {
    switch (key) {
        case ARROW_UP:
            if (Con.app_state == STATE_WELCOME && Con.cy == Con.wel_voffset) break;

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
            write(STDOUT_FILENO, "\x1b[0m", 4); // Reset terminal text-styles.

            exit(0);
            break;

        // Enter is a carriage return in raw mode.
        case ('\r'):
            if (Con.app_state == STATE_WELCOME) Con.app_state = STATE_VISUALIZATION, Con.cy = 1, Con.cx = 1;
            break;

        case (' '):
            // Place start, end and barrier cells one by one.
            if (Con.app_state == STATE_VISUALIZATION) handleSpacePress(curr_cell);
            break;

        case 'r':
            // r press removes starts/ends or non-permanent barriers at cursor location.
            if (Con.app_state == STATE_VISUALIZATION) handleRPress(curr_cell);
            break;

        case ARROW_UP:
        case ARROW_DOWN:
            if (Con.app_state == STATE_WELCOME || Con.app_state == STATE_VISUALIZATION) dashMoveCursor(c);
            break;
        case ARROW_RIGHT:
        case ARROW_LEFT:
            if (Con.app_state == STATE_VISUALIZATION) dashMoveCursor(c);
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