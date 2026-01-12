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

}

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
}
