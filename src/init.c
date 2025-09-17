#include <stdlib.h>
#include <string.h>

#include "terminal.h"
#include "init.h"
#include "output.h"

struct Grid *g = NULL;

void init() {
	Con.cx = 0;
	Con.cy = 0;
	
	// Allocate rows and cols of terminal, initialise grid with these values.
	if (getWindowSize(&Con.screenrows, &Con.screencols) == -1) die("getWindowSize");
	g = initGrid(g, Con.screenrows, Con.screencols); 
	
}

struct Grid* initGrid(struct Grid *g, int rows, int cols) {
	g = malloc(sizeof(struct Grid));
	if (!g) die("Couldn't allocate memory for grid of terminals size.");

	// Allocate the rows and cols.
	g->rows = rows;
	g->cols = cols;

	// Allocate memory for an array of row pointers, sized for rows
	g->cells = malloc(sizeof(struct Cell*) * rows);
	if (!g->cells) die("g->cells not allocated.");

	for (int y = 0; y < rows; y++) {
		// Allocate memory for a row of cells, sized for cols
		g->cells[y] = malloc(sizeof(struct Cell) * cols);
		if (!g->cells[y]) die("g->cells[y] not allocated");

		for (int x = 0; x < cols; x++) {
			// Initialise Cells in row.
			g->cells[y][x].type = BORDER;
			g->cells[y][x].x = x;
			g->cells[y][x].y = y;
			g->cells[y][x].buf = '#';
		}
	}
	return g;
}

void freeGrid(struct Grid *g) {
	
	for (int y = 0; y < g->rows; y++) {
		free(g->cells[y]);
	}
	free(g->cells);
}