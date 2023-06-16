/*
** EPITECH PROJECT, 2023
** server
** File description:
** look_command.c
*/

#include "server.h"

coordinate_t get_relative_coords(client_t *client, int x, int y)
{
    int relative_x = client->x_position + x;
    int relative_y = client->y_position + y;

    if (client->orientation == NORTH) {
        relative_x = client->x_position + x;
        relative_y = client->y_position - y;
    } else if (client->orientation == EAST) {
        relative_x = client->x_position + y;
        relative_y = client->y_position + x;
    } else if (client->orientation == SOUTH) {
        relative_x = client->x_position - x;
        relative_y = client->y_position + y;
    } else if (client->orientation == WEST) {
        relative_x = client->x_position - y;
        relative_y = client->y_position - x;
    }
    return (coordinate_t){ relative_x, relative_y };
}

void handle_look_command(client_t *clients, client_t *client,
                         server_params_t *server_params, char **args)
{
     char tiles_content[4096] = { 0 };
     int i = 2;
     int nb_tiles[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17 };
     bool is_item = false;
     coordinate_t coord = { 0 };

     if (strcmp(args[0], "Look") != 0)
         return;
     strncpy(tiles_content, "[ ", BUFFER_SIZE);
     for (int lv = 0; lv <= client->level; lv++)
         for (int ix = -lv; ix < nb_tiles[lv] - lv; ix++, i += 1 + is_item) {
             coord = get_relative_coords(client, ix, lv);
             is_item = get_player_on_tile(clients, &tiles_content[0], &i,
             coord); is_item |= get_relative_tile_items(
                 coord, &tiles_content[0], &i, server_params);
             strncpy(tiles_content + i, ", ", BUFFER_SIZE - i);
         }
     i += (i < 2 ? 2 : 0);
     strncpy((tiles_content + i) - 2, " ]\n", BUFFER_SIZE - i);
     write(client->socket, tiles_content, BUFFER_SIZE);
}
