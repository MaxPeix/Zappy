/*
** EPITECH PROJECT, 2023
** B-YEP-400-BDX-4-1-zappy-max.peixoto
** File description:
** placement_command.c
*/

#include "server.h"

static void handle_north_south(client_t *client, server_params_t *server_params)
{
    if (client->orientation == NORTH) {
        client->y_position = client->y_position - 1;
        if (client->y_position < 0)
            client->y_position = client->y_position + server_params->height;
    }
    if (client->orientation == SOUTH) {
        client->y_position = client->y_position + 1;
        if (client->y_position > server_params->height - 1)
            client->y_position = client->y_position - server_params->height;
    }
}

void handle_forward_command(server_params_t *server_params,
                            client_t *client,
                            char **args)
{
    if (strcasecmp(args[0], "FORWARD") != 0)
        return;
    handle_north_south(client, server_params);
    if (client->orientation == EAST) {
        client->x_position = client->x_position + 1;
        if (client->x_position > server_params->width - 1)
            client->x_position = client->x_position - server_params->width;
    }
    if (client->orientation == WEST) {
        client->x_position = client->x_position - 1;
        if (client->x_position < 0)
            client->x_position = client->x_position + server_params->width;
    }
    send_response(client->socket, "ok\n");
}

void handle_right_command(client_t *client, char **args)
{
    if (strcasecmp(args[0], "RIGHT") != 0)
        return;
    if (client->orientation == NORTH)
        client->orientation = EAST;
    else if (client->orientation == EAST)
        client->orientation = SOUTH;
    else if (client->orientation == SOUTH)
        client->orientation = WEST;
    else if (client->orientation == WEST)
        client->orientation = NORTH;
    send_response(client->socket, "ok\n");
}

void handle_left_command(client_t *client, char **args)
{
    if (strcasecmp(args[0], "LEFT") != 0)
        return;
    if (client->orientation == NORTH)
        client->orientation = WEST;
    else if (client->orientation == WEST)
        client->orientation = SOUTH;
    else if (client->orientation == SOUTH)
        client->orientation = EAST;
    else if (client->orientation == EAST)
        client->orientation = NORTH;
    send_response(client->socket, "ok\n");
}
