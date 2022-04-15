##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## .
##

CFLAGS = -I./include

SERVER_SRC = source/main.c

all: server clean

server:
	gcc	-o myftp $(SERVER_SRC) $(CFLAGS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf myftp

re: fclean all

.PHONY: re fclean clean