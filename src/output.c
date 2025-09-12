#include <unistd.h>

#include "output.h"
#include "terminal.h"
#include "abuf.h"

void dashRefreshScreen() {
    struct abuf ab = ABUF_INIT;

    abAppend(&ab, "\x1b[2J", 4);
    abAppend(&ab, "\x1b[H", 3);

    dashDrawRows(&ab);

    abAppend(&ab, "\x1b[H", 3);
    write(STDOUT_FILENO, ab.b, ab.len);
}

void dashDrawRows(struct abuf *ab) {
    
    int y;

    for (int y = 0; y < dashCon.dashrows; y++) {
        abAppend(ab, "~", 1);

        if (y < dashCon.dashrows - 1) {
            abAppend(ab, "\r\n", 2);
        }
    }
}