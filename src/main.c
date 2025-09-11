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
    initDash();

    while (1) {
        dashRefreshScreen();
        dashProcessKeypress();
  }

    return 0;
}