#include "abuf.h"
#include "grid.h"
#include "cell.h"

void drawGrid(struct abuf *ab) {
    
    /* Loop through the Cells in the row pointers and append their color and char to abuf. */
    
    int y;
    int x;
    for (y = 0; y < g->rows; y++) {
        for (x = 0; x < g->cols; x++) {

            // Current Cell
            struct Cell *c = &g->cells[y][x];
            
            switch (c->type) {
                case START:
                    abAppend(ab, "\x1b[32m", 5); // Green
                    abAppend(ab, &c->ch, 1);
                    break;

                case END:
                    abAppend(ab, "\x1b[31m", 5); // Red
                    abAppend(ab, &c->ch, 1);
                    break;

                case BARRIER:
                case PERMANENT_BARRIER:
                    abAppend(ab, "\x1b[37m", 5); // White
                    abAppend(ab, &c->ch, 1);
                    break;

                case CLOSED:
                    abAppend(ab, "\x1b[35m", 5);
                    abAppend(ab, &c->ch, 1);
                    break;

                case OPEN:
                    abAppend(ab, "\x1b[36m", 5);
                    abAppend(ab, &c->ch, 1);
                    break;

                case PATH:
                    abAppend(ab, "\x1b[33m", 5);
                    abAppend(ab, &c->ch, 1);
                    break;

                default:
                    abAppend(ab, &c->ch, 1);  // No color
                    break;
            }
        }
        if (y < g->rows - 1) abAppend(ab, "\r\n", 2);
    }
}