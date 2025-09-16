path: src/main.c src/terminal.c src/input.c src/output.c src/init.c src/abuf.c; gcc -Iinclude -o $@ $^

clean: ; rm -f path