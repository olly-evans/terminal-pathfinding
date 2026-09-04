#include <windows.h>

#include "input.h"
#include "algorithms.h"
#include "utils.h"

/* 

Windows console implementations of required functions

    - getWindowSize
    - dashReadKey
    - enableRawMode
    - disableRawMode

*/

HANDLE hStdin; // Global handle for console input queue.

static DWORD fdwSaveOldMode = 0; // Old console state.

VOID ErrorExit(LPCSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);

void disableRawMode() {
    if (!SetConsoleMode(hStdin, fdwSaveOldMode))
        die("SetConsoleMode");
    
    // Writes to reset console perhaps.

    showSearchStats();
}
void enableRawMode() {

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        die("GetStdHandle()");

    if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
        die("GetConsoleMode()");

    DWORD fdwRawMode = 0;
    fdwRawMode = ~(ENABLE_ECHO_INPUT |
              ENABLE_LINE_INPUT |
              ENABLE_PROCESSED_INPUT);

    fdwRawMode |= ENABLE_WINDOW_INPUT;

    SetConsoleMode(hStdin, fdwRawMode);
}

int dashReadKey() {

    INPUT_RECORD record;
    DWORD events;

    DWORD result = WaitForSingleObject(hStdin, 100);

    if (result == WAIT_TIMEOUT)
        return -1;

    if (result != WAIT_OBJECT_0)
        return -1;

    if (!ReadConsoleInput(hStdin, &record, 1, &events))
        return -1;

    if (record.EventType != KEY_EVENT)
        return -1;

    KEY_EVENT_RECORD *key = &record.Event.KeyEvent;

    if (!key->bKeyDown)
        return -1;

    switch (key->wVirtualKeyCode) {
        case VK_UP:    return ARROW_UP;
        case VK_DOWN:  return ARROW_DOWN;
        case VK_LEFT:  return ARROW_LEFT;
        case VK_RIGHT: return ARROW_RIGHT;
    }

    return key->uChar.AsciiChar;
}

int getWindowSize(int *rows, int *cols) {

    // will need a backdrop presumably incase of failure, write cursor to 999, 999 and return cursor pos.

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // may need our global handle may not if just queries stdout.
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi) == -1)
        return -1;
    
    *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return 0;
}