/*
** EPITECH PROJECT, 2023
** handle_command
** File description:
** handle_command
*/

#include "server.h"

void handle_command_three(client_t *client, server_params_t *server_params,
    char **args)
{
    if (strcasecmp(args[1], "sgt\n") == 0) {
        print_sgt(server_params, client);
        return;
    }
    if (strcasecmp(args[1], "mct\n") == 0) {
        print_mct(server_params, client);
        return;
    }
    if (strcasecmp(args[1], "msz\n") == 0) {
        print_msz(server_params, client);
        return;
    }
    if (strcasecmp(args[1], "tna\n") == 0) {
        print_tna(server_params, client);
        return;
    }
    if (strcasecmp(args[1], "bct\n") == 0) {
        print_bct(server_params, client, args);
        return;
    }
    send_response(client->socket, "ko\n");
}

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
    handle_command_three(client, server_params, args);
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
