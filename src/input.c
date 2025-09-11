#include <stdlib.h>

#include "terminal.h"
#include "input.h"

void dashProcessKeypress() {
    char c = dashReadKey();

    switch (c) {
        case (CTRL_KEY('q')):
            dashRefreshScreen();
            exit(0);
            break;
    }
}