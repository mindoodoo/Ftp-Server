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

// Crash serveral successive connections
// Crash only one process for several clients
