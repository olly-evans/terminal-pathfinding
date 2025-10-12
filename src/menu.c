#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "terminal.h"
#include "abuf.h"
#include "input.h"
#include "algorithms.h"
#include "cell.h"
#include "grid.h"
#include "menu.h"

/* WELCOME SCREEN */



void drawMenu() {

    Con.state = STATE_WELCOME;

    // Define abuf for this welcome menu.
    struct abuf wel_ab = ABUF_INIT;

    abAppend(&wel_ab, "\x1b[?25l", 6);
    abAppend(&wel_ab, "\x1b[2J", 4);
    abAppend(&wel_ab, "\x1b[3J", 4);
    abAppend(&wel_ab, "\x1b[H", 3);

    drawMenuItems(&wel_ab);

    char mcursor[32];
    snprintf(mcursor, sizeof(mcursor), "\x1b[%d;%dH", Con.cy + 1, (Con.cx - Con.coloff)+ 1); // adding offset could be close
    abAppend(&wel_ab, mcursor, strlen(mcursor));

    write(STDOUT_FILENO, wel_ab.b, wel_ab.len);

    // if algo chosen in cursor row, proceed.
    abFree(&wel_ab);
}


void drawMenuItems(struct abuf *ab) {
    
    char welcome[80];
    abAppend(ab, "\x1b[1m", 4);
    int welcomelen = snprintf(welcome, sizeof(welcome), "Welcome to PATH -- Version %s", PATH_VERSION);
    abAppendCentered(ab, welcome);
    abAppend(ab, "\x1b[0m", 4);
    abAppend(ab, "\r\n\r\n", 4);

    abAppendCentered(ab, "An in-terminal pathfinding algorithm visualizer!");
    abAppend(ab, "\r\n\r\n", 4);
        
    
    // global variable here that keeps algorithmsIdx.
    int padding = (Con.screencols - strlen(M.algorithms[M.algoIdx])) / 2;
    while(padding--) abAppend(ab, " ", 1);

    abAppend(ab, "<", 1);
    
    abAppend(ab, "\x1b[33m", 5);
    abAppend(ab, M.algorithms[M.algoIdx], strlen(M.algorithms[M.algoIdx]));
    abAppend(ab, "\x1b[0m", 4);
    abAppend(ab, ">", 1);
    

    abAppend(ab, "\r\n\r\n", 4);
    
    abAppendCentered(ab, "[ Use the arrow-keys and Enter to select an algorithm ]");
}