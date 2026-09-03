#include <windows.h>

#include "input.h"

/* 

Windows implementations of required functions

    - getWindowSize
    - dashReadKey
    - enableRawMode

*/

HANDLE hStdin; // feels like a global

VOID ErrorExit(LPCSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);

int dashReadKey() {

    INPUT_RECORD record;
    DWORD events;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);

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