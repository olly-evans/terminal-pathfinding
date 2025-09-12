#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <ctype.h>

#include "terminal.h"
#include "init.h"

struct dashConfig dashCon;

void die(char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen.
    write(STDOUT_FILENO, "\x1b[H", 3); // Cursor home.
	write(STDOUT_FILENO, "\x1b[3J", 4); // Clear scrollback buffer.


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
    if (nread == -1 && errno != EAGAIN) die("dashReadKey() -> read");
  }
  return c;
}

int getCursorPosition(int *rows, int *cols) {
	char buf[32];
	unsigned int i = 0;
	if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;
	while (i < sizeof(buf) - 1) {
		if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
		if (buf[i] == 'R') break;
		i++;
	}

	buf[i] = '\0';
	if (buf[0] != '\x1b' && buf[1] != '[') return -1;
	if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

	return 0;
}

int getWindowSize(int *rows, int *cols) {

	struct winsize ws;

	// If ioctl fails set cursor to value greater than any terminal window size and return its position.
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
		if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;
		return getCursorPosition(rows, cols);
	} else {
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return 0;
	}
}