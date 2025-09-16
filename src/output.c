#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "output.h"
#include "terminal.h"
#include "abuf.h"

void dashRefreshScreen() {
    struct abuf ab = ABUF_INIT;

    abAppend(&ab, "\x1b[?25l", 6);
    abAppend(&ab, "\x1b[H", 4);
    abAppend(&ab, "\x1b[2J", 4);
    abAppend(&ab, "\x1b[3J", 4);

    // dashDrawRows(&ab);
    drawRows(&ab);

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", Con.cy + 1, Con.cx + 1);
    abAppend(&ab, buf, strlen(buf)); // move cursor. maybe movement stuff here.


    abAppend(&ab, "\x1b[?25h", 6);
    
    write(STDOUT_FILENO, ab.b, ab.len);

    abFree(&ab);
}

// void dashDrawRows(struct abuf *ab) {

//     int y;
//     int x;
//     abAppend(ab, "\x1b[3J", 4); // Clear Scrollback buffer
//     for (y = 0; y < Con.borderrows; y++) {
        
//         abAppend(ab, "\x1b[K", 3); // Clear line.

//         for (x = 0; x < Con.screencols; x++) {
//             if (y == 0 || y == Con.borderrows - 1) {
//                 // abAppend(ab, "#", 1);
//             } else {
//                 // Also, to fill in chars inbetween hashtags might be difficult with this formats.
//                 // 999 works for now. May need to make it length.
//                 // Probably solved with erow struct check kilo.c
//                 // abAppend(ab, "#\x1b[999C#", 7);  
//             }
//         }
//         if (y < Con.screenrows - 1) abAppend(ab, "\r\n", 2); // Don't \n last row.
//     }
// }

void drawRows(struct abuf *ab) {
    
    for (int i = 0; i < Con.screenrows; i++) {
        abAppend(ab, Con.row[i].chars, Con.screencols);
        // abAppend(ab, "\r\n", 2);
    }
}