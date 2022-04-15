##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## .
##

CFLAGS = -I./include

SERVER_SRC = server.c

CLIENT_SRC = client.c

all: server client clean

client:
	gcc -o client $(CLIENT_SRC) $(CFLAGS)

server:
	gcc	-o server $(SERVER_SRC) $(CFLAGS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf server
	rm -rf client

re: fclean all

.PHONY: re fclean clean