#ifndef INPUT_H
#define INPUT_H

enum editorKey {
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN
};

void dashMoveCursor(int key);
void dashProcessKeypress();

#endif