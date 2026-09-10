#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

void sleep_ms(int milliseconds)
{
    #ifdef WIN32
        Sleep(milliseconds);
    #elif _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #else
        usleep(milliseconds * 1000);
    #endif
}