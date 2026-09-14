#include <assert.h>
#include <string.h>

#include "cell.h"
#include "grid.h"
#include "init.h"
#include "terminal.h"
#include "abuf.h"
 
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

    freeGrid(g);
    return;
}

void test_draw_grid() {

    int rows = 10;
    int cols = 10;

    Grid *g = initGrid(rows, cols);

    struct abuf t_ab = ABUF_INIT;

    drawGrid(g, &t_ab);


    assert(t_ab.b != NULL);

    assert(getSubStrNum(t_ab.b, HIDE_CURSOR) == 1);
    assert(getSubStrNum(t_ab.b, RESET_F) == rows*cols);

    freeGrid(g);
    abFree(&t_ab);
    return;
}

void test_randomize_grid() {

    Grid *g = initGrid(10, 10);

    int testNumBarriers = 0;
    g = randomizeGrid(g, &testNumBarriers);

    assert(g);

    assert(g->start_cell != NULL);
    assert(g->end_cell != NULL);

    assert(testNumBarriers != 0);
    assert(g->start_cell->x != g->end_cell->x);
    assert(g->start_cell->y != g->end_cell->y);

    freeGrid(g);
    return;
}

void test_reset_grid() {

    Grid *g = initGrid(10, 10);
    
    g = resetGrid(g);
    
    assert(g);
    
    assert(g->start_cell == NULL);
    assert(g->end_cell == NULL);
    
    freeGrid(g);
    return;
}

int main(void) {

    test_init_grid();
    test_draw_grid();
    test_randomize_grid();
    test_reset_grid();

    return 0;
}