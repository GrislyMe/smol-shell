#include "list.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GREEN 1
#define RED 2
#define BLUE 3
#define WHITE 4
#define GRAY 5

#define header ">[shell]$ "

void init_color_pair();
int load_cmd(char* path);
char* auto_comp(char* args, char* last);
inline int clear_comp(WINDOW* win, char* tmp, char* buff);
int read_input(WINDOW* win, char* ret);
