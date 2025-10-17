#include <stdio.h>  
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "abuf.h"
#include "cell.h"
#include "grid.h"

void drawCell(struct Cell *cell) {

    /* 

    Move the cursor to the arg cell's y,x and append its new character.

    Write this small buffer to terminal to draw it.
    
    */

    struct abuf cell_buf = ABUF_INIT;
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", cell->y + 1, cell->x + 1);
    abAppend(&cell_buf, buf, strlen(buf)); 

    char *cell_color = getCellColor(cell);

    usleep(1000); 

    abAppend(&cell_buf, "\x1b[?25l", 6); // Hide cursor.
    abAppend(&cell_buf, cell_color, strlen(cell_color));
    abAppend(&cell_buf, &cell->ch, 1);
    abAppend(&cell_buf, "\x1b[0m", 4);
    abAppend(&cell_buf, "\r\n", 2);

    write(STDOUT_FILENO, cell_buf.b, cell_buf.len); 
    abFree(&cell_buf);
}

char* getCellColor(struct Cell *cell) {
    
    // need to be careful returning these.
    // Perhaps some buffer action required.
    switch (cell->type) {
        case PATH:
            return "\x1b[48;5;62m"; // Yellow

        // chance none below are printed. borders. could be from drawGrid
        case PERMANENT_BARRIER:
        case BARRIER:
            return "\x1b[47m"; // White
        
        case OPEN:
            return "\x1b[46m";
        case CLOSED:
            return "\x1b[45m";
    }   
}

bool isStartCell(struct Cell *c) {
    return (c->x == g->start_cell->x && c->y == g->start_cell->y);
}

bool isEndCell(struct Cell *c) {
    return (c->x == g->end_cell->x && c->y == g->end_cell->y);
}

bool isWalkableCell(struct Cell *c) {
    return !(c->type == PERMANENT_BARRIER || c->type == BARRIER);
}

int getManhattanDist(struct Cell *c1, struct Cell *end) {
    return 2*(abs(end->x - c1->x) + abs(end->y - c1->y));
}