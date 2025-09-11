dash: src/main.c src/terminal.c src/input.c src/output.c src/init.c; gcc -Iinclude -o $@ $^

clean: ; rm -f dash