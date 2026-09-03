#include <windows.h>

/* 

Windows implementations of required functions

    - getWindowSize
    - dashReadKey
    - enableRawMode

*/

HANLDE hStdin;

int dashReadKey() {
    INPUT_RECORD irInBuf[120];
    DWORD cNumRead;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead))
        ErrorExit("ReadConsoleInput");


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