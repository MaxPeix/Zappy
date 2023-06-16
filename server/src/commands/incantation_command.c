/*
** EPITECH PROJECT, 2023
** server
** File description:
** incantation_command.c
*/

#include "server.h"

int is_valid_user(client_t *client)
{
    if ((client->is_connected == 1 && client->is_graphical == 0))
        return 1;
    return 0;
}

void send_elevation_underway(client_t *clients, client_t *client)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (is_valid_user(&clients[i]) == 0)
            continue;
        if (clients[i].x_position == client->x_position
            && clients[i].y_position == client->y_position
            && clients[i].level == client->level)
            dprintf(clients[i].socket, "Elevation underway\n");
    }
}

int can_do_incantation(client_t *clients, client_t *client,
    server_params_t *server_params, char **args)
{
    int nb_player[7] = { 1, 2, 2, 4, 4, 6, 6 };
    int nb_player_on_tile = 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (is_valid_user(&clients[i]) == 0)
            continue;
        if (clients[i].x_position == client->x_position
            && clients[i].y_position == client->y_position
            && clients[i].level == client->level)
            nb_player_on_tile += 1;
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
        if (is_valid_user(&clients[i]) == 0)
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

void upgrade_level_players(client_t *clients, client_t *client,
    server_params_t *server_params, char **args)
{
    int nb_player[7] = { 1, 2, 2, 4, 4, 6, 6 };
    int nb_player_on_tile = 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (is_valid_user(&clients[i]) == 0)
            continue;
        if (clients[i].x_position == client->x_position
            && clients[i].y_position == client->y_position
            && clients[i].level == client->level)
            nb_player_on_tile += 1;
    }
    if (client->level < 8) {
        if (nb_player_on_tile >= nb_player[client->level - 1]
            && check_stone(&server_params->world[client->y_position][client->x_position],
            client->level) == true) {
            client->level++;
            dprintf(client->socket, "Current level: %d\n", client->level);
            remove_stones(&server_params->world[client->y_position][client->x_position],
                client->level);
        }
    }
}

void handle_incantation_command(client_t *clients,
    client_t *client, server_params_t *server_params, char **args)
{
    tile_t *tile =
        &server_params->world[client->y_position][client->x_position];
    int nb_player_on_tile = 0;
    int nb_player[7] = { 1, 2, 2, 4, 4, 6, 6 };
    char *output_graphical = NULL;

    if (strcmp(args[0], "Incantation") != 0)
        return;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (is_valid_user(&clients[i]) == 0)
            continue;
        if (clients[i].x_position == client->x_position
            && clients[i].y_position == client->y_position
            && clients[i].level == client->level)
            nb_player_on_tile += 1;
    }
    int level_client_before = client->level;
    if (level_client_before < 8) {
        if (nb_player_on_tile >= nb_player[level_client_before - 1]
            && check_stone(tile, level_client_before) == true) {
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (is_valid_user(&clients[i]) == 0)
                    continue;
                if (clients[i].x_position == client->x_position
                    && clients[i].y_position == client->y_position
                    && clients[i].level == level_client_before) {
                    clients[i].level++;
                    dprintf(clients[i].socket, "Current level: %d\n", clients[i].level);
                    output_graphical = msprintf("pie %d %d %d\n", clients[i].x_position,
                        clients[i].y_position, clients[i].level);
                    send_message_to_graphical(clients, output_graphical);
                    free(output_graphical);
                }
            }
            remove_stones(tile, client->level);
        }
    }
}
