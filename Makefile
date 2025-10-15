path: src/main.c src/terminal.c src/input.c src/init.c src/abuf.c src/heap.c src/algorithms.c src/cell.c src/grid.c src/visualizer.c src/menu.c src/queue.c; gcc -g -O0 -Iinclude -o $@ $^

clean: ; rm -f path