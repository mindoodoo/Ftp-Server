/*
** EPITECH PROJECT, 2022
** server.c
** File description:
** .
*/

#include "server.h"

int main()
{
    // Initialize socket
    // AF_INET = IPV4
    // SOCK_STREAM = TCP
    // 0 = Default protocol for arg 2
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr; // Socket address
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(8888); // Diff alex a ntohs
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t addrSize = sizeof(addr);

    int opt = 1;

    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind socket to internet address
    if (bind(socket_fd, (struct sockaddr *)&addr, addrSize) < 0)
        printf("Socket bind failed\n");
    else
        printf("Succesfully bound socket with file descriptor : %d\n", socket_fd);

    // Marks socket fd as passive and listens for incoming connections
    // First arg is fd, second arg is queue length
    if (listen(socket_fd, 10) == -1)
        printf("Listen failed\n");

    // Variables to store information on incoming connection
    struct sockaddr_in addrIncoming; // Socket address struct for incoming connection
    int size = sizeof(addrIncoming);
    int client_fd = -1;

    char *msg = "Hello client !";

    while (1) {
        // Accept one (first) connection
        if ((client_fd = accept(socket_fd, (struct sockaddr *)&addrIncoming, &size)) < 0)
            printf("Accepting first connection failed\n");
        else
            printf("Incoming connection is : %s\nFrom port : %u\n", inet_ntoa(addrIncoming.sin_addr),
            ntohs(addrIncoming.sin_port));

        write(client_fd, msg, strlen(msg));

        close(client_fd);
    }

    close(socket_fd);
}