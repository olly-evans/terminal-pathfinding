#include <stdlib.h>
#include <stdio.h>

void die(char *s) {
    fprintf(stderr, "%s", s);
    exit(1);
}

void *Malloc(size_t n)
{
    void *p = malloc(n);
    if (p == NULL) die("malloc()");
    return p;
}