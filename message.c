#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"

struct message *makeMessage(char *username, char *message) {
  struct message *m = malloc(sizeof(struct message));
  if (!m) return NULL;

	m->username = malloc(NAME_LENGTH);
  m->message = malloc(MAX_MESSAGE);

  return m;
}



void freeMsg(struct message *m) {
  if (!m) return;
  free(m->username);
  free(m->message);
  free(m);
}
