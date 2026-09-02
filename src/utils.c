#include <stdlib.h>

void *Malloc(size_t n)
{
    void *p = malloc(n);
    if (p == NULL) die("malloc()");
    return p;
}