/*
** EPITECH PROJECT, 2022
** csv.cpp
** File description:
** .
*/

#include "server.h"

// Setup, bind and listen on new socket
int setup_cmd_socket(int port)
{
    int cmd_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    socklen_t sock_len = sizeof(server_addr);
    int opt = 1;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = ntohs(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    setsockopt(cmd_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // Allow reuse
    if (bind(cmd_fd, (struct sockaddr *)&server_addr, sock_len) < 0) {
        ERR("Server command socket binding failed\n");
        return 0;
    }
    if (listen(cmd_fd, 10) == -1) {
        ERR("Server command socket listening failed\n");
        return 0;
    }
    return cmd_fd;
}

struct pollfd *init_poll_fds(int count, int server_fd)
{
    struct pollfd *poll_fds = calloc(count, sizeof(struct pollfd));

    for (int i = 0; i < count; i++) {
        poll_fds[i].fd = -1;
        poll_fds[i].events = POLLIN;
    }
    poll_fds[0].fd = server_fd;
    return poll_fds;
}

int handle_connections()
{

}

int poll_loop(struct pollfd *poll_fds, nfds_t nfds)
{
    int poll_ret = 0;
    
    while (1) {
        if ((poll_ret = poll(poll_fds, nfds, -1))) {
            // Check if activity on cmd socket
            if (poll_fds[0].revents)

        }
    }
}

// Main function of the server
int my_ftp(int port, char *path)
{
    int cmd_fd = setup_cmd_socket(port);
    nfds_t nfds = 10;
    struct pollfd *poll_fds = NULL;

    if (!cmd_fd)
        return 1;
    poll_fds = init_poll_fds(nfds, cmd_fd);
    poll_loop(poll_fds, nfds);
}