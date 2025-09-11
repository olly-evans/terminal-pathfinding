#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#include "terminal.h"
#include "input.h"

int main(void) {
    enableRawMode();

    while (1) {
        dashRefreshScreen();
        dashProcessKeypress();
  }

    return 0;
}