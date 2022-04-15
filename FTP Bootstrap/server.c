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
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr; // Socket address
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(8888); // Diff alex a ntohs
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t addrSize = sizeof(addr);

    int opt = 1;

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind socket to internet address
    if (bind(server_fd, (struct sockaddr *)&addr, addrSize) < 0)
        printf("Socket bind failed\n");
    else
        printf("Succesfully bound socket with file descriptor : %d\n", server_fd);

    // Marks socket fd as passive and listens for incoming connections
    // First arg is fd, second arg is queue length
    if (listen(server_fd, 10) == -1)
        printf("Listen failed\n");

    // Variables to store information on incoming connection
    struct sockaddr_in addrIncoming; // Socket address struct for incoming connection
    int size = sizeof(addrIncoming);
    int client_fd = -1;

    char *msg = "Hello client !\n";

    // Poll call variables
    struct pollfd *fds = calloc(10, sizeof(struct pollfd));
    nfds_t nfds = 10;
    int fd_index = 1;
    int poll_ret = 0;

    // Init fds array
    for (int i = 0; i < nfds; i++) {
        fds[i].fd = -1;
        fds[i].events = POLLIN;
    }

    fds[0].fd = server_fd;

    printf("Starting polling...\n");
    while (1) {
        poll_ret = poll(fds, nfds, -1);

        if (poll_ret) {
            // Check if new connection to accept
            if (fds[0].revents & POLLIN) {
                fds[fd_index].fd = accept(server_fd, (struct sockaddr*) &addrIncoming, &size);
                fd_index;
                write(fds[fd_index].fd, msg, strlen(msg));
            }
        }
    }

    close(server_fd);
}