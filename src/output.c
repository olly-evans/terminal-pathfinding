#include <unistd.h>

#include "output.h"

void dashRefreshScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen.
    write(STDOUT_FILENO, "\x1b[H", 3); // Cursor home.

    dashDrawRows();

    write(STDOUT_FILENO, "\x1b[H", 3);
}

void dashDrawRows() {
    
    int y;
    for (int y = 0; y < 12; y++) {
        write(STDOUT_FILENO, "~\r\n", 3);
    }
}