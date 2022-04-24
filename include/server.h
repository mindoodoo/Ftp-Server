/*
** EPITECH PROJECT, 2022
** server.h
** File description:
** .
*/

#pragma once


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <sys/stat.h>
#include <libgen.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define ERR(msg) fprintf(stderr, msg);

// State macros for client / server exchanges
#define NOTHING 0;
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
    int port;
} client_t;

typedef struct request_s {
    int valid;
    char *prefix;
    char *args;
} request_t;

typedef struct cmd_s {
    char *name;
    int (*ptr)(client_t *, request_t);
} cmd_t;

// Core
int my_ftp(int port, char *path);

// Cmd handling
int select_loop(int nfds, char *cwd, int server_fd);

// Commands
    // auth cmds
int user_cmd(client_t *client, request_t request);
int pass_cmd(client_t *client, request_t request);

    // simple cmds
int noop_cmd(client_t *client, request_t request);
int usage_cmd(client_t *client, request_t request);
int quit_cmd(client_t *client, request_t request);
int port_cmd(client_t *client, request_t request);

    // cwd cmds
int cwd_cmd(client_t *client, request_t request);
int pwd_cmd(client_t *client, request_t request);
int cdup_cmd(client_t *client, request_t request);

// Response
int send_response(int client_fd, char *code, int n_lines, ...);

// Parsing
request_t parse_request(char *raw);

// Utilities
int setup_cmd_socket(int port);
int table_len(char **table);
void free_table(char **table);
char *str_to_lowcase(char *str);

// Client linked list
client_t *push(client_t *head, client_t *new_client);
client_t *pop(client_t *client, client_t *list_head);
client_t *find_client(int fd, client_t *head);
client_t *create_client(char *cwd);
