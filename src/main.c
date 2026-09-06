#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#include "config.h"
#include "input.h"
#include "visualizer.h"
#include "menu.h"
#include "init.h"
#include "algorithms.h"
#include "grid.h"
#include "utils.h"
#include "terminal.h"

int main() {
    enableRawMode();
    init();

    while (Con.state != RUN) {
        if (Con.state == MENU_) 
            drawMenu();
        if (Con.state == VISUALIZATION) 
            drawPathfindingVisualizer();
        dashProcessKeypress();  
    }
    
    // I don't like that drawing cells is within the algorithm functions.
    // Perhaps we could call drawCell() upon some other condition.
    switch (M.selection) {
        case 0:
            astar(g);
            break;
        case 1:
            DFS(g);
            break;
        case 2:
            BFS(g);
            break;
        default:
            die("Invalid algorithm choice");
    }

    // Wait for input, user can look at run result.
    // Any input exits.
    dashReadKey();
    
    return 0;
}