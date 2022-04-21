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
    return send_response(client->fd, "214", 14,
    "USER <SP> <username> <CRLF>   : Specify user for authentication",
    "PASS <SP> <password> <CRLF>   : Specify password for authentication",
    "CWD  <SP> <pathname> <CRLF>   : Change working directory",
    "CDUP <CRLF>                   : Change working directory to parent directory",
    "QUIT <CRLF>                   : Disconnection",
    "DELE <SP> <pathname> <CRLF>   : Delete file on the server",
    "PWD  <CRLF>                   : Print working directory",
    "PASV <CRLF>                   : Enable \"passive\" mode for data transfer",
    "PORT <SP> <host-port> <CRLF>  : Enable \"active\" mode for data transfer",
    "HELP [<SP> <string>] <CRLF>   : List available commands",
    "NOOP <CRLF>                   : Do nothing",
    "RETR <SP> <pathname> <CRLF>   : Download file from server to client",
    "STOR <SP> <pathname> <CRLF>   : Upload file from client to server",
    "LIST [<SP> <pathname>] <CRLF> : List files in the current working directory");
}
