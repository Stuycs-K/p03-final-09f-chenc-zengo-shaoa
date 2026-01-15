#ifndef ui_ncurses
#define ui_ncurses

#include <errno.h>
#include <ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_MSG 1000
#define MAX_MSG_LEN 256

void init_ui();
void create_name_page(char *input, int height, int width);
char setup_name_page(char *input, int *input_len, char *name, int server_socket,
                     int *cursor);
char input_detect(char *input, int *input_len, int *cursor, int server_socket,
                  char mode, char *user, int *scroll_offset);
void setup_ui(char *input, char chat[][MAX_MSG_LEN], int chat_count, char *user,
              int cursor, int scroll_offset);
void end_ui();

#endif
