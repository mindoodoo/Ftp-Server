/*
** EPITECH PROJECT, 2022
** cwd_cmd.c
** File description:
** .
*/

#include "server.h"

int cwd_cmd(client_t *client, request_t request)
{
    if (!client->logged_in)
        return send_response(client->fd, "530", 1, "Not logged in.");
    client->cwd = request.args;
    return send_response(client->fd, "250", 1, "Requested file action okay, completed");
}