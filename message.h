#ifndef MESSAGE_H
#define MESSAGE_H

#define NAME_LENGTH 32

#define MAX_MESSAGE 512


struct message{
	char *username;
	char *message;
	long long int id;
};

struct message *makeMessage(char *username, char *message, long long int id);

void freeMsg(struct message *m);



#endif

