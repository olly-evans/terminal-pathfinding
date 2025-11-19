#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#include "terminal.h"
#include "input.h"
#include "visualizer.h"
#include "menu.h"
#include "init.h"
#include "algorithms.h"
#include "grid.h"

int main(void) {
    enableRawMode();
    init();

    while (Con.state != RUN) {
        if (Con.state == MENU) drawMenu();
        if (Con.state == VISUALIZATION) drawPathfindingVisualizer();
        dashProcessKeypress();  
    }
    
    switch (M.selection) {
        case 0:
            astar();
            break;
        case 1:
            DFS();
            break;
        case 2:
            BFS();
            break;
        default:
            die("Invalid algorithm choice");
    }
    // Allows check for run state in input.c
    // if check at the top of dashProcessKeypress() it will auto exit upon algorithm completion due to main structure.
    // Con.state = END;
    dashProcessKeypress();

    
    return 0;
}