/*
** EPITECH PROJECT, 2022
** client_list.c
** File description:
** .
*/

#include "server.h"

client_t *push(client_t *head, client_t *new_client)
{
    if (!new_client)
        return head;
    if (!head)
        return new_client;
    new_client->next = head;
    head->previous = new_client;
    return new_client;
}

client_t *pop(client_t *client, client_t *list_head)
{
    client_t *previous = client->previous;
    client_t *next = client->next;

    if (next)
        next->previous = previous;
    if (previous)
        previous->next = next;
    free(client);
    if (!previous)
        return next;
    else
        return list_head;
}

client_t *find_client(int fd, client_t *head)
{
    client_t *temp_head = head;

    while (head) {
        if (temp_head->fd = fd)
            return temp_head;
        temp_head = temp_head->next;
    }
    return NULL;
}

client_t *create_client(char *cwd)
{
    client_t *new = malloc(sizeof(client_t));

    new->sock_len = sizeof(struct sockaddr_in);
    new->original_cwd = cwd;
    new->cwd = strdup(cwd);
    new->previous = NULL;
    new->next = NULL;
    new->fd = 0;
    new->logged_in = 0;
    new->state = AUTH_NEEDED;
    return new;
}
