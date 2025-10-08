#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "welcome.h"
#include "abuf.h"
#include "algorithms.h"
#include "heap.h"
#include "cell.h"
#include "grid.h"

const int DIRS[4][2] = {
    { 0, -1 }, // Up
    { 0, 1 },  // Down
    { -1, 0 }, // Left
    { 1, 0 }   // Right
};

void astarGrid(Heap *hp, struct abuf *s_ab) {

    /* Very very very outdated compared to astarCell. Only here for testing for now. */

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

void astar() {
    /* 

    Find shortest path to end cell using the A* algorithm.
    Shortest path drawn using cell pointers.

    Cell states updated and appended to buffer before being
    written to the terminal.
        
    */

    // Init heap struct containing open and closed set, (bh and cs).
    Heap *hp = initHeap();

    g->start_cell->g = 0;
    g->start_cell->md = getManhattanDist(g->start_cell, g->end_cell);
    g->start_cell->f = g->start_cell->g + g->start_cell->md;
    g->start_cell->prev = NULL;

    hp = heapInsert(hp, g->start_cell); 
    drawCell(g->start_cell);

    while (hp->os_size > 0 && hp->bh != NULL) {
        
        struct Cell *current = heapExtract(hp);

        if (isEndCell(current)) {
            
            struct Cell *previous = g->end_cell->prev;
            while (previous != NULL && !isStartCell(previous)) {
                previous->ch = 'P';
                previous->type = PATH;
                drawCell(previous);

                previous = previous->prev;
            }
            break;
        }

        hp = makeClosed(hp, current);
        drawCell(current);

        // No diagonals, hence 4 neighbours. DIRS appendable to add diagonals.
        for (int i = 0; i < sizeof(DIRS)/sizeof(DIRS[0]); i++) {
            // See DIRS array.
            int nx = current->x + DIRS[i][0];
            int ny = current->y + DIRS[i][1];
            
            // Is this neighbour in the grid range.
            if (nx < 0 || ny < 0 || nx >= g->cols || ny >= g->rows) continue;
            
            // Point to neighbour of current.
            struct Cell *neighbour = &g->cells[ny][nx];

            if (neighbour->inClosedSet) continue;
            if (isWalkableCell(neighbour)) continue;

            int tentative_g = current->g + neighbour->weight;

            if (tentative_g < neighbour->g) {
                neighbour->prev = current;
                neighbour->g = tentative_g;
                neighbour->f = tentative_g + getManhattanDist(neighbour, g->end_cell);

                if (!neighbour->inOpenSet) {
                    hp = heapInsert(hp, neighbour);
                } else {
                    // Indexing if in open set here is not optimal, heap_index cell member better.
                    int idx = getOpenSetIdx(hp, neighbour); 
                    hp->bh[idx]->f = neighbour->f;
                    hp = heapBubbleUp(hp, idx);
                }
            }
            drawCell(neighbour);
        } 
    }
    // No solution.
}