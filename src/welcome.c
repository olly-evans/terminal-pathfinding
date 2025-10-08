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

/* CONTROLS */

const char *wel_controls_text =
    "Arrows"      "\x1b[46mMove/Scroll\x1b[0m"
    " Enter"          "\x1b[46mSelect Algorithm\x1b[0m"
    " CTRL-Q"         "\x1b[46mQuit\x1b[0m";

/* WELCOME SCREEN */

void drawWelcomeScreen() {

    Con.state = STATE_WELCOME;
    // checkScroll();

    // Define abuf for this welcome menu.
    struct abuf wel_ab = ABUF_INIT;

    abAppend(&wel_ab, "\x1b[?25l", 6);
    abAppend(&wel_ab, "\x1b[2J", 4);
    abAppend(&wel_ab, "\x1b[3J", 4);
    abAppend(&wel_ab, "\x1b[H", 3);

    // drawWelcomeRows(&wel_ab);

    char mcursor[32];
    snprintf(mcursor, sizeof(mcursor), "\x1b[%d;%dH", Con.cy + 1, (Con.cx - Con.coloff)+ 1); // adding offset could be close
    abAppend(&wel_ab, mcursor, strlen(mcursor));


    write(STDOUT_FILENO, wel_ab.b, wel_ab.len);

    // if algo chosen in cursor row, proceed.
    abFree(&wel_ab);
}





























/*
void drawWelcomeRows(struct abuf *ab) {

    abAppend(ab, "\x1b[?7l", 5); // Disable terminal auto-wrap.


    for (int y = 0; y < Con.screenrows; y++) {
                
        if (y == 0) {
            // always at the top, stops scrolling.
            char welcome[80];
            int welcomelen = snprintf(welcome, sizeof(welcome), "Welcome to PATH -- Version %s", PATH_VERSION);
            if (welcomelen > Con.screencols) welcomelen = Con.screencols;
            abAppend(ab, welcome, welcomelen);
        }

        if (isHeaderRow(y)) {
            abAppend(ab, "\x1b[46m", 5);

            int sz = getfRowLen(y - Con.headerrow) + 1;
            char buf[sz];

            formatRow(buf, sz, y - Con.headerrow);
            appendVisibleRow(ab, buf);

            abAppend(ab, "\x1b[0m", 4);
        }
        
        if (isCursorRow(y)) {
            abAppend(ab, "\x1b[7m\x1b[K", 7); // not extending to end of row.

            int sz = getfRowLen(y - Con.headerrow) + 1;
            char buf[sz];

            formatRow(buf, sz, y - Con.headerrow);
            appendVisibleRow(ab, buf);
            abAppend(ab, "\x1b[0m", 4); // Reset background.

        } else if (isDataRow(y)) {
            int sz = getfRowLen(y - Con.headerrow) + 1;
            char buf[sz];

            formatRow(buf, sz, y - Con.headerrow);
            appendVisibleRow(ab, buf);
        }
    
        if (y != Con.screenrows - 1) abAppend(ab, "\r\n", 2);
    }

    char controls[80];
    int controlslen = snprintf(controls, sizeof(controls), "%s", wel_controls_text);

    if (controlslen > Con.screencols) controlslen = Con.screencols;

    abAppend(ab, controls, controlslen);
}

bool isHeaderRow(int row) {
    if (row == Con.headerrow) return true;
    return false;
}

bool isDataRow(int row) {

    int idx = row - Con.headerrow;

    if (row == Con.screenrows - 1) return false; // last row is always controls.

    if (idx < algos.algoCount && idx >0) return true;
    return false;
}

bool isCursorRow(int row) {

    if (row == Con.screenrows - 1) return false; // last row always controls.

    if (row == Con.cy) return true;
    return false;
}


void checkScroll() {
    if (Con.cx < Con.coloff) {
        Con.coloff = Con.cx;
    }
    if (Con.cx >= Con.coloff + Con.screencols) {
        Con.coloff = Con.cx - Con.screencols + 1;
    }
}

int getfRowLen(int row) {
    return snprintf(NULL, 0, " %-*s %-*s %-*s", 
                algos.lName, algos.rows[row].name,
                algos.lDesc, algos.rows[row].description,
                algos.lSpeed, algos.rows[row].speed);
}

void formatRow(char * buf, size_t bufsize, int row) {
    algos.tablewidth = bufsize - 1;
    snprintf(buf, bufsize, " %-*s %-*s %-*s", 
                algos.lName, algos.rows[row].name,
                algos.lDesc, algos.rows[row].description,
                algos.lSpeed, algos.rows[row].speed);
}

void appendVisibleRow(struct abuf *ab, char *buf) {

    int len = strlen(buf) - Con.coloff;
    if (len < 0) len = 0;
    if (len > Con.screencols) len = Con.screencols;

    
    abAppend(ab, &buf[Con.coloff], len); 
}
*/