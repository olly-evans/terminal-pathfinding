#include <stdio.h>
#include <assert.h>

#include "cell.h"
#include "heap.h"

void test_init_heap() {

    Heap *test_heap = initHeap();

    assert(test_heap);

    assert(test_heap->openSet == NULL);
    assert(test_heap->closedSet == NULL);

    assert(test_heap->openSetSize == 0);
    assert(test_heap->closedSetSize == 0);

    assert(test_heap->openSetCapacity == INIT_OS_CAP);
    
    return;
}

void test_heap_insert() {

    Heap *test_heap = initHeap();

    struct Cell cell1;
    struct Cell cell2;

    cell1.f = 44;
    cell2.f = 40;

    // One cell.

    heapInsert(test_heap, &cell1);

    assert(test_heap->openSetSize == 1);
    assert(test_heap->openSet != NULL);

    // Two cells.

    heapInsert(test_heap, &cell2);

    assert(test_heap->openSetSize == 2);
    assert(test_heap->openSetCapacity == 4);
    assert(test_heap->openSet != NULL);

    // assert(test_heap->openSet[0])

    return;
}

int main(void) {

    test_init_heap();
    test_heap_insert();

    return 0;
}