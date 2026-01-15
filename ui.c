#include "ui.h"
#include "networking.h"

void init_ui() {
  initscr();             // Initialize the standard window
  noecho();              // Don't display keys when they are typed
  nodelay(stdscr, true); // Set up non-blocking input with getch()
  curs_set(true);
  keypad(stdscr, true);
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

char setup_name_page(char *input, int *input_len, char *name, int server_socket,
                     int *cursor) {
  int height, width;
  getmaxyx(stdscr, height, width);
  create_name_page(input, height, width);
  move(height / 2, 37 + *cursor);
  refresh();
  strcpy(name, input);
  char c = input_detect(input, input_len, cursor, server_socket, 1, name);
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
        *cursor = 0;
        memset(input, 0, BUFFER_SIZE);
        clear();
        return 1;
      }
    } else if (c == KEY_LEFT) {
      if (*cursor > 0)
        (*cursor)--;
    } else if (c == KEY_RIGHT) {
      if (*cursor < *input_len)
        (*cursor)++;
    } else if (c == KEY_BACKSPACE || c == 127) { // backspace or delete
      if (*input_len > 0 && *cursor > 0) {
        memmove(input + *cursor - 1, input + *cursor, *input_len - *cursor);
        (*input_len)--;
        (*cursor)--;
        input[*input_len] = '\0';
        clear();
      }
    } else if (c == KEY_RESIZE) {
      clear();
    } else if (c >= ' ' && c <= '~' && *input_len < BUFFER_SIZE - 1) {
      memmove(input + *cursor + 1, input + *cursor, *input_len - *cursor);
      input[*cursor] = c;
      (*input_len)++;
      (*cursor)++;
      input[*input_len] = '\0';
    }
  }
  return 0;
}

void setup_ui(char *input, char chat[][MAX_MSG_LEN], int chat_count, char *user,
              int cursor) { // setup one frame
                            // clear();

  int height, width;
  getmaxyx(stdscr, height, width);
  if (height < 12 || width < 30)
    return;

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

  int row = 2;
  for (int i = start; i < chat_count && row < chat_height - 1; i++) {
    int offset = 0;
    while (offset < strlen(chat[i]) && row < chat_height - 1) {
      mvprintw(row, 2, "%.*s", width - 4, chat[i] + offset);
      offset += width - 4;
      row++;
    }
  }
  /*
   */

  mvprintw(chat_height, 2, " Message Input ");

  mvprintw(height - 5, 2, "Debug: chat_count: %d", chat_count);
  mvprintw(height - 4, 2, "User_name: %s", user);
  mvprintw(height - 3, 2, "Start chat: %s", chat[start]);

  int max_input = width - 6;
  int input_len = strlen(input);
  int input_start = 0;

  if (input_len > max_input) {
    input_start = input_len - max_input;
  }
  mvprintw(chat_height + 1, 2, "> %.*s", max_input, input + input_start);

  int cursor_x = 4 + cursor - input_start;
  if (cursor_x < 4) {
    cursor_x = 4;
  }
  if (cursor_x >= width - 1) {
    cursor_x = width - 2;
  }
  move(chat_height + 1, cursor_x);
  refresh();
}

void end_ui() { endwin(); }
