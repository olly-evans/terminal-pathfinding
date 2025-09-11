#ifndef TERMINAL_H
#define TERMINAL_H

#define CTRL_KEY(k) ((k) & 0x1f)

struct dashConfig;

void die(char *s);
void disableRawMode();
void enableRawMode();
char dashReadKey();

#endif