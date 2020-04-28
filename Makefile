.PHONY: all
.PHONY: main.c
all: main.c

run: main.c
	./main

main.c:
	gcc -g   -o main main.c  -lreadline -Wall -Werror

debug: main.c
	gdb main
