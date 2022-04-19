/*
** EPITECH PROJECT, 2022
** auth_cmd.c
** File description:
** .
*/

#include "server.h"

// Note anonymous user is hardcoded
int user_cmd(client_t *client, request_t request)
{
    if (client->logged_in)
        return send_response(client->fd, "230", "User logged in, proceed");
    if (!strcmp(request.args, "Anonymous")) {
        client->state = AUTH_PASS_NEEDED;
        return send_response(client->fd, "331", "User name okay, need password.");
    }
    if (client->state == AUTH_PASS_NEEDED) {
        client->state = AUTH_NEEDED;
        return send_response(client->fd, "503", "Bad sequence of commands");
    }
    return send_response(client->fd, "530", "Not logged in"); // Not sure about this one
}

// Note anonymous user is hardcoded
int pass_cmd(client_t *client, request_t request)
{
    if (client->logged_in)
        return send_response(client->fd, "230", "User logged in, proceed");
    if (client->state != AUTH_PASS_NEEDED)
        return send_response(client->fd, "503", "Bad sequence of commands");
    else if (!strcmp(request.args, "")) {
        client->logged_in = 1;
        client->state = NOTHING;
        return send_response(client->fd, "230", "User logged in, proceed");
    } else {
        client->state = AUTH_NEEDED;
        return send_response(client->fd, "530", "Not logged in.");
    }
}
