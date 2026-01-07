#include "networking.h"

void clientLogic(int server_socket){
  char buff[BUFFER_SIZE];

  while (fgets(buff, BUFFER_SIZE, stdin)) {
    write(server_socket, buff, strlen(buff));
    int bytes = read(server_socket, buff, sizeof(buff));

    if (bytes <= 0) {
      exit(0);
    }
    buff[bytes] = '\0';
    printf("recieved: %s", buff);
  }

  close(server_socket);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  clientLogic(server_socket);
}
