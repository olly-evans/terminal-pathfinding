#include <assert.h>
#include <string.h>

#include "abuf.h"

void test_abuf_init() {
    struct abuf t_ab = ABUF_INIT;

    assert(t_ab.b == NULL);
    assert(t_ab.len == 0);

    abFree(&t_ab);
}
void test_ab_append() {

    struct abuf t_ab = ABUF_INIT;

    abAppend(&t_ab, "abcd", 4);

    assert(t_ab.b != NULL);
    assert(strcmp(t_ab.b, "abcd") == 0);
    assert(t_ab.len == 4);

    abAppend(&t_ab, "efg", 3);


    assert(strcmp(t_ab.b, "abcdefg") == 0);
    assert(t_ab.len == 7);

    abFree(&t_ab);
}

int main(void) {
    
    test_abuf_init();
    test_ab_append();
    
    return 0;
}