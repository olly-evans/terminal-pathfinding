#include "terminal.h"
#include "init.h"

void initDash() {
	dashCon.cx = 0;
	dashCon.cy = 0;
	
	if (getWindowSize(&dashCon.dashrows, &dashCon.dashcols) == -1) die("getWindowSize");
}