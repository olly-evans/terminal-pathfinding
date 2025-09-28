#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#include "output.h"
#include "abuf.h"
#include "algorithms.h"
#include "heap.h"

const int DIRS[4][2] = {
    { 0, -1 }, // Up
    { 0, 1 },  // Down
    { -1, 0 }, // Left
    { 1, 0 }   // Right
};

// perhaps just search.c with algos elsewhere.

void search() {

    struct abuf s_ab = ABUF_INIT;

    abAppend(&s_ab, "\x1b[?25l", 6);
    abAppend(&s_ab, "\x1b[H", 4);
    abAppend(&s_ab, "\x1b[2J", 4);
    abAppend(&s_ab, "\x1b[3J", 4);

    drawGrid(&s_ab);
    astar(&hp);
    

    write(STDOUT_FILENO, s_ab.b, s_ab.len);
    abFree(&s_ab);
}

// will return heap probably.
void astar(Heap *hp) {

    // set start cell g to zero.
    // other cells g set in initGrid().
    // This is me thinking i dont need to loop through grid again in initSearch().
    g->start_cell->g = 0;
    g->start_cell->md = 0;

    // F = G + H
    g->start_cell->f = g->start_cell->g + g->start_cell->md;

    // Add start to the openset.
    hp = heapInsert(hp, g->start_cell);

    while (hp->os_size > 0 && hp->bh != NULL) {
        // start cell not shown to be in closed set visually.
        struct Cell *current_cell = heapExtract(hp); // Don't need to f check, done in bubbledown.
        if (current_cell == NULL) return;

        hp = makeClosed(hp, current_cell);
        if (current_cell == g->end_cell) {
            // highlight the cells in prev.
            // backtrack();
        } // we're finished here nothing to find.

        // get the neighbours and update their f.

        for (int i = 0; i < 4; i++) {
            int nx = current_cell->x + DIRS[i][0];
            int ny = current_cell->y + DIRS[i][1];

            // In grid.
            if (nx < 0 || ny < 0 || nx >= g->cols || ny >= g->rows) continue;
            
            struct Cell *neighbour = &g->cells[ny][nx];
            // G IS DIFFERENT FOR PATH, WHAT IS G UP TO THIS POINT? IN TOTAL?

            if (!isValidNeighbour(hp, neighbour)) {
                hp = makeClosed(hp, neighbour);
                continue;
            }

            int tentative_g = current_cell->g + neighbour->weight;
            
            if (tentative_g < neighbour->g) {
                neighbour->g = tentative_g;
                neighbour->prev = current_cell;

                neighbour->md = getManhattanDist(neighbour, g->end_cell);
                neighbour->f = neighbour->g + neighbour->md;

                if (!neighbour->inOpenSet) {
                    hp = heapInsert(hp, neighbour);
                    neighbour->inOpenSet = true;
                }

            }
        }
    }   
}

// void initSearch() {
//     /* 
//     Loop through all cells and give them manhattan dist to end cell.
//     Compute their respective f values. f = g + mh. 
//     */

//     for (int y = 0; y < Con.screenrows; y++) {
//         for (int x = 0; x < Con.screencols; x++) {

//             g->cells[y][x].md = getManhattanDist(&g->cells[y][x], g->end_cell);
            
//             if (x == g->start_cell->x && y == g->start_cell->y) {
//                 g->cells[y][x].g = 0;
//             } else {
//                 g->cells[y][x].g = -1;
//             }
//             g->cells[y][x].f = g->cells[y][x].g + g->cells[y][x].md;
            
//         }
//     }
// }

struct Cell* updateCellF(struct Cell *cell) {
    cell->g = getManhattanDist(cell, g->start_cell);
    cell->md = getManhattanDist(cell, g->end_cell);

    cell->f = cell->g + cell->md;
    return cell;
}

Heap* makeClosed(Heap *hp, struct Cell* curr) {

    /* Add a cell to the closed set. */

    // Make memory for it.
    hp->cs = realloc(hp->cs, (hp->cs_size + 1) * sizeof(*hp->cs )); // *hp->cs ??? 

    // Add it.
    hp->cs[hp->cs_size++] = curr;

    // Make cell.ch something different.
    if (curr == g->start_cell) return hp;
    
    curr->ch = 'C'; 
    curr->type = CLOSED;

    return hp;
}

bool isValidNeighbour(Heap *hp, struct Cell *cell) {

    if (cell->type == PERMANENT_BARRIER && cell->type == BARRIER) return false;
    
    // maybe just change to bool.
    for (int y = 0; y < hp->cs_size; y++) {
        if (hp->cs[y] == cell) {
            return false;
        }
    }

    return true;
}