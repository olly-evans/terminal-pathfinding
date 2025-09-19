#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "output.h"
#include "terminal.h"
#include "abuf.h"

void drawWelcomeScreen() {
    // Define abuf for this welcome menu.
    struct abuf wel_ab = ABUF_INIT;

    abAppend(&wel_ab, "\x1b[?25l", 6);
    abAppend(&wel_ab, "\x1b[H", 4);
    abAppend(&wel_ab, "\x1b[2J", 4);
    abAppend(&wel_ab, "\x1b[3J", 4);

    // Draw something?
    drawWelcomeRows(&wel_ab);
    // need to append using a row struct i think for this.

    // Cursor stuff, want it to take up whole row.

    abAppend(&wel_ab, "\x1b[?25h", 6);
    
    write(STDOUT_FILENO, wel_ab.b, wel_ab.len);

    // if algo chosen in cursor row, proceed.
    abFree(&wel_ab);
}

void drawPathfindingVisualizer() {
    // Perhaps make this refresh grid function instead then have seperate function for drawing welcome menu.
    struct abuf vis_ab = ABUF_INIT; // hmmm could prob be in the init section

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
            case PERM_BARRIER:
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

    int voffset = Con.screenrows / 3;

    for (int y = 0; y < Con.screenrows; y++) {

        if (y == voffset) {
            abAppend(ab, ">", 1), abAppend(ab, "\x1b[K", 3);
        } else {
            abAppend(ab, "\r\n", 2);
        }
    }
    abAppend(ab, "\x1b[H", 3); // Cursor home.

    int size = snprintf(NULL, 0, "\x1b[%dB", voffset);
    char buf[size];
    snprintf(buf, size, "\x1b[%dB", voffset); // snprintf appends null term.

    abAppend(ab, buf, size);
}