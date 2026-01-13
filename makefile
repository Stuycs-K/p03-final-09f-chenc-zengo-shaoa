.PHONY: clean compile run

CLIENT_OBJECTS = client.o networking.o ui.o message.o
CLIENT_FILES = client.c networking.c ui.c message.c

SERVER_OBJECTS = server.o networking.o message.o

H_FILES = networking.h ui.h message.h

run: client
	./client

compile: client server

client: $(CLIENT_OBJECTS)
	@gcc $(CLIENT_OBJECTS) -o client -lncurses

server: $(SERVER_OBJECTS)
	@gcc $(SERVER_OBJECTS) -o server

server.o: server.c
	@gcc -c -Wall server.c

$(CLIENT_OBJECTS) : $(CLIENT_FILES) $(H_FILES)
	@gcc -c -Wall $(CLIENT_FILES)

clean:
	rm -rf *.o client server
