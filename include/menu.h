#ifndef MENU_H
#define MENU_H

#define PATH_VERSION "0.0.1"

typedef struct Menu {
    char **algorithms;
    int algoCount;
    int selection;
} Menu;

extern struct Menu M;

typedef struct {
    char *key;
    char *action;
} MenuControl;

// enum AlgorithmSelection {
//     ASTAR = 0,
//     DFS,
//     BFS
// };

void drawMenu();
void drawMenuItems(struct abuf *ab);
int totalControlsChars(MenuControl controls[], int num_controls);

#endif