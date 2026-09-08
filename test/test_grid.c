#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "grid.h"
#include "init.h"
#include "abuf.h"

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

    struct abuf ab = ABUF_INIT;

    drawGrid(g, &ab);
    assert(ab.b != NULL);

    // what does drawGrid promise.
    
    // 10x10 grid promises 9 carriage returns. n-1 because of last line.
    
    int carriageRetCount = 0;
    char *pos = ab.b;
    printf("%s", pos);
    while ((pos = strstr(pos, "\r\n")) != NULL) {
        printf("posLen: %d", strlen(pos));
        carriageRetCount++;
        printf("carriageret: %d\n", carriageRetCount);
        pos += strlen("\r\n");
    }

    printf("count: %d\n", carriageRetCount);

    assert(carriageRetCount == 9);

    return;
}

int main(void) {
    test_init_grid();
    test_draw_grid();

    return 0;
}