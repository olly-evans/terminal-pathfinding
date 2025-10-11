#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#include "terminal.h"
#include "input.h"
// #include "welcome.h"
#include "menu.h"
#include "init.h"
#include "algorithms.h"
#include "grid.h"

int main(void) {
    enableRawMode();
    init();

    // New; works but still wanna try no drawGrid().
    while (Con.state != STATE_RUN) {
        if (Con.state == STATE_WELCOME) drawWelcomeScreen();
        if (Con.state == STATE_VISUALIZATION) drawPathfindingVisualizer();
        dashProcessKeypress();  
    }
    
    astar(); // How is a chosen algo identified.. panel has a pointer to it perhaps.
    dashProcessKeypress();

    freeGrid(g);
    return 0;
}