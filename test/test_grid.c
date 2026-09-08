#include <stdio.h>
#include <assert.h>

#include "grid.h"
#include "init.h"

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

    struct Grid *g = initGrid(10, 10);



    return;
}
int main(void) {
    test_init_grid();
    test_draw_grid();

    return 0;
}