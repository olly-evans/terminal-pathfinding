#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "abuf.h"
#include "terminal.h"
#include "grid.h"


// const char *vis_controls_text =
//     "Arrows"      BG_BLUE "Move/Scroll" RESET_F
//     "Space"          BG_PINK "Select Algorithm" RESET_F
//     " CTRL-Q"         BG_PINK "Quit" RESET_F;


/* VISUALIZER */

void drawPathfindingVisualizer() {

    struct abuf vis_ab = ABUF_INIT;

    // abAppend(&vis_ab, HIDE_CURSOR, 6);
    // abAppend(&vis_ab, HOME_CURSOR, 4);
    // abAppend(&vis_ab, "\x1b[K", 3);
    // abAppend(&vis_ab, "\x1b[3J", 4);

    drawGrid(&vis_ab); // cell by cell, must abappend all at once.
    
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", Con.cy + 1, Con.cx + 1);
    abAppend(&vis_ab, buf, strlen(buf)); 


    abAppend(&vis_ab, SHOW_CURSOR, 6);
    
    // Don't forget this is a linux file descriptor.
    write(STDOUT_FILENO, vis_ab.b, vis_ab.len);

    // this writes cell by cell. need one big flush.
    abFree(&vis_ab);
}