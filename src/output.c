#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "output.h"
#include "terminal.h"
#include "abuf.h"
#include "input.h"
#include "algorithms.h"

void drawWelcomeScreen() {

    Con.app_state = STATE_WELCOME;
    checkScroll();

    // Define abuf for this welcome menu.
    struct abuf wel_ab = ABUF_INIT;

    abAppend(&wel_ab, "\x1b[?25l", 6);
    abAppend(&wel_ab, "\x1b[2J", 4);
    abAppend(&wel_ab, "\x1b[3J", 4);
    abAppend(&wel_ab, "\x1b[H", 3);

    drawWelcomeRows(&wel_ab);

    char mcursor[32];
    snprintf(mcursor, sizeof(mcursor), "\x1b[%d;%dH", Con.cy + 1, (Con.cx - Con.coloff)+ 1); // adding offset could be close
    abAppend(&wel_ab, mcursor, strlen(mcursor));


    write(STDOUT_FILENO, wel_ab.b, wel_ab.len);

    // if algo chosen in cursor row, proceed.
    abFree(&wel_ab);
}

void drawPathfindingVisualizer() {
    Con.app_state = STATE_VISUALIZATION;

    // Perhaps make this refresh grid function instead then have seperate function for drawing welcome menu.
    struct abuf vis_ab = ABUF_INIT; // hmmm could prob be in the init section.

    abAppend(&vis_ab, "\x1b[?25l", 6);
    abAppend(&vis_ab, "\x1b[H", 4);
    abAppend(&vis_ab, "\x1b[2J", 4);
    abAppend(&vis_ab, "\x1b[3J", 4);

    drawGrid(&vis_ab);

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", Con.cy + 1, Con.cx + 1);
    abAppend(&vis_ab, buf, strlen(buf)); 


    abAppend(&vis_ab, "\x1b[?25h", 6);
    
    write(STDOUT_FILENO, vis_ab.b, vis_ab.len);

    abFree(&vis_ab);
}

void drawGrid(struct abuf *ab) {
    
    /* Loop through the Cells in the row pointers and append their color and char to abuf. */
    
    int y;
    int x;
    for (y = 0; y < g->rows; y++) {
        for (x = 0; x < g->cols; x++) {

            // Current Cell
            struct Cell *c = &g->cells[y][x];

            switch (c->type) {
                case START:
                abAppend(ab, "\x1b[32m", 5); // Green
                abAppend(ab, &c->ch, 1);
                break;

            case END:
                abAppend(ab, "\x1b[31m", 5); // Red
                abAppend(ab, &c->ch, 1);
                break;

            case BARRIER:
            case PERMANENT_BARRIER:
                abAppend(ab, "\x1b[37m", 5); // White
                abAppend(ab, &c->ch, 1);
                
                break;

            default:
                abAppend(ab, &c->ch, 1);  // No color
                break;
            }
        }
        if (y < g->rows - 1) abAppend(ab, "\r\n", 2);
    }
}

void drawWelcomeRows(struct abuf *ab) {

    for (int y = 0; y < Con.screenrows; y++) {

        if (isHeaderRow(y)) {
            abAppend(ab, "\x1b[46m", 5);

            padAppendData(ab, y - Con.headerrow);

            abAppend(ab, "\x1b[0m", 4);
        }
        
        if (isCursorRow(y)) {
            abAppend(ab, "\x1b[7m\x1b[K", 7); // not extending to end of row.
            padAppendData(ab, y - Con.headerrow);

            abAppend(ab, "\x1b[0m", 4); // Reset background.
        } else if (isDataRow(y)) {
            padAppendData(ab, y - Con.headerrow);
        }
        if (y != Con.screenrows -1) abAppend(ab, "\r\n", 2);
    }
}

bool isHeaderRow(int row) {
    if (row == Con.headerrow) return true;
    return false;
}

bool isDataRow(int row) {
    int idx = row - Con.headerrow;
    if (idx < algos.algoCount && idx >0) return true; // <<<<<<<<<<<<<<<< change to algoCount.
    return false;
}

bool isCursorRow(int row) {
    if (row == Con.cy) return true;
    return false;
}

void padAppendData(struct abuf *ab, int row) {
    /* Pad table based on the widest column entries 
    
        this whole function needs to be refactored to actually do one thing.
    */

    // Disable terminal auto-wrap. Might be able to do this in disableRawMode().
    abAppend(ab, "\x1b[?7l", 5); // MAY NEED TO REASSIGN AUTO WRAP IN VISUALIZER.

    // Lord forgive me. Not for what I've done but for what I'm about to do.
    int maxName = (int)strlen(Con.maxName); /////////////////////////////////////////////
    int maxDesc = (int)strlen(Con.maxDesc);
    int maxSpeed = (int)strlen(Con.maxSpeed);

    int sz = snprintf(NULL, 0, " %-*s %-*s %-*s", 
                maxName, algoTab[row].name,
                maxDesc, algoTab[row].description,
                maxSpeed, algoTab[row].speed);
    char buf[sz + 1];
    
    // absolutely vile find a better way.
    Con.totalcols = sz + 1;
    
    
    snprintf(buf, sizeof(buf), " %-*s %-*s %-*s", 
                maxName, algoTab[row].name,
                maxDesc, algoTab[row].description,
                maxSpeed, algoTab[row].speed);


    int len = strlen(buf) - Con.coloff;
    if (len < 0) len = 0;
    if (len > Con.screencols) len = Con.screencols;
    abAppend(ab, &buf[Con.coloff], len);    
    }

void checkScroll() {
    if (Con.cx < Con.coloff) {
        Con.coloff = Con.cx;
    }
    if (Con.cx >= Con.coloff + Con.screencols) {
        Con.coloff = Con.cx - Con.screencols + 1;
    }

}