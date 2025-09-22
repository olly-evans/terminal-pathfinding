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

    // Define abuf for this welcome menu.
    struct abuf wel_ab = ABUF_INIT;

    abAppend(&wel_ab, "\x1b[?25l", 6);
    abAppend(&wel_ab, "\x1b[2J", 4);
    abAppend(&wel_ab, "\x1b[3J", 4);
    abAppend(&wel_ab, "\x1b[H", 3);

    // abAppend(&wel_ab, "\x1b[37m", 4); // trying to change cursor color.

    // Draw something?
    drawWelcomeRows(&wel_ab);

    // sets pos, but also means itll be set in visualizer which isnt a massive problem rn.
    char mcursor[32];
    snprintf(mcursor, sizeof(mcursor), "\x1b[%d;%dH", Con.cy + 1, Con.cx + 1); // adding offset could be close
    abAppend(&wel_ab, mcursor, strlen(mcursor));

    // i think cursor is init by this ^^ to 0,0 i think. its definitely fucking with it.

    abAppend(&wel_ab, "\x1b[?25h", 6);

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
        

        // So happy with this, so simple but effective.
        if (isHeaderRow(y)) {
            abAppend(ab, "\x1b[46m\x1b[K", 8);
            drawData(ab, y - Con.headerrow);
            abAppend(ab, "\x1b[0m", 4);
        }

        
        // // if is cursor row and data row?
        if (isCursorRow(y)) {
            abAppend(ab, ">", 1);
            abAppend(ab, "\x1b[47m", 5);
            drawData(ab, y - Con.headerrow);
            abAppend(ab, "\x1b[K", 3); // clear line.

            abAppend(ab, "\x1b[0m", 4); // reset background.
        } else if (isDataRow(y)) {
            drawData(ab, y - Con.headerrow);
        }
        // if cy goes past algocount get seg fault.
        if (y != Con.screenrows -1) abAppend(ab, "\r\n", 2);
    }
}

bool isHeaderRow(int row) {
    if (row == Con.headerrow) return true;
    return false;
}

bool isDataRow(int row) {
    int idx = row - Con.headerrow;
    if (idx < Con.algoCount && idx >0) return true;
    return false;
}

bool isCursorRow(int row) {
    if (row == Con.cy) return true;
    return false;
}

void drawData(struct abuf *ab, int idx) {
        abAppend(ab, algoTab[idx].name, strlen(algoTab[idx].name));
        abAppend(ab, algoTab[idx].description, strlen(algoTab[idx].description));
        abAppend(ab, algoTab[idx].speed, strlen(algoTab[idx].speed));
}