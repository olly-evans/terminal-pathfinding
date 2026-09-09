#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "grid.h"
#include "init.h"
#include "abuf.h"
#include "terminal.h"
#include "cell.h"


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

void test_randomize_grid() {

    Grid *g = initGrid(10, 10);

    int numBarriers = 0;
    g = randomizeGrid(g, &numBarriers);

    assert(g);

    // int startX = g->start_cell->x;
    // int endX = g->end_cell->x;

    // int startY = g->start_cell->y;
    // int endY = g->end_cell->y;

    assert(numBarriers != 0);
    // assert(g->start_cell->x != g->end_cell->x);
    // assert(g->start_cell->y != g->end_cell->y);

    return;
}

void test_reset_grid() {

    Grid *g = initGrid(10, 10);
    
    // ci demo commit
    g = resetGrid(g);
    
    return;
}

int main(void) {

    test_init_grid();
    test_draw_grid();
    test_randomize_grid();
    test_reset_grid();

    return 0;
}