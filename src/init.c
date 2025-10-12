#include <stdlib.h>
#include <string.h>

#include "terminal.h"
#include "init.h"
#include "welcome.h"
#include "algorithms.h"
#include "heap.h"
#include "cell.h"
#include "grid.h"
#include "welcome.h"
#include "menu.h"

#define MIN_ROWS 7
#define MIN_COLS 48

struct Grid *g = NULL;

trow rows[] = {
    { "Algorithm Name", "Description", "Speed", true},

    { "A*", "Weighted and direction-based algorithm. A* is guaranteed to find the shortest path.", "Fast"},
    { "Dijkstra", "Unweighted, but guarantees the shortest path.", "Medium" },
    { "BFS", "Breadth-first search. Explores equally in all directions.", "Slow" },
	{"DFS", "Depth-first search.", "Slow"},
	{"DFS", "Depth-first search.", "Slow"},
	{"DFS", "Depth-first search.", "Slow"},
	{"DFS", "Depth-first search.", "Slow"},
	{"DFS", "Depth-first search.", "Slow"},
	{"DFS", "Depth-first search.", "Slow"},
	{"DFS", "Depth-first search.", "Slow"}
};

table algos = {
    .rowCount = sizeof(rows) / sizeof(rows[0]),
    .rows = rows
};

char *algorithms[] = {
    "A*",
    "Dijkstra",
    "Depth-First Search",
    "Breadth-First Search"
};

struct Menu M = {
	.algoCount = sizeof(algorithms) / sizeof(algorithms[0]),
	.algoIdx = 0,
	.algorithms = algorithms
};

void init() {
	
	// Init cursor pos
	Con.cx = 0;
	Con.cy = 0;
	Con.coloff = 0;
	Con.rowoff = 0;

	// Allocate rows and cols of terminal, initialise grid with these values.
	if (getWindowSize(&Con.screenrows, &Con.screencols) == -1) die("init() -> getWindowSize");
	if (Con.screenrows < MIN_ROWS || Con.screencols < MIN_COLS) die("Terminal window too small!");
	
	///////////////// !!!!!!!!!!!!!!! ////////////////////
	// the worst things ive ever seen.
	Con.headerrow = 2; // Will be refactored. TMP

	Con.cy = Con.headerrow + 1; // Assign after wel_offset assigned.
	
	///////////////// !!!!!!!!!!!!!!! ////////////////////

	g = initGrid(g, Con.screenrows, Con.screencols);
	if (!g) die("init() -> initGrid");

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

	for (int y = 0; y < algos.rowCount; y++) {

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