# Dev Log:

This document must be updated daily every time you finish a work session.

## Christine Chen

### 2026-01-06 - Basic Setup
Added basic information to README and set up devlogs. Created files and completed networking.c and networking.h by minimally modifying prior TCP networking code.

### 2026-01-07 - Basic Client + Server
Added basic server and client with sighandler. Modified client to use fork() then modified that to select().

### 2026-01-08 - Client + UI
Completed server using select(). Refactored ui.c into separate functions called in client and added keyboard input display logic to client.

### 2026-01-09 - Minor Mods + Basic Chat History
Modified makefile and added error checks for select(). Implemented a basic janky chat history to display messages sent from other clients.

### 2026-01-11 - Fix Bug
Fixed very minor bug fix in client that prevented clients on different machines from connecting properly.

### 2026-01-12 - Message Struct
Completed helper functions for struct + minor fixes to struct.

