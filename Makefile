dash: src/main.c src/terminal.c src/input.c; gcc -Iinclude -o $@ $^

clean: ; rm -f dash