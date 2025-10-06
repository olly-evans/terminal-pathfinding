#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#include "terminal.h"
#include "input.h"
#include "welcome.h"
#include "init.h"
#include "algorithms.h"
#include "grid.h"

int main(void) {
    enableRawMode();
    init();

    while (1) {
        // Con.app_state changed upon enter keypress in STATE_WELCOME.
        if (Con.state == STATE_WELCOME) drawWelcomeScreen();
        if (Con.state == STATE_VISUALIZATION) drawPathfindingVisualizer();
        dashProcessKeypress();

        if (Con.state == STATE_RUN) {
            search(); // How is a chosen algo identified.. panel has a pointer to it perhaps.
            dashProcessKeypress();
            break;
        }
        
    }
    
    freeGrid(g);
    return 0;
}