#ifndef MENU_H
#define MENU_H

typedef struct {
    const char *name;
    const char *description;
    const char *speed;
} Algorithm;

// const Algorithm ALGORITHM_TABLE[] = {
//     // { "Algorithm Name", "Description", "Speed" }
//     {
//         "A*",
//         "Weighted and direction-based algorithm. A* is guaranteed to find the shortest path.",
//         "Fast"
//     },
//     {
//         "Dijkstra",
//         "Unweighted, but guarantees the shortest path.",
//         "Medium"
//     },
//     {
//         "BFS",
//         "Breadth-first search. Explores equally in all directions.",
//         "Slow"
//     }
// };

void drawMenu();
void drawMenuItems(struct abuf *ab);

#endif