/*
** EPITECH PROJECT, 2023
** zappy main$
** File description:
** main
*/

#include "server.h"

int main(int argc, char **argv)
{
    int errorChecked = check_errors(argc, argv);
    if (errorChecked == 84)
        return EPITECH_ERROR;
    if (errorChecked == 1)
        return 0;
    int server_socket;
    client_t *clients = malloc(sizeof(client_t) * MAX_CLIENTS);
    struct sockaddr_in address;
    init_clients_list(clients);
    server_socket = create_and_bind_socket(argv, &address);
    if (server_socket == -1)
        return EPITECH_ERROR;
    if (listen(server_socket, 3) < 0) {
        perror("listen failed");
        return EPITECH_ERROR;
    }
    printf("Waiting for connections...\n");
    wait_for_connections(server_socket, clients, address);
    return 0;
}
