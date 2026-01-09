
#include "ui.h"


void draw_chat(char* prompt_bar){
	int height, width;
	getmaxyx(stdscr, height, width);

	int chat_height = height - 5;

	mvhline(0, 1, 0, width - 2);
	mvhline(chat_height, 0, 0, width - 2);

	mvvline(1, 0, 0, chat_height - 2);
	mvvline(1, width - 1, 0, chat_height - 2);

	mvaddch(0, 0, ACS_ULCORNER);
	mvaddch(0, width - 1, ACS_URCORNER);
	mvaddch(chat_height, -1, ACS_LLCORNER);
	mvaddch(chat_height, width - 0, ACS_LRCORNER);

	mvprintw(1, 2, " Chat History ");
	mvprintw(2, 2, "User1: Thing");
	mvprintw(3, 2, "User2: Wise?");

	mvhline(chat_height + 2, 1, 0, width - 2);
	mvvline(chat_height + 1, 0, 0, 1);
	mvvline(chat_height + 1, width - 1, 0, 1);

	mvaddch(chat_height, 0, ACS_LTEE);
	mvaddch(chat_height, width - 1, ACS_RTEE);
	mvaddch(chat_height + 2, 0, ACS_LLCORNER);
	mvaddch(chat_height + 2, width - 1, ACS_LRCORNER);
	mvprintw(chat_height, 2, " Message Input ");


	mvprintw(chat_height + 1, 2,"> %s", prompt_bar);
	refresh();

}

int addnull(int i, char *s){
	s[i] = '\n';
	return i--;
}

void setup_ui() {
	initscr();						// Initialize the standard window
	noecho();							// Don't display keys when they are typed
	nodelay(stdscr, true);// Set up non-blocking input with getch()
	curs_set(0);
	char input_buff[2048];
	memset(input_buff, 0, sizeof(input_buff));
	char *type_prompt = "Enter message here";
	char *pbar;
	int m_size = 0; // size of the current message
	int curpos; // position of the cursor on the current message
	// curs_set(false);

	// Start the game loop
	int running = 1;
	while (running) {
		// Check for user input
		int input;
		while ((input = getch()) != ERR) {
			// Exit when the user types q
			if (input == KEY_BACKSPACE && curpos > 0) {
				addnull(m_size-1, input_buff);
				m_size--;
				curpos --;
			}	else if (input >= ' ' && input <= '~'){
				input_buff[m_size] = (char) input;
				m_size++;
				addnull(m_size + 1, input_buff);
				curpos ++;
			}

		// Get the next user input
			input = getch();
		}

		//clear();
		if(m_size == 1) pbar = type_prompt;
		else pbar = input_buff;

		draw_chat(pbar);
	}

	endwin();

}
