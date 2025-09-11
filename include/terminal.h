#ifndef TERMINAL_H
#define TERMINAL_H

#define CTRL_KEY(k) ((k) & 0x1f)

void die(char *s);
void disableRawMode();
void enableRawMode();
void dashRefreshScreen();
char dashReadKey();

#endif