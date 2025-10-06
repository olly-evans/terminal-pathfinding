#include <stdio.h>  
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "abuf.h"
#include "cell.h"
#include "grid.h"

void drawCell(struct abuf *ab, struct Cell *cell) {

    /* 

    buffer is problematic here. a lot of writes needed with each cell. 
    perhaps just make a new buffer in here? Is basically the same thing.
    Perhaps dont update after individual cells but as neighbours or something.
    */

    // okay this isnt as flickery because we're writing less. as opposed to appending whole of ab.
    // need to investigate what that is again. but is exiting weirdly once its found path.
    struct abuf cell_buf = ABUF_INIT;
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", cell->y + 1, cell->x + 1);
    abAppend(&cell_buf, buf, strlen(buf)); 

    char *cell_col = getCellColor(cell);
    usleep(10000); 
    abAppend(&cell_buf, cell_col, strlen(cell_col));
    abAppend(&cell_buf, &cell->ch, 1);
    abAppend(&cell_buf, "\x1b[H", 3);
    write(STDOUT_FILENO, cell_buf.b, cell_buf.len); 
    
    // this write also isnt correct, testing it.
    // its writing the whole buffer up to this point or something its not great.
    // lots of flicker.
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

bool isStartCell(struct Cell *cell) {
    return (cell->x == g->start_cell->x && cell->y == g->start_cell->y);
}

bool isEndCell(struct Cell *cell) {
    return (cell->x == g->end_cell->x && cell->y == g->end_cell->y);
}

int getManhattanDist(struct Cell *c1, struct Cell *end) {
    return 2*(abs(end->x - c1->x) + abs(end->y - c1->y));
}