/*
** EPITECH PROJECT, 2022
** response.c
** File description:
** .
*/

#include "server.h"

int send_response(int client_fd, char *code, int n_lines, ...)
{
    va_list args;
    char *msg = NULL;

    va_start(args, n_lines);
    for (int i = n_lines - 1; i >= 0; i--) {
        msg = va_arg(args, char *);
        if (i == 0)
            dprintf(client_fd, "%s %s\r\n", code, msg);
        else
            dprintf(client_fd, "%s-%s\r\n", code, msg);
    }
    return 0;
}
