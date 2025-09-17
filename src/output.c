#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "output.h"
#include "terminal.h"
#include "abuf.h"

void dashRefreshScreen() {
    struct abuf ab = ABUF_INIT;

    abAppend(&ab, "\x1b[?25l", 6);
    abAppend(&ab, "\x1b[H", 4);
    abAppend(&ab, "\x1b[2J", 4);
    abAppend(&ab, "\x1b[3J", 4);

    drawGrid(&ab);

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", Con.cy + 1, Con.cx + 1);
    abAppend(&ab, buf, strlen(buf)); // move cursor. maybe movement stuff here.


    abAppend(&ab, "\x1b[?25h", 6);
    
    write(STDOUT_FILENO, ab.b, ab.len);

    abFree(&ab);
}

void drawGrid(struct abuf *ab) {
    

    // Get the right row from the pointer...
    // G->cells, an array of row pointers.
    
    int y;
    int x;
    for (y = 0; y < g->rows; y++) {
        for (x = 0; x < g->cols; x++) {
            abAppend(ab, &g->cells[y][x].buf, 1); // Should just be a char.
        }
        if (y < g->rows - 1) abAppend(ab, "\r\n", 2);
    }
}