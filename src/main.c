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
    while (Con.state != RUN) {
        if (Con.state == WELCOME) drawMenu();
        if (Con.state == VISUALIZATION) drawPathfindingVisualizer();
        dashProcessKeypress();  
    }
    
    switch (M.algoIdx) {
        case 0:
            astar();
            break;
    }
    dashProcessKeypress();

    freeGrid(g);
    return 0;
}