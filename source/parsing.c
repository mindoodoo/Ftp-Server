/*
** EPITECH PROJECT, 2022
** parsing.c
** File description:
** .
*/

#include "server.h"

char **split_str(char *str, char *sep)
{
    char *save_pointer = NULL;
    char **output = NULL;
    char *token = NULL;
    int size = 0;
    int index = 0;

    for (int i = 0; str[i]; i++)
        if (!strncmp(&str[i], sep, strlen(sep)))
            size++;
    output = calloc(size + 2, sizeof(char *));
    output[0] = NULL;
    token = strtok_r(str, sep, &save_pointer);
    while (token) {
        if (token) {
            output[index] = strdup(token);
            output[index + 1] = NULL;
            index++;
        }
        token = strtok_r(NULL, sep, &save_pointer);
    }
    return output;
}

request_t parse_request(char *raw)
{
    request_t output;
    char **split_msg = NULL;
    char *msg = NULL;

    if (!(msg = strtok(raw, "\r\n"))) {
        output.valid = 0;
        return output;
    }
    split_msg = split_str(msg, " ");
    if (table_len(split_msg) < 1 || strlen(split_msg[0]) != 4 ||
    table_len(split_msg) > 2) {
        output.valid = 0;
        return output;
    }
    output.valid = 1;
    output.prefix = strdup(str_to_lowcase(split_msg[0]));
    if (table_len(split_msg) < 2)
        output.args = strdup("");
    else
        output.args = strdup(split_msg[1]);
    free_table(split_msg);
    return output;
}