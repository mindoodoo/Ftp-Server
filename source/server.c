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
    int nfds = 100;
    char *real_path = realpath(path, NULL);

    if (!cmd_fd)
        return 1;
    select_loop(nfds, real_path, cmd_fd);
    free(real_path);
}
