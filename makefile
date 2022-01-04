SHELL = /bin/bash
CC = gcc
CFLAGS = -O2 -Wall
LIB = -lncurses
SRC = $(filter-out $(LIB), $(wildcard *.c))
EXE = $(patsubst %.c, %, $(SRC))

shell: $(LIB) shell.c makefile
	$(CC) $(CFLAGS) list.c shell.c -o shell $(LIB)

.PHONY: clean
clean: $(EXE)
	rm $(EXE)
