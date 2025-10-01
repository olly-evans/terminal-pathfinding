#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

    astar(&hp, &s_ab);
    // drawGrid(&s_ab);
    
    

    write(STDOUT_FILENO, s_ab.b, s_ab.len);
    abFree(&s_ab);
}

// will return heap probably.
void astar(Heap *hp, struct abuf *s_ab) {

    g->start_cell->g = 0;
    g->start_cell->md = getManhattanDist(g->start_cell, g->end_cell);

    // F = G + H
    g->start_cell->f = g->start_cell->g + g->start_cell->md;
    g->start_cell->prev = NULL;

    // Add start to the openset.
    hp = heapInsert(hp, g->start_cell); 

    // os_size = 1


    while (hp->os_size > 0 && hp->bh != NULL) {
        abAppend(s_ab, "\x1b[?25l", 6);
        abAppend(s_ab, "\x1b[H", 4);
        drawGrid(s_ab);
        
        // perhaps we dont remove from here and extract all in one.
        struct Cell *current = heapExtract(hp);
        // os_size = 0

        
        // if end cell, long version.
        if (current->x == g->end_cell->x && current->y == g->end_cell->y) {
            
            struct Cell *previous = g->end_cell->prev;
            while (previous != NULL) {
                previous->ch = 'P';
                drawCell(s_ab, previous);

                previous = previous->prev;
            }
            break;
        }

        // rem from openset here?
            

        hp = makeClosed(hp, current);
        drawCell(s_ab, current);
        // OS: 0
        // CS: 1

        // as expected to up to here.

        for (int i = 0; i < 4; i++) {
            // { 0, -1 }, // Up
            // { 0, 1 },  // Down
            // { -1, 0 }, // Left
            // { 1, 0 }   // Right
            int nx = current->x + DIRS[i][0];
            int ny = current->y + DIRS[i][1];
            
            // In grid.
            if (nx < 0 || ny < 0 || nx >= g->cols || ny >= g->rows) continue;
            
            struct Cell *neighbour = &g->cells[ny][nx];

            // check for barriers.

            int tentative_g = current->g + neighbour->weight;

            if (inClosedSet(hp, neighbour) && tentative_g > neighbour->g) continue;

            // need to check for barriers.
            if (!inOpenSet(hp, neighbour) || tentative_g < neighbour->g) {
                neighbour->prev = current;
                neighbour->g = tentative_g;
                neighbour->f = neighbour->g + getManhattanDist(neighbour, g->end_cell);
                

                // this check isnt working.
                if (!inOpenSet(hp, neighbour)) {
                    hp = heapInsert(hp, neighbour); // okay so something up with this.
                }
            drawCell(s_ab, neighbour);


            }
        }
        
    }
    // no solution
}

Heap* makeClosed(Heap *hp, struct Cell* curr) {

    /* Add a cell to the closed set. */

    if (inClosedSet(hp, curr)) return hp;

    // Make memory for it.
    hp->cs = realloc(hp->cs, (hp->cs_size + 1) * sizeof(*hp->cs )); 

    // Add it.
    hp->cs[hp->cs_size] = curr;
    hp->cs_size++;

    curr->ch = 'C'; 
    curr->type = CLOSED;
    


    // // Make cell.ch something different.
    return hp;
}

bool isValidNeighbour(Heap *hp, struct Cell *cell) {

    if (cell->type == PERMANENT_BARRIER || cell->type == BARRIER) return false;
    
    // maybe just change to bool.
    for (int y = 0; y < hp->cs_size; y++) {
        if (hp->cs[y] == cell) {
            return false;
        }
    }

    return true;
}

bool inClosedSet(Heap *hp, struct Cell* curr) {
    for (int i = 0; i < hp->cs_size; i++) {
        if (curr == hp->cs[i]) {
            return true;
        }
    }
    return false;
}

bool inOpenSet(Heap *hp, struct Cell* curr) {
    for (int i = 0; i < hp->os_size; i++) {
        if (curr == hp->bh[i]) {
            return true;
        }
    }
    return false;
}