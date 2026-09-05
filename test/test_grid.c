#include <stdio.h>

#include "grid.h"

/* UNIT */

void test_init_grid() {
    struct Grid *g = NULL;
    g = initGrid(g, 10, 10);

    // is y = row is x = col
    // i guess we can assert all conditions with a for.

    // for (int y = 0; y < 10; y++) {
    //     for (int x = 0; x < 10; x++) {
    //         assert(g->cells[y][x].g)
    //     }
    //     assert(g->cells[y])
    // }

    // access g->cells[11][11]
    
    return;
}

int main(void) {
    test_init_grid();
    return 0;
}