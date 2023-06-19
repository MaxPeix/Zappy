/*
** EPITECH PROJECT, 2023
** server
** File description:
** look_command_tile.c
*/

#include "server.h"

tile_t *get_tile(server_params_t *server_params, int x, int y)
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

bool get_tile_items(tile_t *tile, char *tiles_content, int *i)
{
    char **names = (char *[]){ "food",     "linemate", "deraumere", "sibur",
        "mendiane", "phiras",   "thystame",  NULL };
    int *resources[] = { &tile->food, &tile->linemate,
        &tile->deraumere, &tile->sibur,
        &tile->mendiane,  &tile->phiras,
        &tile->thystame,  NULL };
    bool is_resource = false;

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

bool get_player_on_tile(client_t *clients, char *tiles_content, int *i,
    coordinate_t coord)
{
    bool is_player = false;
    for (int j = 0; j < MAX_CLIENTS; j++) {
        if (clients[j].x_position == coord.x
            && clients[j].y_position == coord.y
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

bool get_relative_tile_items(coordinate_t coord, char *tiles_content, int *i,
    server_params_t *server_params)
{
    tile_t *tile = get_tile(server_params, coord.x, coord.y);

    return get_tile_items(tile, tiles_content, i);
}
