#include "networking.h"

void subserver_logic(int client_socket){
  while (1) {
    char buff[BUFFER_SIZE];
    int bytes = read(client_socket, buff, sizeof(buff));

    if (bytes <= 0) {
      exit(0);
    }
    buff[bytes] = '\0';
    rot13(buff);
    write(client_socket, buff, bytes);
  }

  close(client_socket);
  exit(0);
}

int main(int argc, char *argv[] ) {
  int listen_soc = server_setup();
  while (1) {

    int client_soc = server_tcp_handshake(listen_soc);

    int f = fork();
    if (f == 0) { // child
      close(listen_soc);
      subserver_logic(client_soc);
    } else {
      close(client_soc);
    }
  }
}
