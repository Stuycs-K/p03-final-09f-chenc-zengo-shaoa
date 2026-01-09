#ifndef ui_ncurses
#define ui_ncurses
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ncurses.h>

#define MAX_MSG 100
#define MAX_MSG_LEN 256

void init_ui();
void setup_ui(char *input, char chat[][MAX_MSG_LEN], int chat_count);
void end_ui();

#endif
