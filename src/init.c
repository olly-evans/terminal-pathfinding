#include <stdlib.h>
#include <string.h>

#include "terminal.h"
#include "init.h"
#include "output.h"
#include "algorithms.h"

struct Grid *g = NULL;

// Len of chars for each obj assigned at runtime, array length is also.
algoTable algoTab[] = {
	{"Algorithm Name", "Description", "Speed", 0},
    {"A*", "Weighted and direction-based algorithm. A* is guaranteed to find the shortest path.", "Fast", 0},
    {"Dijkstra", "Unweighted, but guarantees the shortest path.", "Medium", 0},
    {"BFS", "Breadth-first search. Explores equally in all directions.", "Slow", 0},
};

void init() {
	// Init cursor pos
	Con.cx = 0;
	Con.cy = 0;
	Con.coloff = 0;
	
	Con.algoCount = sizeof(algoTab) / sizeof(algoTab[0]);

	// Allocate rows and cols of terminal, initialise grid with these values.
	if (getWindowSize(&Con.screenrows, &Con.screencols) == -1) die("getWindowSize");

	Con.headerrow = (Con.screenrows / 3 ) - 1; // Assign after screenrows value retrieved.
	Con.cy = Con.headerrow + 1; // Assign after wel_offset assigned.

	g = initGrid(g, Con.screenrows, Con.screencols);
	if (!g) die("Couldn't initialise the grid.");

	// Pointers to start/end cell.
	g->start_cell = NULL;
    g->end_cell = NULL;

	initAlgoDisplayInfo();
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

void initAlgoDisplayInfo() {

	Con.maxName = "";
	Con.maxDesc = "";
	Con.maxSpeed = "";

	for (int i = 0; i < Con.algoCount; i++) {

		// Get name, description and speed that will take the most cols.
		if (strlen(Con.maxName) < strlen(algoTab[i].name)) Con.maxName = algoTab[i].name;
		if (strlen(Con.maxDesc) < strlen(algoTab[i].description)) Con.maxDesc = algoTab[i].description;
		if (strlen(Con.maxSpeed) < strlen(algoTab[i].speed)) Con.maxSpeed = algoTab[i].speed;

		// Get total length of all info, so we can test against screenrows.
		algoTab[i].len = strlen(algoTab[i].name) + 
						 strlen(algoTab[i].description) + 
						 strlen(algoTab[i].speed);

		// Calculate padding leftover.
		algoTab[i].padding = Con.screencols - algoTab[i].len;
	}
}