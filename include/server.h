/*
** EPITECH PROJECT, 2022
** server.h
** File description:
** .
*/

#pragma once

#include <sys/stat.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

#define ERR(msg) fprintf(stderr, msg);

// State macros for client / server exchanges
#define NOTHING 0; // Used when client in no specific state
#define AUTH_NEEDED 1
#define AUTH_PASS_NEEDED 2

typedef struct client_s {
    int fd;
    struct sockaddr_in client_sock;
    int sock_size;
    int state;
    struct client_s *next;
    struct client_s *previous;
} client_t;

int my_ftp(int port, char *path);

// Client linked list
client_t *push(client_t *head, client_t *new_client);
void pop(client_t *client);
client_t *find_client(int fd, client_t *head);
client_t *create_client();
