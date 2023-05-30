/*
** EPITECH PROJECT, 2023
** core_server
** File description:
** core
*/

#include "server.h"

void handle_disconnect(client_t *clients, int socket, int index)
{
    close(socket);
    clients[index].socket = 0;
}

void handle_client_request(client_t *clients, int index,
    char *buffer, int buffer_size)
{
    if (!buffer)
        return;
    buffer[buffer_size] = '\0';
    if (buffer && strlen(buffer) > 0)
        handle_command(clients, index, buffer);
}

void check_client_activity(client_t *clients,
    int server_socket, fd_set *readfds)
{
    int client_socket = 0;
    int valread = 0;
    char buffer[BUFFER_SIZE];

    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_socket = clients[i].socket;

        if (!FD_ISSET(client_socket, readfds))
            continue;
        if ((valread = read(client_socket, buffer, BUFFER_SIZE)) == 0) {
            handle_disconnect(clients, client_socket, i);
            continue;
        }
        handle_client_request(clients, i, buffer, valread);
    }
}
