/*
** EPITECH PROJECT, 2023
** server
** File description:
** incantation_command.c
*/

#include "server.h"
#include <stdbool.h>

static bool check_stone(tile_t *tile, int level)
{
    int linemate[7] = { 1, 1, 2, 1, 1, 1, 1 };
    int deraumere[7] = { 0, 1, 0, 1, 2, 2, 2 };
    int sibur[7] = { 0, 1, 1, 2, 1, 3, 2 };
    int mendiane[7] = { 0, 0, 0, 0, 3, 0, 2 };
    int phiras[7] = { 0, 0, 2, 1, 0, 1, 2 };
    int thystame[7] = { 0, 0, 0, 0, 0, 0, 1 };

    if (level > 0 && level < 8 && tile->linemate < linemate[level - 1]
        || tile->deraumere < deraumere[level - 1]
        || tile->sibur < sibur[level - 1] || tile->phiras < phiras[level - 1]
        || tile->mendiane < mendiane[level - 1]
        || tile->thystame < thystame[level - 1])
        return false;
    tile->linemate -= linemate[level - 1];
    tile->deraumere -= deraumere[level - 1];
    tile->sibur -= sibur[level - 1];
    tile->mendiane -= mendiane[level - 1];
    tile->phiras -= phiras[level - 1];
    tile->thystame -= thystame[level - 1];
    return true;
}

void handle_incantation_command(client_t *clients,
                                client_t *client,
                                server_params_t *server_params,
                                char **args)
{
    tile_t *tile =
        &server_params->world[client->y_position][client->x_position];
    int nb_player_on_tile = 0;
    int nb_player[7] = { 1, 2, 2, 4, 4, 6, 6 };

    if (strcasecmp(args[0], "INCANTATION") != 0)
        return;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].x_position == client->x_position
            && clients[i].y_position == client->x_position
            && strcmp(clients[i].team_name, client->team_name) == 0)
            nb_player_on_tile++;
    }
    if (client->level < 8) {
        if (nb_player_on_tile >= nb_player[client->level - 1]
            && check_stone(tile, client->level) == true) {
            client->level++;
            dprintf(client->socket, "Current level: %d\n", client->level);
        }
    }
}

int can_do_incantation(client_t *clients,
                       client_t *client,
                       server_params_t *server_params,
                       char **args)
{
    int nb_player[7] = { 1, 2, 2, 4, 4, 6, 6 };
    int nb_player_on_tile = 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].x_position == client->x_position
            && clients[i].y_position == client->x_position
            && strcmp(clients[i].team_name, client->team_name) == 0)
            nb_player_on_tile++;
    }
    if (client->level < 8) {
        if (nb_player_on_tile >= nb_player[client->level - 1]
            && check_stone(&server_params
                                ->world[client->y_position][client->x_position],
                           client->level)
                   == true)
            return 1;
    }
    return 0;
}

void send_message_to_graphical_start_incantation(client_t *clients,
                                                 client_t *client,
                                                 server_params_t *server_params,
                                                 char **args)
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
        if (clients[i].x_position == client->x_position
            && clients[i].y_position == client->x_position
            && strcmp(clients[i].team_name, client->team_name) == 0) {
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
