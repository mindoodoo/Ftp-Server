/*
** EPITECH PROJECT, 2022
** response.c
** File description:
** .
*/

#include "server.h"

int send_response(int client_fd, char *code, char *msg)
{
    // Not sure that the multiple consecutive writes work as intended, but let's try it
    write(client_fd, code, strlen(code));
    write(client_fd, " ", 1);
    write(client_fd, msg, strlen(msg));
    write(client_fd, "\r\n", 2);
    return 0;
}
