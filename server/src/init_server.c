/*
** EPITECH PROJECT, 2023
** init_server
** File description:
** init_server
*/

#include "server.h"

int create_and_bind_socket(char **argv, struct sockaddr_in *address)
{
    if (!argv || !argv[1] || !address)
        return -1;
    int server_socket;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        return -1;
    }

    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(atoi(argv[1]));

    if (bind(server_socket,
        (struct sockaddr *)address, sizeof(*address)) < 0) {
        perror("bind failed");
        return -1;
    }

    return server_socket;
}
