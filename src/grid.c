#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "abuf.h"
#include "grid.h"
#include "cell.h"
#include "terminal.h"

#define BARRIER_CHANCE_FOR_RANDOMIZE 10

void drawGrid(struct abuf *ab) {
    
    /* Loop through the Cells in the row pointers and append their color and char to abuf. */
    
    int y;
    int x;
    for (y = 0; y < g->rows; y++) {
        for (x = 0; x < g->cols; x++) {

            // Current Cell
            struct Cell *c = &g->cells[y][x];
            
            switch (c->type) {
                case START:
                    abAppend(ab, TXT_GREEN, 5); // Green
                    abAppend(ab, &c->ch, 1);
                    break;

                case END:
                    abAppend(ab, TXT_RED, 5); // Red
                    abAppend(ab, &c->ch, 1);
                    break;

                case BARRIER:
                case PERMANENT_BARRIER:
                    abAppend(ab, BG_WHITE, 5); // White
                    abAppend(ab, &c->ch, 1);
                    abAppend(ab, RESET_F, 4);
                    break;
                case EMPTY:
                    abAppend(ab, BG_BLACK, 5); 
                    abAppend(ab, &c->ch, 1);
                    abAppend(ab, RESET_F, 4);
                    break;
                default:
                    abAppend(ab, &c->ch, 1);  // No color
                    break;
            }
        }
        if (y < g->rows - 1) abAppend(ab, "\r\n", 2);
    }
}

struct Grid* initGrid(struct Grid *g, int rows, int cols) {
	g = malloc(sizeof(struct Grid));
	if (!g) die("initGrid() -> malloc");

	g->rows = rows;
	g->cols = cols;

	// Allocate memory for an array of row pointers, sized for rows.
	g->cells = malloc(sizeof(struct Cell*) * rows);
	if (!g->cells) die("initGrid() -> malloc");

	for (int y = 0; y < rows; y++) {
		// Allocate memory for a row of cells, sized for cols
		g->cells[y] = malloc(sizeof(struct Cell) * cols);
		if (!g->cells[y]) die("initGrid() -> malloc");

		for (int x = 0; x < cols; x++) {
			if (y == 0 || x == 0 || y == Con.screenrows - 1 || x == Con.screencols - 1) {
				g->cells[y][x].type = PERMANENT_BARRIER;
			} else {
				g->cells[y][x].type = EMPTY;	
			}

            g->cells[y][x].ch = ' ';
			g->cells[y][x].x = x;
			g->cells[y][x].y = y;
			g->cells[y][x].g = INT_MAX;
			g->cells[y][x].weight = 1;
			g->cells[y][x].inOpenSet = false;
			g->cells[y][x].inClosedSet = false;
            g->cells[y][x].explored = false;
            g->cells[y][x].prev = NULL;
		}
	}
	return g;
}

void freeGrid(struct Grid *g) {
	
	for (int y = 0; y < g->rows; y++) {
		free(g->cells[y]);
        g->cells[y] = NULL;
	}
	free(g->cells);
    g->cells = NULL;
    free(g);
}

struct Grid* randomizeGrid(struct Grid *g) {
    srand(time(NULL));

    int startRow = 0;
    int startCol = 0;

    int endRow = 0;
    int endCol = 0;

    while(startRow == endRow || startCol == endCol) {
        startRow = rand() % (g->rows);
        startCol = rand() % (g->cols);

        endRow = rand() % (g->rows);
        endCol = rand() % (g->cols);
    }
    
    
    for (int y = 0; y < g->rows; y++) {
        for (int x = 0; x < g->cols; x++) {

            struct Cell *curr = &g->cells[y][x];
            int toBarrier = rand() % 5;

            // look in handleSpacePress for making start/end cell.
            // make into seperate function i think in cells.c.
            // assign start/end before loop.

            // check x and y.
            if (y == startRow && x == startCol && (g->start_cell == NULL) && (!isPermBarrier(curr))) {
                g->start_cell = curr;

                g->start_cell->type = START;
                g->start_cell->ch = 'S';
                continue;
            } 

            if (y == endRow && x == endCol && (g->end_cell == NULL) && (!isPermBarrier(curr))) {
                g->end_cell = curr;

                g->end_cell->type = END;
                g->end_cell->ch = 'E';
                continue;
            }

            if (toBarrier != 0) continue;
            curr->type = BARRIER;

        }
    }
}