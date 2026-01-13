#ifndef message_H
#define message_H

struct message{
	char *username;
	char *message;
	struct message *prev;
}

struct message *makeMessage(char *username, char *message);




#endif
