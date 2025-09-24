#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdbool.h>

#include "abuf.h"
#include "terminal.h"

#define PATH_VERSION "0.0.1"

/* Grid */

enum CellTypes {
    START,
    END,
    BARRIER,
    PERMANENT_BARRIER,
    EMPTY
};  

struct Cell {
    enum CellTypes type;
    int x, y;
    char ch;
};

struct Grid {
    int rows, cols;
    struct Cell **cells;

    struct Cell *start_cell;
    struct Cell *end_cell;
};

extern struct Grid *g;

void drawPathfindingVisualizer();
void drawWelcomeScreen();
void drawGrid(struct abuf *ab);
void drawWelcomeRows(struct abuf *ab);
void drawData(struct abuf *ab, int idx);
bool isHeaderRow(int row);
bool isDataRow(int row); 
bool isCursorRow(int row);
void checkScroll();
void formatAppendRows(struct abuf *ab, int row);

int getfRowLen(int row);
void formatRow(char * buf, size_t bufsize, int row);
void appendVisibleRow(struct abuf *ab, char *buf);

#endif