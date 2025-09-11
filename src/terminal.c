#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#include "terminal.h"

struct termios termiosOrig;

void die(char *s) {
    perror(s);
    exit(1);
}
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &termiosOrig);
}

void enableRawMode() {
    tcgetattr(STDOUT_FILENO, &termiosOrig);
    atexit(disableRawMode);

    struct termios termiosRaw = termiosOrig;

    termiosRaw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &termiosRaw);
}