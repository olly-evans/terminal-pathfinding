#include <stdlib.h>
#include <string.h>

#include "terminal.h"
#include "init.h"
#include "algorithms.h"
#include "heap.h"
#include "cell.h"
#include "grid.h"
#include "menu.h"

#define MIN_ROWS 7
#define MIN_COLS 48

struct Grid *g = NULL;

char *algorithms[] = {
    "A*",
    "Dijkstra",
    "Depth-First Search",
    "Breadth-First Search"
};

struct Menu M = {
	.algoCount = sizeof(algorithms) / sizeof(algorithms[0]),
	.selection = 0,
	.algorithms = algorithms
};

void init() {
	
	// Init cursor pos
	Con.cx = 0;
	Con.cy = 0;

	// Allocate rows and cols of terminal, initialise grid with these values.
	if (getWindowSize(&Con.screenrows, &Con.screencols) == -1) die("init() -> getWindowSize");
	if (Con.screenrows < MIN_ROWS || Con.screencols < MIN_COLS) die("Terminal window too small!");

	g = initGrid(g, Con.screenrows, Con.screencols);
	if (!g) die("init() -> initGrid");

	// Pointers to start/end cell.
	g->start_cell = NULL;
    g->end_cell = NULL;
}