#include "networking.h"

int main(){
void subserver_logic(int client_soc, int listen_soc, fd_set *all_fds, int max) {
  char buff[BUFFER_SIZE];
  int bytes = read(client_soc, buff, sizeof(buff));

	return 0;
  if (bytes <= 0) {
    close(client_soc);
    FD_CLR(client_soc, all_fds);
    return;
  }
  buff[bytes] = '\0';

  for (int fd = 0; fd <= max; fd++) {
    if (FD_ISSET(fd, all_fds) && fd != client_soc && fd != listen_soc) { // send to currently tracking sockets
      write(fd, buff, bytes);
    }
  }
}

int main(int argc, char *argv[] ) {
  int listen_soc = server_setup();
  fd_set read_fds, all_fds;
  FD_ZERO(&all_fds);
  FD_SET(listen_soc, &all_fds);
  int max = listen_soc; // track for select call

  while (1) {
    // copy into read_fds
    read_fds = all_fds;
    if (select(max + 1, &read_fds, NULL, NULL, NULL) == -1) {
      perror("select error");
      return 1;
    }

    if (FD_ISSET(listen_soc, &read_fds)) {
      int client_soc = server_tcp_handshake(listen_soc);
      FD_SET(client_soc, &all_fds); // add neww connected client socket to all_fds
      if (client_soc > max) {
        max = client_soc;
      }
    }
    for (int fd = 0; fd <= max; fd++) {
      if (fd != listen_soc && FD_ISSET(fd, &read_fds)) {
        subserver_logic(fd, listen_soc, &all_fds, max);
      }
    }
  }
}
