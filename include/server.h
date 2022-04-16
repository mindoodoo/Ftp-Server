/*
** EPITECH PROJECT, 2022
** server.h
** File description:
** .
*/

#pragma once

#include <sys/stat.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ERR(msg) fprintf(stderr, msg);

int my_ftp(int port, char *path);
