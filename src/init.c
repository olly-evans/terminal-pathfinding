#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "terminal.h"
#include "init.h"
#include "welcome.h"
#include "algorithms.h"
#include "heap.h"
#include "cell.h"
#include "grid.h"

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