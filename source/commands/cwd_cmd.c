/*
** EPITECH PROJECT, 2022
** cwd_cmd.c
** File description:
** .
*/

#include "server.h"

int cwd_cmd(client_t *client, request_t request)
{
    struct stat sb;
    char *new_path = NULL;

    if (!client->logged_in)
        return send_response(client->fd, "530", 1, "Not logged in.");
    if (request.args[0] == '\0')
        return send_response(client->fd, "501", 1, "Synthaxe error in params or args");
    chdir(client->cwd);
    new_path = realpath(request.args, NULL);
    if (stat(new_path, &sb) < 0) {
        free(new_path);
        return send_response(client->fd, "550", 1, "File action not taken. (File not found)");
    } else if (!S_ISDIR(sb.st_mode)) {
        free(new_path);
        return send_response(client->fd, "550", 1, "File action not taken. (File not found)");
    }
    free(client->cwd);
    client->cwd = new_path;
    return send_response(client->fd, "250", 1, "Requested file action okay, completed");
}

int pwd_cmd(client_t *client, request_t request)
{
    if (!client->logged_in)
        return send_response(client->fd, "530", 1, "Not logged in.");
    return send_response(client->fd, "257", 1, client->cwd);
}