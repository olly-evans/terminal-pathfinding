#include <stdlib.h>

#include "terminal.h"


void *Malloc(size_t n)
{
    void *p = malloc(n);
    if (p == NULL) die("malloc()");
    return p;
}

void *Realloc(void **orig_ptr, size_t newsize) {
    /* realloc() with error-checks. */
    if (orig_ptr == NULL) return NULL;

    void *tmp = realloc(*orig_ptr, newsize);
    
    if (tmp == NULL) return *orig_ptr;

    *orig_ptr = tmp;
    return *orig_ptr;
}

// void heapShowOpenSet(Heap* hp) {
    
//     disableRawMode(); 
//     for (int i = 0; i < hp->os_size; i ++) {
//         printf("OS %d: (%d, %d), f: %d\n", i, hp->bh[i]->y, hp->bh[i]->x, hp->bh[i]->f);
//         if (i == hp->os_size - 1) printf("\n");
//     }
//     printf("Open set size: %i\n", hp->os_size);
// }

// void heapShowClosedSet(Heap* hp) {

//     disableRawMode();
//     for (int i = 0; i < hp->cs_size; i++) {
//         printf("CS %d: (%d, %d)\n", i, hp->cs[i]->y, hp->cs[i]->x);
//         if (i == hp->cs_size - 1) printf("\n");
//     printf("Closed set size: %i\n", hp->cs_size);
//     }
// }

// // printf("Start Cell (y,x): (%d, %d)\n", g->start_cell->y, g->start_cell->x);
// // printf("End Cell (y,x): (%d, %d)\n", g->end_cell->y, g->end_cell->x);