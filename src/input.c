#include <stdlib.h>
#include <unistd.h>

#include "terminal.h"
#include "input.h"

void dashProcessKeypress() {
    char c = dashReadKey();

    switch (c) {
        case (CTRL_KEY('q')):
            write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen.
            write(STDOUT_FILENO, "\x1b[H", 3); // Cursor home.
            exit(0);
            break;
    }
}