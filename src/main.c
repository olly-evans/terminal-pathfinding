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
        drawWelcomeScreen(); // maybe in seperate loop???
        // going to need keypress recog here for enter and arrow keys.
        // or in the welcomeScreen function.
        drawPathfindingVisualizer();
        dashProcessKeypress();
    }
    freeGrid(g);
    return 0;
}