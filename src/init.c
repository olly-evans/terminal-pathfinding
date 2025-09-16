#include <stdlib.h>
#include <string.h>

#include "terminal.h"
#include "init.h"
#include "output.h"

struct Grid *g = NULL;

void init() {
	Con.cx = 1;
	Con.cy = 1;
	

	if (getWindowSize(&Con.screenrows, &Con.screencols) == -1) die("getWindowSize");
	
	initGrid(g, Con.screenrows, Con.screencols);
	
}

void initGrid(struct Grid *g, int rows, int cols) {
	// 	Set the grid’s number of rows and cols
	g = malloc(sizeof(struct Grid));

	g->rows = rows;
	g->cols = cols;

	// Allocate memory for an array of row pointers, sized for rows
	g->cells = malloc(sizeof(struct Cell*) * rows);

	for (int y = 0; y < rows - 1; y++) {
		// Allocate memory for a row of cells, sized for cols
		g->cells[y] = malloc(sizeof(struct Cell) * cols);
		// For each column index from 0 to cols - 1:
		for (int x = 0; x < cols - 1; x++) {
			g->cells[y][x].type = EMPTY;
			g->cells[y][x].x = x;
			g->cells[y][x].y = y;
		}
	}
}

void freeGrid(struct Grid *g) {
	
	for (int y = 0; y < g->rows; y++) {
		free(g->cells[y]);
	}

	free(g->cells);
}