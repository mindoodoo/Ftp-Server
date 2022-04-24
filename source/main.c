/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** .
*/

#include "server.h"

void display_usage()
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home ");
    printf("directory for the Anonymour user\n");
}

// Returns -1 if main needs to exit without error
// Returns 1 if main needs to exit with error
// Returns 0 otherwise
int check_args(int ac, char **av)
{
    struct stat sb;

    if (ac == 2 && !strcmp(av[1], "-help")) {
        display_usage();
        return -1;
    }
    if (ac != 3) {
        printf("Invalid number of arguments\n");
        return 1;
    }
    if (stat(av[2], &sb) == -1 || !S_ISDIR(sb.st_mode)) {
        printf("Invalid filepath for home folder...\n");
        return 1;
    } else
        return 0;
}

int main(int ac, char **av)
{
    int arg_check = 0;

    if ((arg_check = check_args(ac, av)) == -1)
        return 0;
    else if (arg_check == 1)
        return 84;
    else {
        printf("Starting my_ftp ftp server...\n");
        if (my_ftp(atoi(av[1]), av[2]))
            return 84;
        else
            return 0;
    }
}
