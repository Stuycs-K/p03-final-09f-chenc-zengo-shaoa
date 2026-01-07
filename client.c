
#include "networking.h"

static void sighandler(int signo) {
  if (signo == SIGINT) {
    close(server_socket);
    exit(0);
  }
}

void clientLogic(int server_socket){
  char buff[BUFFER_SIZE];

  int f = fork()
  if (f == 0) {
    // child receives msg
    while (1) {
      int bytes = read(server_socket, buff, sizeof(buff));

      if (bytes <= 0) {
        close(server_socket);
        exit(0);
      }
      buff[bytes] = '\0';
      printf("recieved: %s", buff);
    }
  } else {
    // parent sends msg
    write(server_socket, buff, strlen(buff));
  }
}

int main(int argc, char *argv[] ) {
  signo(SIGINT, sighandler);
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  setup_ui();
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  clientLogic(server_socket);
}
