#include <windows.h>

#include "input.h"

/* 

Windows console implementations of required functions

    - getWindowSize
    - dashReadKey
    - enableRawMode
    - disableRawMode

*/

HANDLE hStdin; // Global handle for console input queue.

static DWORD fdwSaveOldMode; // Old console state.

VOID ErrorExit(LPCSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);

void enableRawMode() {

    
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle()");

    if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
        ErrorExit("GetConsoleMode()");

    DWORD fdwRawMode;
    fdwRawMode = // choose flags for raw mode.

    // SetConsoleMode()
}

int dashReadKey() {

    INPUT_RECORD record;
    DWORD events;

    for (;;) {
        if (!ReadConsoleInput(hStdin, &record, 1, &events))
            return '\x1b';

        if (record.EventType != KEY_EVENT)
            continue;

        KEY_EVENT_RECORD *key = &record.Event.KeyEvent;

        if (!key->bKeyDown)
            continue;

        switch (key->wVirtualKeyCode) {
            case VK_UP:    return ARROW_UP;
            case VK_DOWN:  return ARROW_DOWN;
            case VK_LEFT:  return ARROW_LEFT;
            case VK_RIGHT: return ARROW_RIGHT;
        }

        if (key->uChar.AsciiChar != 0)
            return key->uChar.AsciiChar;
    }
}

int getWindowSize(int *rows, int *cols) {

    // will need a backdrop presumably incase failure, write cursor to 999, 999 and return cursor pos.

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi) == -1)
        return;
    
    *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return 0;
}