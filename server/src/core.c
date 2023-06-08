/*
** EPITECH PROJECT, 2023
** core_server
** File description:
** core
*/

#include "server.h"

void handle_client_request(client_t *client, char *buffer,
    int buffer_size, server_params_t *server_params)
{
    if (!buffer)
        return;
    buffer[buffer_size] = '\0';
    if (buffer && strlen(buffer) > 0)
        handle_command(client, server_params, buffer);
}

void check_client_activity(client_t *clients,
    int server_socket, fd_set *readfds, server_params_t *server_params)
{
    int client_socket = 0;
    int valread = 0;
    char buffer[BUFFER_SIZE];

    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_socket = clients[i].socket;

        if (!FD_ISSET(client_socket, readfds))
            continue;
        if ((valread = read(client_socket, buffer, BUFFER_SIZE)) == 0) {
            handle_disconnect(&clients[i]);
            continue;
        }
        handle_client_request(&clients[i], buffer, valread, server_params);
    }
}
