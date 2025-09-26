#include "output.h"

void search() {
    initRunState();
}

void astar() {
    return;
}

void enterRunState() {
    /* 
    Loop through all cells and give them manhattan dist to end cell.
    Compute their respective f values. f = g + mh. 
    */

    for (int y = 0; y < Con.screenrows; y++) {
        for (int x = 0; x < Con.screencols; x++) {

            g->cells[y][x].md = getManhattanDist(&g->cells[y][x], g->end_cell);
            g->cells[y][x].g = 1;

            g->cells[y][x].f = g->cells[y][x].g + g->cells[y][x].md;
            
        }
    }
}