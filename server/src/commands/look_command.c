/*
** EPITECH PROJECT, 2023
** server
** File description:
** look_command.c
*/

#include "server.h"
#include <stdbool.h>

static tile_t *get_tile(server_params_t *server_params, int x, int y)
{
    tile_t *tile = NULL;
    int secure_x = x % server_params->width;
    int secure_y = y % server_params->height;

    if (secure_x < 0)
        secure_x += server_params->width;
    if (secure_y < 0)
        secure_y += server_params->height;
    return &(server_params->world[secure_y][secure_x]);
}

static tile_t *get_relative_tile(server_params_t *server_params,
    client_t *client, int x, int y)
{
    int relative_x = client->x_position + x;
    int relative_y = client->y_position + y;

    if (client->orientation == NORTH) {
        relative_x = client->x_position - y;
        relative_y = client->y_position + x;
    } else if (client->orientation == EAST) {
        relative_x = client->x_position + x;
        relative_y = client->y_position + y;
    } else if (client->orientation == SOUTH) {
        relative_x = client->x_position + y;
        relative_y = client->y_position - x;
    } else if (client->orientation == WEST) {
        relative_x = client->x_position - x;
        relative_y = client->y_position - y;
    }
    return get_tile(server_params, relative_x, relative_y);
}

bool get_tile_items(tile_t *tile, char *tiles_content, int *i, bool is_player)
{
    char **names = (char *[]){ "food",     "linemate", "deraumere", "sibur",
                               "mendiane", "phiras",   "thystame",  NULL };
    int *resources[] = { &tile->food,      &tile->linemate,
                         &tile->deraumere, &tile->sibur,
                         &tile->mendiane,  &tile->phiras,
                         &tile->thystame,  NULL };
    bool is_resource = is_player;

    for (int j = 0; names[j] != NULL; j++) {
        for (int k = 0; k < *resources[j]; k++) {
            strncpy(tiles_content + *i, names[j], BUFFER_SIZE - *i);
            *i += strlen(names[j]);
            strncpy(tiles_content + *i, " ", BUFFER_SIZE - *i);
            *i += strlen(" ");
            is_resource = true;
        }
    }
    *i -= is_resource;
    return is_resource;
}

bool get_player_on_tile(client_t *clients,
                        char *tiles_content,
                        int *i,
                        coordinate_t cord)
{
    bool is_player = false;
    for (int j = 0; j < MAX_CLIENTS; j++) {
        if (clients[j].x_position == cord.x && clients[j].y_position == cord.y
            && clients[j].is_connected) {
            strncpy(tiles_content + *i, "player", BUFFER_SIZE - *i);
            *i += strlen("player");
            strncpy(tiles_content + *i, " ", BUFFER_SIZE - *i);
            *i += strlen(" ");
            is_player = true;
        }
    }
    if (is_player)
        *i--;
    return is_player;
}

void handle_look_command(client_t *clients,
                         client_t *client,
                         server_params_t *server_params,
                         char **args)
{
    char tiles_content[4096] = { 0 };
    int i = 2;
    int nb_tiles[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17 };
    tile_t *tile = NULL;
    bool is_item = false;

    if (strcasecmp(args[0], "LOOK") != 0)
        return;
    strncpy(tiles_content, "[ ", BUFFER_SIZE);
    for (int lv = 0; lv <= client->level; lv++)
        for (int idx = -lv; idx < nb_tiles[lv] - lv; idx++) {
            tile = get_relative_tile(server_params, client, idx, lv);
            is_item = get_player_on_tile(
                clients, &tiles_content[0], &i, (coordinate_t){ idx, lv });
            is_item = get_tile_items(tile, &tiles_content[0], &i, is_item);
            strncpy(tiles_content + i, ", ", BUFFER_SIZE - i);
            i += 1 + is_item;
        }
    i += (i < 2 ? 2 : 0);
    strncpy((tiles_content + i) - 2, " ]\n", BUFFER_SIZE - i);
    write(client->socket, tiles_content, BUFFER_SIZE);
}
