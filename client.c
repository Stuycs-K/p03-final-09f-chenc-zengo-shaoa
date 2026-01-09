#include "networking.h"
#include "ui.h"

int server_socket;

static void sighandler(int signo) {
  end_ui();
  close(server_socket);
  exit(0);
}

void clientLogic(int server_socket){
  fd_set read_fds;
  char buff[BUFFER_SIZE];

  while(1) {
    if (!setup_ui()) { // returns 0 if press q
      end_ui();
      close(server_socket);
      exit(0);
    }
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(server_socket,&read_fds);

    if (select(server_socket+1, &read_fds, NULL, NULL, NULL) == -1) {
      perror("select error");
      end_ui();
      return;
    }

    // fgets for stdin (send msg to server)
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      if (fgets(buff, sizeof(buff), stdin) == NULL) {
        end_ui();
        close(server_socket);
        exit(0);
      }
      write(server_socket, buff, strlen(buff));
    }

    // socket (receive msg)
    if (FD_ISSET(server_socket, &read_fds)) {
      int bytes = read(server_socket, buff, sizeof(buff));

      if (bytes <= 0) {
        end_ui();
        close(server_socket);
        exit(0);
      }
      buff[bytes] = '\0';
      printf("received: %s", buff);
    }
  }
}

int main(int argc, char *argv[] ) {
  signal(SIGINT, sighandler);
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  init_ui();
  server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  clientLogic(server_socket);
}
