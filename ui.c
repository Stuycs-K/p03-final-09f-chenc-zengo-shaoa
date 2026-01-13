#include "ui.h"
#include "networking.h"

void init_ui() {
  initscr();             // Initialize the standard window
  noecho();              // Don't display keys when they are typed
  nodelay(stdscr, true); // Set up non-blocking input with getch()
  curs_set(true);
}

// Helper function to implement UI structure elements on the client
// Does NOT include text
void ui_elements(int height, int width, int chat_height) {
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

void create_name_page(char *input, int height, int width) {
  mvhline(height / 2 + 1, 1, 0, width - 2);
  mvprintw(height / 2, 20, " Enter username: %s", input);
}

char setup_name_page(char *input, int *input_len, char *name,
                     int server_socket) {
  int height, width;
  getmaxyx(stdscr, height, width);
  create_name_page(input, height, width);
  refresh();
  strcpy(name, input);
  char c = input_detect(input, input_len, 0, server_socket, 1, name);
  return c;
}

// Detects input using ncurses
char input_detect(char *input, int *input_len, int *cursor, int server_socket,
                  char mode, char *user) {
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
        if (mode == 0) {
          char send[512];
          sprintf(send, "%s: %s\n", user, input);
          int leng = strlen(user) + *input_len + 3;
          write(server_socket, send, leng);
        }
        input[*input_len] = '\0';
        *input_len = 0;
        memset(input, 0, BUFFER_SIZE);
        clear();
        return 1;
      }
    } else if (c == KEY_BACKSPACE || c == 127) { // backspace or delete
      if (*input_len > 0) {
        (*input_len)--;
        cursor--;
        input[*input_len] = '\0';
        clear();
      }
    } else if (c >= ' ' && c <= '~' && *input_len < BUFFER_SIZE - 1) {
      input[(*input_len)++] = c;
      input[*input_len] = '\0';
      cursor++;
    }
  }
  return 0;
}

void setup_ui(char *input, char chat[][MAX_MSG_LEN], int chat_count, char *user,
              int cursor) { // setup one frame
  // clear();

  int height, width;
  getmaxyx(stdscr, height, width);

  int start;
  int chat_height = height - 8;
  int max = chat_height - 3;
  ui_elements(height, width, chat_height);
  move(10, 10);

  mvprintw(1, 2, " Chat History ");
  if (chat_count < max)
    start = 0;
  else
    start = chat_count - max;

  char *thing = malloc(256);
  for (int i = start; i < chat_count; i++) {
    strcpy(thing, chat[i]);
    mvprintw(2 + i - start, 2, "%s", thing);
  }
  free(thing);
  /*
   */

  mvprintw(chat_height, 2, " Message Input ");

  mvprintw(height - 5, 2, "Debug: chat_count: %d", chat_count);
  mvprintw(height - 4, 2, "User_name: %s", user);
  mvprintw(height - 3, 2, "Start chat: %s", chat[start]);

  mvprintw(chat_height + 1, 2, "> %s", input);
  move(chat_height + 1, 4 + cursor);
  refresh();
}

void end_ui() { endwin(); }
