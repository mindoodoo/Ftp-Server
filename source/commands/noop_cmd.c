//
// Created by mindoo on 19.04.22.
//

#include "server.h"

int noop_cmd(client_t *client)
{
    if (!client->logged_in)
        return send_response(client->fd, "530", "Not logged in.");
    return send_response(client->fd, "200", "Command okay.");
}
