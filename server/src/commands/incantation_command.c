/*
** EPITECH PROJECT, 2023
** server
** File description:
** incantation_command.c
*/

#include "server.h"

void handle_incantation_command(client_t *clients,
    client_t *client, server_params_t *server_params, char **args)
{
    tile_t *tile =
        &server_params->world[client->y_position][client->x_position];
    int nb_player_on_tile = 0;
    int nb_player[7] = { 1, 2, 2, 4, 4, 6, 6 };
    char *output_graphical = NULL;

    if (strcasecmp(args[0], "INCANTATION") != 0)
        return;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_connected == 0 || clients[i].is_graphical == 1)
            continue;
        if (clients[i].x_position == client->x_position
            && clients[i].y_position == client->y_position
            && clients[i].level == client->level)
            nb_player_on_tile++;
    }
    if (client->level < 8) {
        if (nb_player_on_tile >= nb_player[client->level - 1]
            && check_stone(tile, client->level) == true) {
            client->level++;
            dprintf(client->socket, "Current level: %d\n", client->level);
            remove_stones(tile, client->level);
        }
    }
    output_graphical = msprintf("pie %d %d %d\n", client->x_position,
        client->y_position, client->level);
    send_message_to_graphical(clients, output_graphical);
}

void send_elevation_underway(client_t *clients, client_t *client)
{
    char *output = NULL;

    output = msprintf("Elevation underway\n");
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_connected == 0 || clients[i].is_graphical == 1)
            continue;
        if (clients[i].x_position == client->x_position
            && clients[i].y_position == client->y_position
            && clients[i].level == client->level)
            send_response(client[i].socket, output);
    }
    free(output);
}

int can_do_incantation(client_t *clients, client_t *client,
    server_params_t *server_params, char **args)
{
    int nb_player[7] = { 1, 2, 2, 4, 4, 6, 6 };
    int nb_player_on_tile = 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_connected == 0 || clients[i].is_graphical == 1)
            continue;
        if (clients[i].x_position == client->x_position
            && clients[i].y_position == client->y_position
            && clients[i].level == client->level)
            nb_player_on_tile++;
    }
    if (client->level < 8) {
        if (nb_player_on_tile >= nb_player[client->level - 1]
            && check_stone(&server_params->world[client->y_position][client->x_position],
            client->level) == true)
            send_elevation_underway(clients, client);
            return 1;
    }
    return 0;
}

void send_message_to_graphical_start_incantation(client_t *clients,
    client_t *client, server_params_t *server_params, char **args)
{
    int nb_player[7] = { 1, 2, 2, 4, 4, 6, 6 };
    char message[1024] = { 0 };
    sprintf(message,
            "pic %d %d %d",
            client->x_position,
            client->y_position,
            client->level);

    int nb_player_on_tile = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_connected == 0 || clients[i].is_graphical == 1)
            continue;
        if (clients[i].x_position == client->x_position
            && clients[i].y_position == client->y_position
            && clients[i].level == client->level) {
            char player_num[10];
            sprintf(player_num, " %d", clients[i].id);
            strcat(message, player_num);
            nb_player_on_tile++;
        }
    }
    strcat(message, "\n");
    if (client->level < 8) {
        if (nb_player_on_tile >= nb_player[client->level - 1]
            && check_stone(&server_params
                                ->world[client->y_position][client->x_position],
                           client->level)
                   == true)
            send_message_to_graphical(clients, message);
    }
}
