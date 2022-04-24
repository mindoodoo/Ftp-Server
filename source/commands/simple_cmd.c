/*
** EPITECH PROJECT, 2022
** noop_cmd.c
** File description:
** .
*/

#include "server.h"

int noop_cmd(client_t *client, request_t request)
{
    return send_response(client->fd, "200", 1, "Command okay.");
}

int usage_cmd(client_t *client, request_t request)
{
    return send_response(client->fd, "214", 1, "This is the usage");
}

int quit_cmd(client_t *client, request_t request)
{
    send_response(client->fd, "221", 1, "Service closing control connection");
    return 1;
}

int port_cmd(client_t *client, request_t request)
{
    if (!client->logged_in)
        return send_response(client->fd, "530", 1, "Not logged in.");
    if (request.args[0] == '\0' || (client->port = atol(request.args)) <= 0)
        return send_response(client->fd, "501", 1, "Synthaxe error in params or args");
    return send_response(client->fd, "200", 1, "Command Ok.");
}
