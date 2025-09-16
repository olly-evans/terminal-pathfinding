#include <stdlib.h>
#include <string.h>

#include "terminal.h"
#include "init.h"

void init() {
	Con.cx = 0;
	Con.cy = 0;

	Con.ey = -1;
	Con.ex = -1;

	if (getWindowSize(&Con.screenrows, &Con.screencols) == -1) die("getWindowSize");

	// Con.borderrows = Con.screenrows - 1; Here for old printing hashes code.

	initRowsStruct();
	
}

void initRowsStruct() {
	// Make room for playablerows
	Con.row = malloc(sizeof(lrow) * Con.screenrows);

	for (int i = 0; i < Con.screenrows; i++) {
		// Go into each .chars and make enough space for playablecols
		Con.row[i].chars = malloc(Con.screencols + 1);
		memset(Con.row[i].chars, ' ', Con.screencols);
	}
	

}