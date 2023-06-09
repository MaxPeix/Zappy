/*
** EPITECH PROJECT, 2023
** core_server
** File description:
** core
*/

#include "server.h"

void handle_client_request(client_t *clients, char *buffer,
    int i, server_params_t *server_params)
{
    char **args = NULL;
    if (buffer && strlen(buffer) > 0) {
        args = get_args_from_buffer(buffer);
        handle_command(&clients[i], server_params, args);
        handle_command_with_player_nbr(clients,
            &clients[i], server_params, args);
        handle_broadcast_command(clients, &clients[i], args);
        handle_eject_command(clients, &clients[i], server_params, args);
    }
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
        if (!buffer)
            return;
        buffer[valread] = '\0';
        handle_client_request(clients, buffer, i, server_params);
    }
}
