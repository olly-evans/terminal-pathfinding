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

// perhaps just search.c with algos elsewhere.

void search() {

    struct abuf s_ab = ABUF_INIT;

    abAppend(&s_ab, "\x1b[?25l", 6);
    abAppend(&s_ab, "\x1b[H", 3);
    abAppend(&s_ab, "\x1b[2J", 4);
    abAppend(&s_ab, "\x1b[3J", 4);

    // astarGrid(&hp, &s_ab);h fo
    astarCell(&s_ab);

    write(STDOUT_FILENO, s_ab.b, s_ab.len);
    abFree(&s_ab);
}

// will return heap probably.
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

void astarCell(struct abuf *s_ab) {
    /* 

    Find shortest path to end cell using the A* algorithm.
    Draw the shortest path using cell pointers.

    Cell states updated and written to appendable buffer
    upon change.
        
    */

    // Init heap struct containing open and closed set, (bh and cs).
    Heap *hp = initHeap();
    
    abAppend(s_ab, "\x1b[?25l", 6); // Hide Cursor
    abAppend(s_ab, "\x1b[H", 4); // Cursor to home (top left).

    // Draw grid once. Only cells that are changed updated from here.
    drawGrid(s_ab);

    g->start_cell->g = 0;
    g->start_cell->md = getManhattanDist(g->start_cell, g->end_cell);
    g->start_cell->f = g->start_cell->g + g->start_cell->md;
    g->start_cell->prev = NULL;

    hp = heapInsert(hp, g->start_cell); 

    while (hp->os_size > 0 && hp->bh != NULL) {
        
        struct Cell *current = heapExtract(hp);
        drawCell(s_ab, current);

        if (isEndCell(current)) {
            
            struct Cell *previous = g->end_cell->prev;
            while (previous != NULL && !isStartCell(previous)) {
                previous->ch = 'P';
                previous->type = PATH;
                drawCell(s_ab, previous);

                previous = previous->prev;
            }
            break;
        }

        hp = makeClosed(hp, current);
        drawCell(s_ab, current);

        // No diagonals, hence 4 neighbours. DIRS appendable to add diagonals.
        for (int i = 0; i < sizeof(DIRS)/sizeof(DIRS[0]); i++) {
            // See DIRS array.
            int nx = current->x + DIRS[i][0];
            int ny = current->y + DIRS[i][1];
            
            // Is this neighbour in the grid range.
            if (nx < 0 || ny < 0 || nx >= g->cols || ny >= g->rows) continue;
            
            // Point to neighbour of current.
            struct Cell *neighbour = &g->cells[ny][nx];

            if (neighbour->type == PERMANENT_BARRIER || neighbour->type == BARRIER) continue;


            int tentative_g = current->g + neighbour->weight;

            if (neighbour->inClosedSet && tentative_g > neighbour->g) continue;

            if (tentative_g < neighbour->g) {
                neighbour->prev = current;
                neighbour->g = tentative_g;
                neighbour->f = tentative_g + getManhattanDist(neighbour, g->end_cell);

                if (!neighbour->inOpenSet) {
                    hp = heapInsert(hp, neighbour);
                } else {
                    // Indexing if in open set here is not optimal.
                    int idx = getOpenSetIdx(hp, neighbour); 
                    hp->bh[idx]->f = neighbour->f;
                    hp = heapBubbleUp(hp, idx);
                }
            }
            drawCell(s_ab, neighbour);
        } 
    }
}