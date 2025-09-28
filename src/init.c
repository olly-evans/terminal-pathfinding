#include <stdlib.h>
#include <string.h>

#include "terminal.h"
#include "init.h"
#include "output.h"
#include "algorithms.h"
#include "heap.h"

struct Grid *g = NULL;

tablerow rows[] = {
    { "Algorithm Name", "Description", "Speed" },

    { "A*", "Weighted and direction-based algorithm. A* is guaranteed to find the shortest path.", "Fast" },
    { "Dijkstra", "Unweighted, but guarantees the shortest path.", "Medium" },
    { "BFS", "Breadth-first search. Explores equally in all directions.", "Slow" },
	{"DFS", "Depth-first search.", "Slow"}
};

table algos = {
    .algoCount = sizeof(rows) / sizeof(rows[0]),
    .rows = rows
};

void init() {
	
	// Init cursor pos
	Con.cx = 0;
	Con.cy = 0;
	Con.coloff = 0;

	// Allocate rows and cols of terminal, initialise grid with these values.
	if (getWindowSize(&Con.screenrows, &Con.screencols) == -1) die("getWindowSize");
	
	Con.headerrow = 2; // Always the 3rd row.

	if (Con.screenrows < Con.headerrow + algos.algoCount + 1) die("Larger terminal height required.");

	Con.cy = Con.headerrow + 1; // Assign after wel_offset assigned.

	g = initGrid(g, Con.screenrows, Con.screencols);
	if (!g) die("Couldn't initialise the grid.");

	// Pointers to start/end cell.
	g->start_cell = NULL;
    g->end_cell = NULL;

	getTableColWidths();

	initBinaryHeap();

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

	// Lord forgive me.
	for (int y = 0; y < rows; y++) {
		// Allocate memory for a row of cells, sized for cols
		g->cells[y] = malloc(sizeof(struct Cell) * cols);
		if (!g->cells[y]) die("g->cells[y] not allocated");

		for (int x = 0; x < cols; x++) {

			// Make terminal edges borders by default.
			if (y == 0 || x == 0 || y == Con.screenrows - 1 || x == Con.screencols - 1) {
				g->cells[y][x].type = PERMANENT_BARRIER;
				g->cells[y][x].ch = '#';
			} else {
				g->cells[y][x].type = EMPTY;
				g->cells[y][x].x = x;
				g->cells[y][x].y = y;
				g->cells[y][x].ch = ' ';
				g->cells[y][x].g = -1;
			}
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

void getTableColWidths() {
	/* Get the widest str in each column. */

	char *lNameStr = "";
	char *lDescStr = "";
	char *lSpeedStr = "";

	for (int y = 0; y < algos.algoCount; y++) {

		if (strlen(lNameStr) < strlen(algos.rows[y].name)) {
			lNameStr = algos.rows[y].name;
		}

		if (strlen(lDescStr) < strlen(algos.rows[y].description)) {
			lDescStr = algos.rows[y].description;
		}

		if (strlen(lSpeedStr) < strlen(algos.rows[y].speed)) {
			lSpeedStr = algos.rows[y].speed;
		}
	}

	algos.lName = strlen(lNameStr);
	algos.lDesc = strlen(lDescStr);
	algos.lSpeed = strlen(lSpeedStr);
}