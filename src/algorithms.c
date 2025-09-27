#include <unistd.h>

#include "output.h"
#include "abuf.h"
#include "algorithms.h"
#include "heap.h"

// perhaps just search.c with algos elsewhere.

void search() {
    struct abuf s_ab = ABUF_INIT;

    abAppend(&s_ab, "\x1b[?25l", 6);
    initSearch(); // Needed here as we could still refresh or change E/S position.
}

void astar() {
    return;
}

void initSearch() {
    /* 
    Loop through all cells and give them manhattan dist to end cell.
    Compute their respective f values. f = g + mh. 
    */

    for (int y = 0; y < Con.screenrows; y++) {
        for (int x = 0; x < Con.screencols; x++) {

            g->cells[y][x].md = getManhattanDist(&g->cells[y][x], g->end_cell);
            
            if (x == g->start_cell->x && y == g->start_cell->y) {
                g->cells[y][x].g = 0;
            } else {
                g->cells[y][x].g = 1;
            }
            

            g->cells[y][x].f = g->cells[y][x].g + g->cells[y][x].md;
            
        }
    }
}