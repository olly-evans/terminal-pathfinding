#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "grid.h"
#include "init.h"
#include "abuf.h"
#include "terminal.h"


int getSubStrNum(char *full, char *sub) {

    int count = 0;
    char *pos = full;

    while ((pos = strstr(pos, sub)) != NULL) {
        count++;
        pos += strlen(sub);
    }

    return count;
}

/* UNIT */

void test_init_grid() {

    struct Grid *g = initGrid(10, 10);

    assert(g != NULL);
    assert(g->rows == 10);
    assert(g->cols == 10);

    assert(g->cells != NULL);
    
    assert(g->end_cell == NULL);
    assert(g->start_cell == NULL);

    return;
}

void test_draw_grid() {

    int rows = 10;
    int cols = 10;

    struct Grid *g = initGrid(rows, cols);

    struct abuf ab = ABUF_INIT;

    drawGrid(g, &ab);
    assert(ab.b != NULL);

    assert(getSubStrNum(ab.b, HIDE_CURSOR) == 1);
    assert(getSubStrNum(ab.b, RESET_F) == rows*cols);


    return;
}

int main(void) {
    
    test_init_grid();
    test_draw_grid();

    return 0;
}