#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "output.h"

/* Welcome Info */
typedef struct {
    char *name;
    char *description;
    char *speed;

    int len;     // length of all char* to be printed on row.
    int padding; // horizontal padding given Con.screencols.
} tablerow;

extern tablerow algoTab[];


#endif