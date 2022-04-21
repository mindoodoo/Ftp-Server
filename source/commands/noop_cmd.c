/*
** EPITECH PROJECT, 2022
** noop_cmd.c
** File description:
** .
*/

#include "server.h"

int noop_cmd(client_t *client, request_t request)
{
    if (!client->logged_in)
        return send_response(client->fd, "530", "Not logged in.");
    return send_response(client->fd, "200", "Command okay.");
}
