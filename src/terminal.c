#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "terminal.h"

struct dashConfig {
    struct termios termiosOrig;
    int dashrows;
    int dashcols;
};

struct dashConfig dashCon;

void die(char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen.
    write(STDOUT_FILENO, "\x1b[H", 3); // Cursor home.
    
    perror(s);
    exit(1);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &dashCon.termiosOrig) == -1) die("disableRawMode() -> tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &dashCon.termiosOrig) == -1) die("enableRawMode() -> tcgetattr");
    atexit(disableRawMode);

    struct termios termiosRaw = dashCon.termiosOrig;
    termiosRaw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    termiosRaw.c_oflag &= ~(OPOST);
    termiosRaw.c_cflag |= (CS8);
    termiosRaw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    termiosRaw.c_cc[VMIN] = 0;
    termiosRaw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &termiosRaw) == -1) die("enableRawMode() -> tcgetattr");
}

char dashReadKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) die("read");
  }
  return c;
}