#ifndef CONFIG_H
#define CONFIG_H

enum appState {
	MENU_,
	VISUALIZATION,
    RUN
};

struct Config {
    int screenrows;
    int screencols;
    int headerrow;
    int cx, cy;

    int coloff;
    int rowoff;

    int cellsSearched;
    int numBarriers;

    enum appState state;
};

extern struct Config Con;

#endif