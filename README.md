[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/QfAIDTGi)
<<<<<<< HEAD
# Project Name: Chat
=======
# Chatroom
>>>>>>> alex

### Team Name: ACO

Roster: **Alex Shao, Owen Zeng, Christine Chen**

### Project Description:

This project is a **chat room program** where users can connect to a chat room, create an alias, and send messages concurrently with access to arrow key and scrollwheel navigation. Users may also resize the chat room at any time.

*We ended up removing the multiple chat room function of our project in order to focus on a better implementation of one chat room.*

### Video Link:

### Video: https://drive.google.com/file/d/1QIwb3FIpxDS1D7jlajtHX293PLn_T0Lz/view?usp=sharing

### Instructions:

<<<<<<< HEAD
- Clone the program from [Final Project](https://github.com/Stuycs-K/p03-final-09f-chenc-zengo-shaoa)
- Then run "make compile"
- In one terminal/machine run "make server"
- After creating the servers, on a different terminal or machine you can run the program by running "make compile" and "make client" to connect to the server
- Once connected, you should give a user name to be identified by, and then you can type to your chatroom.
=======
	1. Clone repository
	2. Compile with `make compile`
	3. Get server ip by running `ifconfig` on the same machine
	4. run `./server`
	5. run `./client <ip_address>` on any local machine

>>>>>>> alex

Interaction (Subject to change)

- User with client will connect by running ./client `ip-address` and connect to the server.

- User will be asked for an alias to be inputted

- User will access a chat room (Or a menu with multiple rooms when that is added, will change if we get there)

### Resources/ References:

- NCurses to read input and display ui
