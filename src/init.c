#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <string.h>

#include "config.h"
#include "init.h"
#include "algorithms.h"
#include "heap.h"
#include "cell.h"
#include "grid.h"
#include "menu.h"
#include "utils.h"
#include "terminal.h"

#define MIN_ROWS 7
#define MIN_COLS 48

Grid *g = NULL;

char *algorithms[] = {
    "A*",
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

	Con.numBarriers = 0;
	Con.cellsSearched = 0; // Incremented upon cell addition to respective algorithms data structure

	// Allocate rows and cols of terminal, initialise grid with these values.
	if (getWindowSize(&Con.screenrows, &Con.screencols) == -1) 
		die("init() -> getWindowSize");
		
	if (Con.screenrows < MIN_ROWS || Con.screencols < MIN_COLS) 
		die("Terminal window too small!");
	
	g = initGrid(Con.screenrows, Con.screencols);
	if (!g) 
		die("init() -> initGrid");

	// // Pointers to start/end cell.
	// g->start_cell = NULL;
    // g->end_cell = NULL;

	write(STDOUT_FILENO, "\x1b[2 q", 5);
	
}