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

// Add to this to display more controls at the bottom of menu.
MenuControl controls[] = {
    {"Scroll", "Arrows"},
    {"Select", "Enter"},
    {"Quit", "Q"},
};

void drawMenu() {
    Con.state = MENU;
    struct abuf wel_ab = ABUF_INIT;

    abAppend(&wel_ab, HIDE_CURSOR, 6);
    abAppend(&wel_ab, CLEAR_SCRN, 4);
    abAppend(&wel_ab, CLEAR_SCROLLBACK_BUF, 4);
    abAppend(&wel_ab, HOME_CURSOR, 3);


    drawMenuItems(&wel_ab);

    write(STDOUT_FILENO, wel_ab.b, wel_ab.len);
    abFree(&wel_ab);
}

void drawMenuItems(struct abuf *ab) {
    
    /* Welcome message */
    
    abAppend(ab, DISABLE_TERMINAL_AUTOWRAP, 5);
    char welcome[80];
    snprintf(welcome, sizeof(welcome), "Welcome to PATH -- Version %s", PATH_VERSION);
    abAppend(ab, "\x1b[1m"BG_PINK, 9);
    abAppendCentered(ab, welcome);

    abAppend(ab, "\x1b[K", 3); // Clear right from cursor.
    abAppend(ab, RESET_F, 4); 
    abAppend(ab, "\r\n\r\n", 4); // Double new line.

    abAppendCentered(ab, "An in-terminal pathfinding algorithm visualizer!");
    abAppend(ab, "\r\n\r\n", 4);
    
    /* Algorithm Selection */
    int padding = (Con.screencols - strlen(M.algorithms[M.selection])) / 2;
    while(padding--) abAppend(ab, " ", 1);
    abAppend(ab, "<", 1);
    
    abAppend(ab, TXT_BLUE"\x1b[1m", 9);
    abAppend(ab, M.algorithms[M.selection], strlen(M.algorithms[M.selection]));
    abAppend(ab, RESET_F, 4);

    abAppend(ab, ">", 1);
    abAppend(ab, "\r\n\r\n", 4);
    
    /* Controls */

    // Filthy hack. Couldn't find a better way to space and color the controls.
    // ANSI is included in strlen() of course so becomes a pain to pad to centre.
    int num_controls = sizeof(controls) / sizeof(controls[0]);
    int total_chars = totalControlsChars(controls, num_controls);

    padding = ((Con.screencols - total_chars) / 2);
    int sz = snprintf(NULL, 0, "\x1b[%d;%dH", Con.screenrows, padding);
    char cursor[sz + 1];
    snprintf(cursor, sizeof(cursor), "\x1b[%d;%dH", Con.screenrows, padding);
    abAppend(ab, cursor, sizeof(cursor));

    for (int y = 0; y < num_controls; y++) {

        abAppend(ab, controls[y].key, strlen(controls[y].key));
        abAppend(ab, BG_PINK"\x1b[1m", 9);
        abAppend(ab, controls[y].action, strlen(controls[y].action));
        abAppend(ab, RESET_F, 4);
    }
}

int totalControlsChars(MenuControl controls[], int num_controls) {

    int total_chars = 0;

    for (int i = 0; i < num_controls; i++) {
        total_chars += strlen(controls[i].key);
        total_chars += strlen(controls[i].action);
    }
    return total_chars;
}