#ifndef GRID_H
#define GRID_H

typedef struct Grid {
    int rows, cols; // The rows and columns in the grid.

    struct Cell **cells; /* Pointer to array of cell pointers.
                            Each cell pointer points to an array of cells for each row.
                         */ 

    struct Cell *start_cell; // Cell pointer to start cell in grid.
    struct Cell *end_cell; // Cell pointer to end cell in grid.
} Grid;

extern struct Grid *g;

void drawGrid(struct Grid *g, struct abuf *ab);
struct Grid* randomizeGrid(struct Grid *g);
struct Grid* resetGrid(struct Grid* g);
struct Grid* initGrid(int rows, int cols);
void freeGrid(struct Grid *g);


#endif