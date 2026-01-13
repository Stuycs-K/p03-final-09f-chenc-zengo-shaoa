#ifndef MESSAGE_H
#define MESSAGE_H

struct message{
	char *username;
	char *message;
	struct message *prev;
};

struct message *makeMessage(char *username, char *message);
void freeMsg(struct message *m);



#endif

