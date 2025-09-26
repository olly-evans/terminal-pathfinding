#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#include "terminal.h"
#include "input.h"
#include "output.h"
#include "init.h"

int main(void) {
    enableRawMode();
    init();

    while (1) {
        // Con global instance of config struct.
        // Con.app_state changed upon enter keypress in STATE_WELCOME.
        if (Con.state == STATE_WELCOME) drawWelcomeScreen();
        if (Con.state == STATE_VISUALIZATION) drawPathfindingVisualizer();
        // if (Con.state == STATE_RUN) search();
        
        dashProcessKeypress();
    }

    freeGrid(g);
    return 0;
}