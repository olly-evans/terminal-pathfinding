#include <assert.h>

#include "abuf.h"

void test_abuf_init() {
    struct abuf t_ab = ABUF_INIT;

    assert(t_ab.b == NULL);
    assert(t_ab.len == 0);

}
void test_ab_append() {
    return;
}

int main(void) {
    
    test_abuf_init();
    test_ab_append();
    return 0;
}