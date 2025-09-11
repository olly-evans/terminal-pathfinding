#include "terminal.h"
#include "init.h"

void initDash() {
  if (getWindowSize(&dashCon.dashrows, &dashCon.dashcols) == -1) die("getWindowSize");
}