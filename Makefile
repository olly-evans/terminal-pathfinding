dash: src/main.c src/terminal.c ; gcc -Iinclude -o $@ $^

clean: ; rm -f dash