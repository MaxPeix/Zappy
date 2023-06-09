/*
** EPITECH PROJECT, 2023
** handle_command
** File description:
** handle_command
*/

#include "server.h"
#include <stdbool.h>

bool handle_command_four(client_t *client, server_params_t *server_params, char **args)
{
    if (strcasecmp(args[0], "BCT") == 0) {
        print_bct(server_params, client, args);
        return true;
    }
    if (strcasecmp(args[0], "FORWARD") == 0) {
        handle_forward_command(client, args);
        return true;
    }
    if (strcasecmp(args[0], "RIGHT") == 0) {
        handle_right_command(client, args);
        return true;
    }
    if (strcasecmp(args[0], "LEFT") == 0) {
        handle_left_command(client, args);
        return true;
    }
    return false;
}

bool handle_command_three(client_t *client, server_params_t *server_params, char **args)
{
    if (strcasecmp(args[0], "SGT") == 0) {
        print_sgt(server_params, client);
        return true;
    }
    if (strcasecmp(args[0], "MCT") == 0) {
        print_mct(server_params, client);
        return true;
    }
    if (strcasecmp(args[0], "MSZ") == 0) {
        print_msz(server_params, client);
        return true;
    }
    if (strcasecmp(args[0], "TNA") == 0) {
        print_tna(server_params, client);
        return true;
    }
    if (handle_command_four(client, server_params, args) == true)
        return true;
    return false;
}

bool handle_command_two(client_t *client, server_params_t *server_params, char **args)
{
    if (strcasecmp(args[0], "INVENTORY") == 0) {
        print_inventory(server_params, client);
        return true;
    }
    if (strcasecmp(args[0], "GRAPHIC") == 0) {
        handle_graphic_command(client, server_params);
        return true;
    }
    if (handle_command_three(client, server_params, args) == true)
        return true;
    return false;
}

void handle_command(client_t *client, server_params_t *server_params, char **args)
{
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
    if (handle_command_two(client, server_params, args) == true)
        return;
    else
        send_response(client_socket, "ko\n");
}
