/*
** EPITECH PROJECT, 2022
** csv.cpp
** File description:
** .
*/

#include "server.h"

// Main function of the server
int my_ftp(int port, char *path)
{
    int cmd_fd = setup_cmd_socket(port);
    nfds_t nfds = 10;
    struct pollfd *poll_fds = NULL;

    if (!cmd_fd)
        return 1;
    poll_fds = init_poll_fds(nfds, cmd_fd);
    poll_loop(poll_fds, nfds, path);
}