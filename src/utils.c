#include <stdlib.h>
#include <stdio.h>

#define _POSIX_C_SOURCE 200809L
#include <time.h>   

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

void sleep_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}