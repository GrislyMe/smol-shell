#include "shell.h"

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

inline int clear_comp(WINDOW* win, char* tmp, char* buff) {
	int x, y;
	getyx(win, y, x);
	for (int i = 0; i < strlen(tmp + strlen(buff)); i++)
		mvdelch(y, x - i - 1);
	return 0;
}

int read_input(WINDOW* win, char* ret) {
	char input = 0;
	char buff[256];
	char* tmp = 0;
	int index = 0;
	int x, y;
	while (1) {
		switch (input = getch()) {
		case '\t':
			if (tmp)
				clear_comp(win, tmp, buff);

			tmp = auto_comp(buff, tmp);

			if (tmp) {
				attron(A_UNDERLINE | COLOR_PAIR(GRAY));
				addstr(tmp + strlen(buff));
				attroff(A_UNDERLINE | COLOR_PAIR(GRAY));
			}
			break;
		case 127:
			getyx(win, y, x);
			if (x <= strlen(header))
				break;

			if (tmp) {
				clear_comp(win, tmp, buff);
				tmp = 0;
			} else {
				mvdelch(y, x - 1);
				index--;
				buff[index] = '\0';
			}
			break;
		case '\n':
			if (tmp) {
				clear_comp(win, tmp, buff);
				addstr(tmp + strlen(buff));

				strcpy(buff, tmp);
				index = strlen(buff);
				tmp = 0;
				break;
			} else {
				strcpy(ret, buff);
				return 0;
			}
		default:
			addch(input | COLOR_PAIR(WHITE));
			buff[index] = input;
			index++;
			buff[index] = '\0';
		}
	}
	return 0;
}

void init_color_pair() {
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(GRAY, 8, COLOR_BLACK);
}

// int main() {
// WINDOW* win = initscr();
// load_cmd("tmp");
// raw();
// noecho();
// start_color();
// init_color_pair();
//
// attron(COLOR_PAIR(GREEN));
// addstr(header);
// attroff(COLOR_PAIR(GREEN));
// char input[256];
// read_input(win, input);
// getch();
// endwin();
// }
