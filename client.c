#include "networking.h"
#include "ui.h"
int server_socket;

char chat[MAX_MSG][MAX_MSG_LEN];
int chat_count = 0;

static void sighandler(int signo) { // crtl-c handler
  end_ui();
  close(server_socket);
  exit(0);
}

void clientLogic(int server_socket) {
  fd_set read_fds;
  char buff[BUFFER_SIZE];

  // buff for typed input using getch
  char input[BUFFER_SIZE];
  int input_len = 0;
  memset(input, 0, BUFFER_SIZE);
  memset(chat, 0, MAX_MSG_LEN * MAX_MSG);
  int cursor = 0;

  while (1) {
    int bytes = 0;

    // keyboard input using ncurses
    int c = getch();
    if (c != ERR) {
      if (c == 24) { // control x
        clear();
        end_ui();
        close(server_socket);
        exit(0);
      }
      if (c == '\n') {
        if (input_len > 0) {
          input[input_len] = '\0';
          write(server_socket, input, input_len);
          write(server_socket, "\n", 1);
          input_len = 0;
          input[0] = '\0';
          cursor = 0;
          clear();
        }
      } else if (c == KEY_BACKSPACE || c == 127) { // backspace or delete
        if (cursor > 0) {
          // Shift characters left
          for (int i = cursor - 1; i < input_len; i++) {
            input[i] = input[i + 1];
          }
          input_len--;
          cursor--;
          clear();
        }
      } else if (c == KEY_LEFT) {
        if (cursor > 0)
          cursor--;
      } else if (c == KEY_RIGHT) {
        if (cursor < input_len)
          cursor++;
      } else if (c == KEY_RESIZE) {
        clear();
      } else if (c >= ' ' && c <= '~' && input_len < BUFFER_SIZE - 1) {
        // Shift characters right
        for (int i = input_len; i > cursor; i--) {
          input[i] = input[i - 1];
        }
        input[cursor] = c;
        input_len++;
        cursor++;
        input[input_len] = '\0';
      }
    }

    FD_ZERO(&read_fds);
    FD_SET(server_socket, &read_fds);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10000; // 10ms

    if (select(server_socket + 1, &read_fds, NULL, NULL, &tv) == -1) {
      if (errno == EINTR) {
        continue;
      }
      perror("select error");
      end_ui();
      close(server_socket);
      return;
    }

    // socket (receive msg)
    if (FD_ISSET(server_socket, &read_fds)) {
      bytes = read(server_socket, buff, sizeof(buff));

      if (bytes <= 0) {
        end_ui();
        close(server_socket);
        exit(0);
      }
      buff[bytes] = '\0';

      if (bytes == 1 && buff[0] == '\0') {
        continue;
      }
    }

    if (chat_count < MAX_MSG && bytes > 0) {
      strncpy(chat[chat_count], buff, MAX_MSG_LEN - 1);
      chat[chat_count][MAX_MSG_LEN - 1] = '\0';
      chat_count++;
    }

    setup_ui(input, chat, chat_count, "owen", cursor);
  }
}

int main(int argc, char *argv[]) {
  signal(SIGINT, sighandler);
  char *IP = "127.0.0.1";
  if (argc > 2) {
    IP = argv[1];
  }
  server_socket = client_tcp_handshake(IP); // connect to server
  for (int i = 0; i < MAX_MSG; i++)
    memset(chat[MAX_MSG - 1], 0, MAX_MSG_LEN);

  setenv("ESCDELAY", "25", 1);

  init_ui();            // initialize ncurses
  keypad(stdscr, TRUE); // bruh keypad

  printf("client connected.\n");
  clientLogic(server_socket);
}
