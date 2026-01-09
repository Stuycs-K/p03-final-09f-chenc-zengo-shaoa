#include "ui.h"

void init_ui() {
  initscr();             // Initialize the standard window
  noecho();              // Don't display keys when they are typed
  nodelay(stdscr, true); // Set up non-blocking input with getch()
  // curs_set(false);
}

int setup_ui() { // setup one frame
  int input;
  while ((input = getch()) != ERR) {
    // Exit when the user types q
    if (input == 'q') {
      return 0;
    }
  }

  clear();

  int height, width;
  getmaxyx(stdscr, height, width);

  int chat_height = height - 5;

  mvhline(1, 1, 0, width - 2);

  mvhline(chat_height, 1, 0, width - 2);

  mvvline(2, 0, 0, chat_height - 2);
  mvvline(2, width - 1, 0, chat_height - 2);

  mvaddch(1, 0, ACS_ULCORNER);
  mvaddch(1, width - 1, ACS_URCORNER);
  mvaddch(chat_height, 0, ACS_LLCORNER);
  mvaddch(chat_height, width - 1, ACS_LRCORNER);

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
  mvprintw(chat_height + 1, 2, "> Type here...");

  refresh();
  return 1; // continue
}

void end_ui() {
  endwin();
}
