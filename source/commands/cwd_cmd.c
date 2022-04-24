/*
** EPITECH PROJECT, 2022
** cwd_cmd.c
** File description:
** .
*/

#include "server.h"

int cwd_cmd2(char *new_path, client_t *client)
{
    struct stat sb;

    if (stat(new_path, &sb) < 0) {
        free(new_path);
        return send_response(client->fd, "550", 1,
        "File action not taken. (File not found)");
    } else if (!S_ISDIR(sb.st_mode)) {
        free(new_path);
        return send_response(client->fd, "550", 1,
        "File action not taken. (File not found)");
    }
    return 1;
}

int cwd_cmd(client_t *client, request_t request)
{
    struct stat sb;
    char *new_path = NULL;

    if (!client->logged_in)
        return send_response(client->fd, "530", 1, "Not logged in.");
    if (request.args[0] == '\0')
        return send_response(client->fd, "501", 1,
        "Synthaxe error in params or args");
    chdir(client->cwd);
    new_path = realpath(request.args, NULL);
    if (!cwd_cmd2(new_path, client))
        return 0;
    free(client->cwd);
    client->cwd = new_path;
    return send_response(client->fd, "250", 1,
    "Requested file action okay, completed");
}

int pwd_cmd(client_t *client, request_t request)
{
    if (!client->logged_in)
        return send_response(client->fd, "530", 1, "Not logged in.");
    return send_response(client->fd, "257", 1, client->cwd);
}

int cdup_cmd(client_t *client, request_t request)
{
    char *new_path = NULL;

    if (!client->logged_in)
        return send_response(client->fd, "530", 1, "Not logged in.");
    new_path = realpath(dirname(client->cwd), NULL);
    free(client->cwd);
    client->cwd = new_path;
    return send_response(client->fd, "200", 1, "Command Ok..");
}
