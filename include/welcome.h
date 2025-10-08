#ifndef WELCOME_H
#define WELCOME_H

#include <stdbool.h>

#include "abuf.h"
#include "terminal.h"

#define PATH_VERSION "0.0.1"

// typedef struct Panel {
//     int x, y, w, h;

//     int scrollV;
//     int scrollH;
    
//     bool needsRedraw;
//     bool cursorOn;

// } Panel;

typedef struct {
    char *name;
    char *description;
    char *speed;

    bool needsRedraw;
    bool isVisible;
} Panel;

typedef struct {
    int lName;
    int lDesc;
    int lSpeed;

    int tablewidth;
    int algoCount;
    Panel *rows;
} Panels;

extern Panels algos;
extern Panel algoRows[];

void drawPathfindingVisualizer();
void drawWelcomeScreen();
void drawWelcomeRows(struct abuf *ab);
bool isHeaderRow(int row);
bool isDataRow(int row); 
bool isCursorRow(int row);
void checkScroll();


void formatAppendRows(struct abuf *ab, int row);

int getfRowLen(int row);
void formatRow(char * buf, size_t bufsize, int row);
void appendVisibleRow(struct abuf *ab, char *buf);


#endif