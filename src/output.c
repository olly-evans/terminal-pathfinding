#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "output.h"
#include "terminal.h"
#include "abuf.h"

void dashRefreshScreen() {
    struct abuf ab = ABUF_INIT; // hmmm could prob be in the init section

    abAppend(&ab, "\x1b[?25l", 6);
    abAppend(&ab, "\x1b[H", 4);
    abAppend(&ab, "\x1b[2J", 4);
    abAppend(&ab, "\x1b[3J", 4);

    drawGrid(&ab);

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", Con.cy + 1, Con.cx + 1);
    abAppend(&ab, buf, strlen(buf)); 


    abAppend(&ab, "\x1b[?25h", 6);
    
    write(STDOUT_FILENO, ab.b, ab.len);

    abFree(&ab);
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