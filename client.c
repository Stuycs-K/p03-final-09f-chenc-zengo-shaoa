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

<<<<<<< HEAD

void selectLogic(int server_socket, fd_set *read_fds, char *buff){
	int bytes = 0;

	FD_ZERO(read_fds);
	FD_SET(server_socket,read_fds);

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 10000; // 10ms

	if (select(server_socket+1, read_fds, NULL, NULL, &tv) == -1) {
		perror("select error");
		end_ui();
		close(server_socket);
		return;
	}
	// socket (receive msg)
	if (FD_ISSET(server_socket, read_fds)) {
		bytes = read(server_socket, buff, sizeof(buff));
		if (bytes <= 0) {
			end_ui();
			close(server_socket);
			fprintf(stderr, "Socket Read Error (Bytes read: %d)", bytes);
			exit(0);
		}
		buff[bytes] = '\0';
	}
	if (chat_count < MAX_MSG && bytes > 0) {
		memset(chat[chat_count], 0, MAX_MSG_LEN-1);
		strncpy(chat[chat_count], buff, MAX_MSG_LEN - 1);
		chat[chat_count][MAX_MSG_LEN - 1] = '\0';
		chat_count++;
	}
}


void clientLogic(int server_socket){
	fd_set read_fds;
	char buff[BUFFER_SIZE];

	// buff for typed input
	char input[BUFFER_SIZE];
	int input_len = 0;
	memset(input, 0, BUFFER_SIZE);
	int cursor = 0;

	char user_name[32];

	// Naming the client
	while(!setup_name_page(input, &input_len, user_name, server_socket)){}

	while(1) {
		// INPUT DETECT: handles all inputs; see ui.c for implementation
		input_detect(input, &input_len, &cursor, server_socket, 0, user_name);

		selectLogic(server_socket, &read_fds, buff);

		setup_ui(input, chat, chat_count, user_name);
	}
=======
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
      if (c == 27) {
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
          clear();
        }
      } else if (c == KEY_BACKSPACE || c == 127) { // backspace or delete
        if (input_len > 0) {
          input_len--;
          input[input_len] = '\0';
          clear();
        }
      } else if (c >= ' ' && c <= '~' && input_len < BUFFER_SIZE - 1) {
        input[input_len++] = c;
        input[input_len] = '\0';
        cursor++;
      }
    }

    FD_ZERO(&read_fds);
    FD_SET(server_socket, &read_fds);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10000; // 10ms

    if (select(server_socket + 1, &read_fds, NULL, NULL, &tv) == -1) {
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
>>>>>>> f26ba3f60498c6c6058cb608bcf708a2d6183316

    setup_ui(input, chat, chat_count);
  }
}

<<<<<<< HEAD
int main(int argc, char *argv[] ) {
	signal(SIGINT, sighandler);
	char* IP = "127.0.0.1";
	if(argc >= 2){
		IP=argv[1];
	}
	server_socket = client_tcp_handshake(IP); // connect to server
	for(int i = 0; i < MAX_MSG; i++)
	init_ui(); // initialize ncurses
	printf("client connected.\n");
	clientLogic(server_socket);
=======
int main(int argc, char *argv[]) {
  signal(SIGINT, sighandler);
  char *IP = "127.0.0.1";
  if (argc > 2) {
    IP = argv[1];
  }
  server_socket = client_tcp_handshake(IP); // connect to server
  for (int i = 0; i < MAX_MSG; i++)
    memset(chat[MAX_MSG - 1], 0, MAX_MSG_LEN);
  init_ui(); // initialize ncurses
  printf("client connected.\n");
  clientLogic(server_socket);
>>>>>>> f26ba3f60498c6c6058cb608bcf708a2d6183316
}
