#ifndef INPUT_H
#define INPUT_H

#include "cell.h"
#include "menu.h"

enum editorKey {
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN
};

void moveCursor(int key);
void processKeypress();

void handleSpacePress(struct Cell *curr_cell);
void handleRPress(struct Cell *curr_cell);

#endif