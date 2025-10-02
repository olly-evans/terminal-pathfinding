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

    // astarGrid(&hp, &s_ab);
    astarCell(&hp, &s_ab);

    
    write(STDOUT_FILENO, s_ab.b, s_ab.len);
    abFree(&s_ab);
}

// will return heap probably.
void astarGrid(Heap *hp, struct abuf *s_ab) {

    struct abuf os_ab = ABUF_INIT;
    
    g->start_cell->g = 0;
    g->start_cell->md = getManhattanDist(g->start_cell, g->end_cell);
    
    // F = G + H
    g->start_cell->f = g->start_cell->g + g->start_cell->md;
    g->start_cell->prev = NULL;

    // Add start to the openset.
    hp = heapInsert(hp, g->start_cell);
    g->start_cell->inOpenSet = true; 

    while (hp->os_size > 0 && hp->bh != NULL) {
        // perhaps we dont remove from here and extract all in one.
        struct Cell *current = heapExtract(hp);
        // os_size = 0
        current->inOpenSet = false;

        
        // if end cell, long version. isEndCell(current)
        if (current->x == g->end_cell->x && current->y == g->end_cell->y) {
            
            struct Cell *previous = g->end_cell->prev;
            while (previous != NULL) {

                if (!isEndCell(previous) && !isStartCell(previous)) {
                    previous->ch = 'P';
                }
                drawGrid(s_ab); // debug cell by cell.


                previous = previous->prev;
            }
            break;
        }

        hp = makeClosed(hp, current);

        current->inClosedSet = true;
        // OS: 0
        // CS: 1

        for (int i = 0; i < 4; i++) {
            int nx = current->x + DIRS[i][0];
            int ny = current->y + DIRS[i][1];
            
            // In grid.
            if (nx < 0 || ny < 0 || nx >= g->cols || ny >= g->rows) continue;
            
            struct Cell *neighbour = &g->cells[ny][nx];

            if (neighbour->type == PERMANENT_BARRIER || neighbour->type == BARRIER) continue;

            int tentative_g = current->g + neighbour->weight;

            // what if one of these is true?
            if (neighbour->inClosedSet && tentative_g > neighbour->g) {
                continue;
            }

            // IT DOES WORK, THE ARRAY INDEXES ARE CHILDREN REMEMBER!!!!!
            if (tentative_g < neighbour->g) {
                neighbour->prev = current;
                neighbour->g = tentative_g;
                neighbour->f = tentative_g + getManhattanDist(neighbour, g->end_cell);

                if (!neighbour->inOpenSet) {
                    hp = heapInsert(hp, neighbour);
                    neighbour->inOpenSet = true;
                } else {
                    int idx = getOpenSetIdx(hp, neighbour);
                    hp->bh[idx]->f = neighbour->f;
                    hp = heapBubbleUp(hp, idx);
                }
            }
        drawGrid(s_ab);
        }
    }
}

void astarCell(Heap *hp, struct abuf *s_ab) {
    g->start_cell->g = 0;
    g->start_cell->md = getManhattanDist(g->start_cell, g->end_cell);

    // F = G + H
    g->start_cell->f = g->start_cell->g + g->start_cell->md;
    g->start_cell->prev = NULL;

    // Add start to the openset.
    hp = heapInsert(hp, g->start_cell); 


    while (hp->os_size > 0 && hp->bh != NULL) {
        abAppend(s_ab, "\x1b[?25l", 6);
        abAppend(s_ab, "\x1b[H", 4); // all above loop?
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

            if (neighbour->type == PERMANENT_BARRIER || neighbour->type == BARRIER) continue;


            int tentative_g = current->g + neighbour->weight;

            if (inClosedSet(hp, neighbour) && tentative_g > neighbour->g) continue;

            if (tentative_g < neighbour->g) {
                neighbour->prev = current;
                neighbour->g = tentative_g;
                neighbour->f = tentative_g + getManhattanDist(neighbour, g->end_cell);

                if (!neighbour->inOpenSet) {
                    hp = heapInsert(hp, neighbour);
                    neighbour->inOpenSet = true;
                } else {
                    int idx = getOpenSetIdx(hp, neighbour);
                    hp->bh[idx]->f = neighbour->f;
                    hp = heapBubbleUp(hp, idx);
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

    if (!isStartCell(curr) && !isEndCell(curr)) {
        curr->ch = 'C'; 
        
    }
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

bool isStartCell(struct Cell *cell) {
    return (cell->x == g->start_cell->x && cell->y == g->start_cell->y);
}

bool isEndCell(struct Cell *cell) {
    return (cell->x == g->end_cell->x && cell->y == g->end_cell->y);
}

void printOpenSet(Heap* hp, struct abuf *openset_buf) {
    for (int i = 0; i < hp->os_size; i++) {

        int size = snprintf(NULL, 0, "Cell%d: %d\n", i, hp->bh[i]->f);
        char buf[size + 1];
        snprintf(buf, sizeof(buf), "Cell%d: %d\n", i, hp->bh[i]->f);
        abAppend(openset_buf, buf, sizeof(buf));
        if (i == hp->os_size - 1) abAppend(openset_buf, "\n\n", 2);
    }
}

int getOpenSetIdx(Heap *hp, struct Cell *cell) {
    for (int i = 0; i < hp->os_size; i++) {
        if (hp->bh[i]->x == cell->x && hp->bh[i]->y == cell->y) {
            return i;
        }
    }
}