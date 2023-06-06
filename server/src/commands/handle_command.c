/*
** EPITECH PROJECT, 2023
** handle_command
** File description:
** handle_command
*/

#include "server.h"

void handle_command_two(client_t *client, server_params_t *server_params,
    char **args)
{
    int client_socket = client->socket;

    if (args[0] == NULL) {
        send_response(client_socket, "ko\n");
        return;
    }
    if (strcasecmp(args[0], "INVENTORY") == 0) {
        send_response(client_socket, "Zappy: Inventory.\n");
        return;
    }
    if (strcasecmp(args[0], "GRAPHIC") == 0) {
        handle_graphic_command(client, server_params);
        return;
    }
    send_response(client_socket, "ko\n");
}

void handle_command(client_t *client, server_params_t *server_params,
    char *buffer)
{
    char **args = get_args_from_client(buffer);
    int client_socket = client->socket;

    if (!args || !args[0]) {
        send_response(client_socket, "ko\n");
        return;
    }
    if (strcasecmp(args[0], "HELP") == 0) {
        send_response(client_socket, "Zappy: Help message.\n");
        return;
    }
    if (strcasecmp(args[0], "QUIT") == 0) {
        send_response(client_socket, "Goodbye.\n");
        handle_disconnect(client);
        return;
    }
    handle_command_two(client, server_params, args);
}
