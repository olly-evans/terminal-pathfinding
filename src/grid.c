#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "abuf.h"
#include "grid.h"
#include "cell.h"
#include "terminal.h"
#include "config.h"
#include "utils.h"

#define PERCENT_BARRIER 20 // % Chance of a cell being a barrier when we randomize the grid.

void drawGrid(Grid *g, struct abuf *ab) {
    
    /* Loop through the Cells in the row pointers and append their color and char to abuf. */

    abAppend(ab, HIDE_CURSOR, 6);

    for (int y = 0; y < g->rows; y++) {
        for (int x = 0; x < g->cols; x++) {

            struct Cell *c = &g->cells[y][x];
            
            char buf[32];
            snprintf(buf, sizeof(buf), "\x1b[%d;%dH", c->y + 1, c->x + 1);
            abAppend(ab, buf, strlen(buf)); 

            char *cell_color = getCellColor(c);

            abAppend(ab, cell_color, strlen(cell_color));
            abAppend(ab, &c->ch, 1);
            abAppend(ab, RESET_F, 4);
        }
    }
}

Grid* initGrid(int rows, int cols) {
	g = Malloc(sizeof(Grid));
	if (!g) die("initGrid() -> Malloc");

	g->rows = rows;
	g->cols = cols;

	// Allocate memory for an array of row pointers, sized for rows.
	g->cells = Malloc(sizeof(struct Cell*) * rows);
	if (!g->cells) die("initGrid() -> Malloc");

	for (int y = 0; y < rows; y++) {
		// Allocate memory for a row of cells, sized for cols
		g->cells[y] = Malloc(sizeof(struct Cell) * cols);
		if (!g->cells[y]) die("initGrid() -> Malloc");

		for (int x = 0; x < cols; x++) {
			if (y == 0 || x == 0 || y == rows - 1 || x == cols - 1) {
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

    g->end_cell = NULL;
    g->start_cell = NULL;
    
	return g;
}

void freeGrid(Grid *g) {
	
	for (int y = 0; y < g->rows; y++) {
		free(g->cells[y]);
        g->cells[y] = NULL;
	}
	free(g->cells);
    g->cells = NULL;
    free(g);
}

Grid* randomizeGrid(Grid *g, int *nBarriers) {
    srand(time(NULL));

    int startRow = 0;
    int startCol = 0;

    int endRow = 0;
    int endCol = 0;

    int minRowCol = 1;
    int maxRow = g->rows-2; // g->rows/cols init to screenrows-padding
    int maxCol = g->cols-2; // 2 should be a global config grid padding var.

    int numBarriers = 0;

    // Generate two random independant coordinates for the start and end cell.
    while(startRow == endRow || startCol == endCol) {
        startRow = rand() % (maxRow + 1 - minRowCol) + minRowCol;//9
        startCol = rand() % (maxCol + 1 - minRowCol) + minRowCol;//

        endRow = rand() % (maxRow + 1 - minRowCol) + minRowCol; //9
        endCol = rand() % (maxCol + 1 - minRowCol) + minRowCol;
    }

    for (int y = 0; y < g->rows; y++) {
        for (int x = 0; x < g->cols; x++) {

            struct Cell *curr = &g->cells[y][x];

            // look in handleSpacePress for making start/end cell.
            // make into seperate function i think in cells.c.
            // assign start/end before loop.

            if (y == startRow && x == startCol && (g->start_cell == NULL) && (!isPermBarrier(curr))) {
                g->start_cell = curr;
                g->start_cell->type = START;
                continue;
            } 

            if (y == endRow && x == endCol && (g->end_cell == NULL) && (!isPermBarrier(curr))) {
                g->end_cell = curr;
                g->end_cell->type = END;
                continue;
            }

            int toBarrier = rand() % (100 / PERCENT_BARRIER);
            if (toBarrier != 0) continue;
            curr->type = BARRIER;
            numBarriers++;
        }
    }
    
    *nBarriers = numBarriers;
}

Grid* resetGrid(Grid* g) {
    freeGrid(g); // windows doesnt like this, we dont need to be freeing mem regardless. test w ubuntu.
    g = initGrid(Con.screenrows, Con.screencols);
    g->end_cell = NULL;
    g->start_cell = NULL;
    Con.numBarriers = 0;
    return g;
}