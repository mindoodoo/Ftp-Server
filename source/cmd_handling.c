/*
** EPITECH PROJECT, 2022
** cmd_handling.c
** File description:
** .
*/

#include "server.h"

client_t *handle_connections(int server_fd, client_t *client_list)
{
    client_t *new_client = create_client();

    new_client->fd = accept(server_fd,
    (struct sockaddr *)&new_client->client_sock, &new_client->sock_size);
    if (new_client->fd == -1) {
        ERR("Accepting incoming connection has failed\n");
        return client_list;
    } else
        return push(client_list, new_client);
}

int poll_loop(struct pollfd *poll_fds, nfds_t nfds)
{
    int poll_ret = 0;
    client_t *client_list = NULL;
    
    while (1) {
        if ((poll_ret = poll(poll_fds, nfds, -1))) {
            // Check for incoming connections
            if (poll_fds[0].revents)
                client_list = handle_connections(poll_fds[0].fd, client_list);
        }
    }
}
