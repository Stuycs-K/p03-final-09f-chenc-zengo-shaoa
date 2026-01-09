.PHONY: clean compile run

run: client
	./client

compile: client server

client: client.o networking.o ui.o networking.h ui.h
	@gcc client.o networking.o ui.o -o client -lncurses

server: server.o networking.o networking.h
	@gcc server.o networking.o -o server

server.o: server.c
	@gcc -c -Wall server.c

client.o: client.c
	@gcc -c -Wall client.c

networking.o: networking.c
	@gcc -c -Wall networking.c

ui.o: ui.c
	@gcc -c -Wall ui.c

clean:
	rm -rf *.o client server
