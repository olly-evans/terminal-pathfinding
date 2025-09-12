#include <unistd.h>

#include "output.h"
#include "terminal.h"

void dashRefreshScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen.
    write(STDOUT_FILENO, "\x1b[H", 3); // Cursor home.

    dashDrawRows();

    write(STDOUT_FILENO, "\x1b[H", 3);
}

void dashDrawRows() {
    
    int y;

    for (int y = 0; y < dashCon.dashrows; y++) {
        write(STDOUT_FILENO, "~", 1);

        if (y < dashCon.dashrows - 1) {
            write(STDOUT_FILENO, "\r\n", 2);
        }
    }
}