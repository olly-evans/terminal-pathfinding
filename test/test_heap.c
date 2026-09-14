#include <stdio.h>
#include <assert.h>

#include "cell.h"
#include "heap.h"

void test_init_heap() {

    Heap *initialised_heap = initHeap();

    assert(initialised_heap);

    assert(initialised_heap->openSet == NULL);
    assert(initialised_heap->closedSet == NULL);

    assert(initialised_heap->openSetSize == 0);
    assert(initialised_heap->closedSetSize == 0);

    assert(initialised_heap->openSetCapacity == INIT_OS_CAP);
    assert(initialised_heap->closedSetCapacity == INIT_CS_CAP);

    return;
}

void test_heap_insert() {

    Heap *insert_hp = initHeap();

    struct Cell cell1;
    struct Cell cell2;

    cell1.f = 44;
    cell2.f = 40;

    // One cell.

    heapInsert(insert_hp, &cell1);
    
    printf("%d\n", insert_hp->openSetSize);
    assert(insert_hp);
    // assert(insert_hp->openSetSize == 1);
    // assert(insert_hp->openSet != NULL);

    // // Two cells.

    // heapInsert(insert_hp, &cell2);

    // assert(insert_hp->openSetSize == 2);
    // assert(insert_hp->openSetCapacity == 4);
    // assert(insert_hp->openSet != NULL);

    // assert(insert_hp->openSet[0] == &cell2);

    return;
}

int main(void) {

    test_init_heap();
    test_heap_insert();

    return 0;
}