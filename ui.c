
#include "ui.h"

void setup_ui () {
  initscr();              // Initialize the standard window
  noecho();               // Don't display keys when they are typed
  nodelay(stdscr, true);  // Set up non-blocking input with getch()
  // curs_set(false);

  // Start the game loop
  int running = 1;
  while (running) {
    // Check for user input
    int input = getch();
    while (input != ERR) {
      // Exit when the user types q
      if (input == 'q') {
        running = false;
      }

      // Get the next user input
      input = getch();
    }

    // TODO: update state

    // Display output
    clear();
    mvprintw(3, 5, "Hello, world!");
    refresh();
  }

  // Shut down
  endwin();
}
