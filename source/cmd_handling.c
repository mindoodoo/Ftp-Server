/*
** EPITECH PROJECT, 2022
** cmd_handling.c
** File description:
** .
*/

#include "server.h"

client_t *handle_connections(int server_fd, client_t *client_list,
struct pollfd *poll_fds)
{
    client_t *new_client = create_client();
    int fd_index;

    new_client->fd = accept(server_fd,
    (struct sockaddr *)&new_client->client_sock, &new_client->sock_len);
    if (new_client->fd == -1) {
        ERR("Accepting incoming connection has failed\n");
        return client_list;
    } else {
        client_list = push(client_list, new_client);
        send_response(new_client->fd, "220", "Service ready for new user");
    }
    for (fd_index = 0; poll_fds[fd_index].fd != -1; fd_index++);
    poll_fds[fd_index].fd = new_client->fd;
    return client_list;
}

int process_request(client_t *client, request_t request)
{
    cmd_t commands[] = {
        "user", &user_cmd,
        "NULL", NULL
    };

    for (int i = 0; commands[i].ptr; i++)
        if (!strcmp(request.prefix, commands[i].name))
            return commands[i].ptr(client, request);
    return -1;
}

client_t *client_handling(client_t *client_list, struct pollfd *poll_fds,
int nfds)
{
    int cmd_ret = 0;
    char *raw = calloc(4096, sizeof(char));
    client_t *client = NULL;
    request_t request;

    for (int i = 0; i < nfds; i++)
        // Note this does not handle client disconnection
        if (poll_fds[i].revents & POLLIN) {
            if (!(client = find_client(poll_fds[i].fd, client_list)))
                continue;
            read(client->fd, raw, 4096);
            request = parse_request(raw);
            if (request.valid) {
                if ((cmd_ret = process_request(client, request)) < 0)
                    send_response(client->fd, "500", "Synthaxe Error, command unrecognized.");
                // Add else for client request to disconnect    
            } else
                send_response(client->fd, "500", "Synthaxe Error, command unrecognized.");
        }
    free(raw); // Is reuse good idea ?
    return client_list;
}

int poll_loop(struct pollfd *poll_fds, nfds_t nfds)
{
    int poll_ret = 0;
    client_t *client_list = NULL;
    
    while (1) {
        if ((poll_ret = poll(poll_fds, nfds, -1))) {
            client_list = client_handling(client_list, poll_fds, nfds);
            // Check for incoming connections
            if (poll_fds[0].revents)
                client_list = handle_connections(poll_fds[0].fd, client_list, poll_fds);
        }
    }
}
