/*
** EPITECH PROJECT, 2023
** handle_command
** File description:
** handle_command
*/

#include "server.h"

void handle_command_two(int client_socket, char **args)
{
    if (args[0] == NULL) {
        send_response(client_socket, "Zappy: Invalid command.\n");
        return;
    }
    if (strcasecmp(args[0], "INVENTORY") == 0) {
        send_response(client_socket, "Zappy: Inventory.\n");
        return;
    }
    send_response(client_socket, "Zappy: Invalid command.\n");
}

void handle_command(client_t *clients, int index, char *buffer)
{
    char **args = get_args_from_client(buffer);
    int client_socket = clients[index].socket;

    if (!args || !args[0]) {
        send_response(client_socket, "Zappy: Invalid command.\n");
        return;
    }
    if (strcasecmp(args[0], "HELP") == 0) {
        send_response(client_socket, "Zappy: Help message.\n");
        return;
    }
    if (strcasecmp(args[0], "QUIT") == 0) {
        send_response(client_socket, "Goodbye.\n");
        handle_disconnect(clients, client_socket, index);
        return;
    }
    handle_command_two(client_socket, args);
}
