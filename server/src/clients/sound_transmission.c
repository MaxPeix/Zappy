/*
** EPITECH PROJECT, 2023
** sound_transmission
** File description:
** sound_transmission
*/

#include "server.h"
#include <math.h>

int manhattan_distance_torus(coord_params_t params)
{
    int dx = abs(params.x1 - params.x2);
    int dy = abs(params.y1 - params.y2);

    dx = dx > params.width / 2 ? params.width - dx : dx;
    dy = dy > params.height / 2 ? params.height - dy : dy;

    return dx + dy;
}

int identify_tile(client_t *emitter,
    client_t *receiver, coord_params_t params)
{
    int dx = (receiver->x_position - emitter->x_position + params.width)
        % params.width;
    int dy = (receiver->y_position - emitter->y_position + params.height)
        % params.height;
    if (dx > params.width / 2)
        dx -= params.width;
    if (dy > params.height / 2)
        dy -= params.height;
    double angle = atan2(dy, dx);
    int direction = (int)((angle + 2 * M_PI + M_PI / 8
        - emitter->orientation * M_PI / 2) / (M_PI / 4));
    direction %= 8;
    int tile_number = direction + 1;
    tile_number = (tile_number == 9) ? 1 : tile_number;
    return tile_number;
}
