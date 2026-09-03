#include <windows.h>

/* 

Windows implementations of required functions

    - getWindowSize
    - dashReadKey
    - enableRawMode

*/

HANDLE hStdin;

VOID ErrorExit(LPCSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);

int dashReadKey() {

    INPUT_RECORD record;
    DWORD cNumRead;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    while (ReadConsoleInput(hStdin, &record, 1, &cNumRead)) {
        if (record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown) {
            char c = record.Event.KeyEvent.uChar.AsciiChar;

            if (c == '\x1b') {
                char seq[2];

                if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
                if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';

                if (seq[0] == '[') {
                    switch (seq[1]) {
                        case 'A': return ARROW_UP;
                        case 'B': return ARROW_DOWN;
                        case 'C': return ARROW_RIGHT;
                        case 'D': return ARROW_LEFT;
                    }
                }

                return '\x1b';
            } else {
                return c;
            }

        }
    }


}

int getWindowSize(int *rows, int *cols) {

    // will need a backdrop presumably, write cursor to 999, 999 and return cursor pos.

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi) == -1)
        return;
    
    *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return 0;
}