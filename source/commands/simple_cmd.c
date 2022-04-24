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

int passv_cmd(client_t *client, request_t request)
{
    int ip1 = 127;
    int ip2 = 0;
    int ip3 = 0;
    int ip4 = 1;
    int p1 = 50;
    int p2 = 47;

    if (!client->logged_in)
        return send_response(client->fd, "530", 1, "Not logged in.");
    client->passive_mode = 1;
    dprintf(client->fd, "227 %d,%d,%d,%d,%d,%d\r\n", ip1, ip2, ip3, ip4, p1, p2);
    return 0;
}
