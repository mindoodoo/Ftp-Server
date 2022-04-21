##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## .
##

CFLAGS = -I./include -g3

SERVER_SRC = source/main.c \
	source/server.c \
	source/client_list.c \
	source/cmd_handling.c \
	source/utilities.c \
	source/parsing.c \
	source/response.c \
	source/commands/auth_cmd.c \
	source/commands/simple_cmd.c

all: server clean

server:
	gcc	-o myftp $(SERVER_SRC) $(CFLAGS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf myftp

re: fclean all

.PHONY: re fclean clean