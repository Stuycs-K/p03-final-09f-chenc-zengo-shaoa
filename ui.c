#include "ui.h"
#include "networking.h"

void init_ui() {
	initscr();						 // Initialize the standard window
	noecho();							// Don't display keys when they are typed
	nodelay(stdscr, true); // Set up non-blocking input with getch()
	curs_set(true);
}

// Helper function to implement UI structure elements on the client
	// Does NOT include text
void ui_elements(int height, int width, int chat_height){
	mvhline(1, 1, 0, width - 2);

	mvhline(chat_height, 1, 0, width - 2);

	mvvline(2, 0, 0, chat_height - 2);
	mvvline(2, width - 1, 0, chat_height - 2);

	mvaddch(1, 0, ACS_ULCORNER);
	mvaddch(1, width - 1, ACS_URCORNER);

	mvaddch(chat_height, 0, ACS_LLCORNER);
	mvaddch(chat_height, width - 1, ACS_LRCORNER);

	mvhline(chat_height + 2, 1, 0, width - 2);
	mvvline(chat_height + 1, 0, 0, 1);
	mvvline(chat_height + 1, width - 1, 0, 1);

	mvaddch(chat_height, 0, ACS_LTEE);
	mvaddch(chat_height, width - 1, ACS_RTEE);
	mvaddch(chat_height + 2, 0, ACS_LLCORNER);
	mvaddch(chat_height + 2, width - 1, ACS_LRCORNER);
}

// Detects input using ncurses
void input_detect(char *input, int *input_len, int *cursor, int server_socket){
	int c = getch();
	if (c != ERR) {
		if (c == 9) { // tab as escape sequence
			clear();
			end_ui();
			close(server_socket);
			exit(0);
		}
		if (c == '\n') {
			if (*input_len > 0) {
				input[*input_len] = '\0';
				write(server_socket, input, *input_len);
				write(server_socket, "\n", 1);
				*input_len = 0;
				memset(input, 0, BUFFER_SIZE);
				clear();
			}
		} else if (c == KEY_BACKSPACE || c == 127) { // backspace or delete
			if (input_len > 0) {
				(*input_len)--;
				cursor --;
				input[*input_len] = '\0';
				clear();
			}
		} else if (c >= ' ' && c <= '~' && *input_len < BUFFER_SIZE - 1) {
			input[(*input_len)++] = c;
			input[*input_len] = '\0';
			cursor++;
		}
	}
}

void setup_ui(char *input, char chat[][MAX_MSG_LEN], int chat_count) { // setup one frame
	//clear();

	int height, width;
	getmaxyx(stdscr, height, width);

	int start;
	int chat_height = height - 8;
	int max = chat_height - 3;
	ui_elements(height, width, chat_height);
	move(10, 10);

	mvprintw(1, 2, " Chat History ");
	if (chat_count < max) start = 0;
	else start = chat_count - max;

	for (int i = start; i < chat_count; i++) {
		mvprintw(2 + i - start, 2, "%s", chat[i]);
	}
/*
	*/

	mvprintw(chat_height, 2, " Message Input ");

	mvprintw( height	- 5, 2, "Debug: chat_count: %d", chat_count);

	mvprintw(chat_height + 1, 2, "> %s", input);
	refresh();
}

void end_ui() {
	endwin();
}
