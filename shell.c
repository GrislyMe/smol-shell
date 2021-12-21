#include "list.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEN 1
#define RED 2
#define BLUE 3
#define WHITE 4

char header[] = ">[shell]$ ";

node* cmd;
int load_cmd(char* path) {
	node* tmp = malloc(sizeof(node));

	FILE* fd = fopen(path, "r");
	cmd = malloc(sizeof(node));
	while (fscanf(fd, "%s\n", tmp->str) != EOF) {
		append(cmd, tmp);
		tmp = malloc(sizeof(node));
	}
	return 0;
}

char* auto_comp(char* args, char* last) {
	node* current = cmd->next;
	if (last) {
		while (current) {
			if (!strcmp(current->str, last))
				break;
			current = current->next;
		}
		current = current->next;
	}

	while (current) {
		if (!strncmp(current->str, args, strlen(args)))
			return current->str;
		current = current->next;
	}
	return 0;
}

int read_input(WINDOW* win) {
	char input = 0;
	char buff[256];
	char* tmp = 0;
	int index = 0;
	int x, y;
	while (input != '\n') {
		switch (input = getch()) {
		case '\t':
			if (tmp) {
				getyx(win, y, x);
				for (int i = 0; i < strlen(tmp + strlen(buff)); i++)
					mvdelch(y, x - i - 1);
			}

			tmp = auto_comp(buff, tmp);

			if (tmp) {
				attron(A_UNDERLINE);
				addstr(tmp + strlen(buff));
				attroff(A_UNDERLINE);
			}
			break;
		case 127:
			getyx(win, y, x);
			if (x <= strlen(header))
				break;

			if (tmp) {
				for (int i = 0; i < strlen(tmp + strlen(buff)); i++)
					mvdelch(y, x - i - 1);
				tmp = 0;
			} else {
				mvdelch(y, x - 1);
				buff[index] = '\0';
				index--;
				buff[index] = '\0';
			}
			break;
		default:
			addch(input | COLOR_PAIR(WHITE));
			buff[index] = input;
			index++;
			buff[index] = '\0';
		}
	}
	return 0;
}

int main() {
	WINDOW* win = initscr();
	load_cmd("tmp");
	raw();
	noecho();
	start_color();
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);

	attron(COLOR_PAIR(GREEN));
	addstr(header);
	attroff(COLOR_PAIR(GREEN));
	read_input(win);
	// WINDOW* win = newwin(15, 17, 2, 10);
	// box(win, 0, 0);
	// mvwprintw(win, 0, 1, "Greeter");
	// wrefresh(win);
	// getch();
	endwin();
}
