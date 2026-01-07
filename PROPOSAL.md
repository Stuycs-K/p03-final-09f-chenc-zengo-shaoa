# Final Project Proposal

## Group Members:

Alex Shao, Owen Zeng, Christine Chen

# Intentions:

A chat room program where users can create and connect to multiple named individual chat rooms

# Intended usage:

A user will run a client and connect to a server using an IP. The user will be asked to input an alias. Then the user will be able to access a menu to interact with chat rooms and create their own room.

# Technical Details:

We will use memory allocation (obviously), working with files, signal handling, processes, and sockets.

- Memory will be allocated to store each chat room on a resizeable array datastructure on the server.

- Chat logs will be written to files and saved so that new clients have access to chat history.

- Signals will be handled by the client to prevent ^C

- The server will spawn children that connect with clients. These will exit once the client exits.

- Sockets will be used to connect clients with the server.

Additional Ambition: Password secured chat room (for those who know)

# Intended pacing:

From Tuesday(1/6), we will work on getting just one chatroom functional as our minimum viable product that is due on Monday(1/12).

From then on, we will work on being able to have multiple chatrooms, which should take around two days, and the last two days will be spent on adding password secured chat rooms or any additional features.
