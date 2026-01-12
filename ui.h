#ifndef ui_ncurses
#define ui_ncurses

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <ncurses.h>

#define MAX_MSG 100
#define MAX_MSG_LEN 256

void init_ui();
void create_name_page(char *input, int height, int width);
char setup_name_page( char *input, int *input_len, char *name, int server_socket);
char input_detect(char *input, int *input_len, int *cursor, int server_socket, char mode);
void setup_ui(char *input, char chat[][MAX_MSG_LEN], int chat_count, char *user);
void end_ui();

#endif
