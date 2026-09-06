#include <stdio.h>
#include <assert.h>

#include "grid.h"
#include "init.h"

/* UNIT */

void test_init_grid() {

    /* Have to decouple grid from config stuff. Can Con and grid not be global? */

    struct Grid *g = initGrid(10, 10);

    assert(g != NULL);
    assert(g->rows == 10);
    assert(g->cols == 10);    
    return;
}

void test_draw_grid() {

    struct Grid *g = initGrid(1, 1);
    

    return;
}
int main(void) {
    test_init_grid();
    return 0;
}