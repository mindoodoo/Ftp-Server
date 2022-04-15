/*
** EPITECH PROJECT, 2022
** my_ftp
** File description:
** server
*/

#include <stddef.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <poll.h>

int main(int ac, char **av)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    struct sockaddr_in new_client_address;

    int opt = 1;

    size_t server_addr_size = sizeof(server_address);
    size_t new_client_addr_size = sizeof(new_client_address);
    size_t max_conn = 8;
    
    int client_fd;

    if (ac != 2) {
        return 84;
    }
    if (server_fd == -1) {
        perror("socket failed.");
        return 84;
    }
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    server_address.sin_family = AF_INET;
    server_address.sin_port = ntohs(strtol(av[1], NULL, 0));
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    
    if (bind(server_fd, (struct sockaddr *)&server_address, server_addr_size)) {
        perror("socket name binding failed.");
        close(server_fd);
        return 84;
    }
    printf("listening on: %s:%i\n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));
    if (listen(server_fd, 8) == -1) {
        perror("listen");
        close(server_fd);
        return 84;
    }
    client_fd = accept(server_fd, (struct sockaddr *)&new_client_address, (socklen_t *)&new_client_addr_size);
    write(client_fd, "Hello world !\n", 15);
    printf("Hello message sent\n");

    close(server_fd);
    close(client_fd);
    
    return 0;
}
