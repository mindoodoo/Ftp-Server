/*
** EPITECH PROJECT, 2022
** client.c
** File description:
** .
*/

#include "client.h"

int main()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    socklen_t len = sizeof(serverAddr);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = ntohs(8888);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (connect(socket_fd, (struct sockaddr*)&serverAddr, len))
        printf("Connection failed...\n");
    else
        printf("Connection succeeded !!\n");

    struct stat sb;
    char *msg = malloc(1024);

    while (1) {
        read(socket_fd, msg, 1024);
        printf("Msg is : %s\n", msg);
    }
}