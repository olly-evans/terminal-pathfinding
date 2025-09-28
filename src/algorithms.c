#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#include "output.h"
#include "abuf.h"
#include "algorithms.h"
#include "heap.h"

// perhaps just search.c with algos elsewhere.

void search() {
    struct abuf s_ab = ABUF_INIT;

    abAppend(&s_ab, "\x1b[?25h", 6);
    initSearch(); // Needed here as we could still refresh or change E/S position.

    astar(&hp);

    //write(stdout, &s_ab, )
}

// will return heap probably.
void astar(Heap *hp) {
    // Add start to the openset.
    heapInsert(hp, g->start_cell);


    while (hp->os_size > 0) {
        struct Cell *current_cell = heapExtract(hp);     // Don't need to f check, done in bubbledown.
        if (current_cell == NULL) return; // tmp

        // Add current to closed set.
        hp = makeClosed(hp, current_cell);
    }   
    

    // get neighbors
    // make neighbours g distance to start.
    // update f score.

    // Closed set size of total cells.
    struct Cell closed_set[Con.screenrows * Con.screencols];



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
                g->cells[y][x].g = -1;
            }
            

            g->cells[y][x].f = g->cells[y][x].g + g->cells[y][x].md;
            
        }
    }
}

Heap* makeClosed(Heap *hp, struct Cell* curr) {

    /* Add a cell to the closed set. */

    // Make memory for it.
    hp->cs = realloc(hp->cs, (hp->cs_size + 1) * sizeof(*hp->cs )); // *hp->cs ??? 

    // Add it.
    hp->cs[hp->cs_size++] = curr;


    // Make cell.ch something different.
    curr->ch = 'C'; 

    return hp;
}