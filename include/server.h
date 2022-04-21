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
#include <ctype.h>
#include <unistd.h>
#include <stdarg.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <poll.h>

#define ERR(msg) fprintf(stderr, msg);

// State macros for client / server exchanges
#define NOTHING 0; // Used when client in no specific state
#define AUTH_NEEDED 1
#define AUTH_PASS_NEEDED 2

typedef struct client_s {
    int fd;
    int logged_in;
    struct sockaddr_in client_sock;
    socklen_t sock_len;
    int state;
    char *original_cwd;
    char *cwd;
    struct client_s *next;
    struct client_s *previous;
} client_t;

typedef struct request_s {
    int valid;
    char *prefix; // This may cause segfault depending on implementation
    char *args;
} request_t;

typedef struct cmd_s {
    char *name;
    int (*ptr)(client_t *, request_t);
} cmd_t;

// Core
int my_ftp(int port, char *path);

// Cmd handling
int poll_loop(struct pollfd *poll_fds, nfds_t nfds, char *cwd);

// Commands
int user_cmd(client_t *client, request_t request);
int pass_cmd(client_t *client, request_t request);

int noop_cmd(client_t *client, request_t request);
int usage_cmd(client_t *client, request_t request);

int cwd_cmd(client_t *client, request_t request);

// Response
int send_response(int client_fd, char *code, int n_lines, ...);

// Parsing
request_t parse_request(char *raw);

// Utilities
int setup_cmd_socket(int port);
struct pollfd *init_poll_fds(int count, int server_fd);
int table_len(char **table);
void free_table(char **table);
char *str_to_lowcase(char *str);

// Client linked list
client_t *push(client_t *head, client_t *new_client);
void pop(client_t *client);
client_t *find_client(int fd, client_t *head);
client_t *create_client(char *cwd);
