.PHONY: all
.PHONY: main.c
all: main.c

run: main.c
	./main

main.c:
	gcc -g   -o main main.c  -lreadline -lm -Wall -Werror -Wformat-security

debug: main.c
	gdb main
release: main.c
	mv main pc