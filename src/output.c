#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "output.h"
#include "terminal.h"
#include "abuf.h"

void dashRefreshScreen() {
    struct abuf ab = ABUF_INIT;

    abAppend(&ab, "\x1b[?25l", 6);
    abAppend(&ab, "\x1b[H", 3);

    dashDrawRows(&ab);

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", dashCon.cy + 1, dashCon.cx + 1);
    abAppend(&ab, buf, strlen(buf));

    abAppend(&ab, "\x1b[?25h", 6);
    
    write(STDOUT_FILENO, ab.b, ab.len);

    abFree(&ab);
}

void dashDrawRows(struct abuf *ab) {
    int y;
    for (int y = 0; y < dashCon.dashrows; y++) {
        abAppend(ab, "~", 1);
        
        abAppend(ab, "\x1b[K", 3);
        if (y < dashCon.dashrows - 1) {
            abAppend(ab, "\r\n", 2);
        }
    }
}