SHELL = /bin/bash
CC = gcc
CFLAGS = -O2 -lncurses
LIB = list.c
SRC = $(filter-out $(LIB), $(wildcard *.c))
EXE = $(patsubst %.c, %, $(SRC))

.PHONY: all
all: $(EXE)

shell: $(LIB) shell.c
	$(CC) $(CFLAGS) $(LIB) shell.c -o shell

.PHONY: clean
clean: $(EXE)
	rm $(EXE)
