/*
** EPITECH PROJECT, 2022
** cmd_handling.c
** File description:
** .
*/

#include "server.h"

client_t *handle_connections(int server_fd, client_t *client_list, char *cwd)
{
    client_t *new_client = create_client(cwd);

    new_client->fd = accept(server_fd,
    (struct sockaddr *)&new_client->client_sock, &new_client->sock_len);
    if (new_client->fd == -1) {
        ERR("Accepting incoming connection has failed\n");
        return client_list;
    } else {
        client_list = push(client_list, new_client);
        send_response(new_client->fd, "220", 1, "Service ready for new user");
    }
    return client_list;
}

int process_request(client_t *client, request_t request)
{
    cmd_t commands[] = {
        "user", &user_cmd,
        "pass", &pass_cmd,
        "noop", &noop_cmd,
        "help", &usage_cmd,
        "cwd", &cwd_cmd,
        "pwd", &pwd_cmd,
        "NULL", NULL
    };

    for (int i = 0; commands[i].ptr; i++)
        if (!strcmp(request.prefix, commands[i].name))
            return commands[i].ptr(client, request);
    return -1;
}

client_t *client_handling(client_t *client_list, fd_set *readfds,
int nfds)
{
    int cmd_ret = 0;
    int ret = 1;
    char *raw = calloc(4096, sizeof(char));
    client_t *head = client_list;
    request_t request;

    while (head) {
        if (FD_ISSET(head->fd, readfds)) {
            ret = read(head->fd, raw, 4096);
            if (!ret) {
                client_list = pop(head, client_list);
                head = client_list;
                continue;
            }
            request = parse_request(raw);
            if (request.valid) {
                if ((cmd_ret = process_request(head, request)) < 0)
                    send_response(head->fd, "500", 1, "Synthaxe Error, command unrecognized.");
            } else
                send_response(head->fd, "500", 1, "Synthaxe Error, command unrecognized.");
            free(request.args);
            free(request.prefix);
        }
        head = head->next;
    }
    free(raw);
    return client_list;
}

int select_loop(int nfds, char *cwd, int server_fd)
{
    fd_set readfds[100];
    client_t *client_list = NULL;
    client_t *head = NULL;

    while (1) {
        head = client_list;
        FD_ZERO(readfds);
        FD_SET(server_fd, readfds);
        while (head) {
            FD_SET(head->fd, readfds);
            head = head->next;
        }
        if (select(nfds, readfds, NULL, NULL, NULL)) {
            client_list = client_handling(client_list, readfds, nfds);
            // Check for incoming connections
            if (FD_ISSET(server_fd, readfds))
                client_list = handle_connections(server_fd, client_list, cwd);
        }
    }
    return 0;
}
