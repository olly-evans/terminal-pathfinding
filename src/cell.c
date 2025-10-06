#include <stdio.h>  
#include <string.h>

#include "abuf.h"
#include "cell.h"

void drawCell(struct abuf *ab, struct Cell *cell) {

    // append cursor pos
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", cell->y + 1, cell->x + 1);
    abAppend(ab, buf, strlen(buf)); 

    char *cell_col = getCellColor(cell);
    // usleep(10000); // wont work :(
    abAppend(ab, cell_col, strlen(cell_col));
    abAppend(ab, &cell->ch, 1);
}

char* getCellColor(struct Cell *cell) {
    
    // need to be careful returning these.
    // Perhaps some buffer action required.
    switch (cell->type) {
        case PATH:
            return "\x1b[33m"; // Yellow

        // chance none below are printed. borders. could be from drawGrid
        case PERMANENT_BARRIER:
        case BARRIER:
            return "\x1b[37m"; // White
        
        case OPEN:
            return "\x1b[36m";
        case CLOSED:
            return "\x1b[35m";
    }   
}