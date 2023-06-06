/*
** EPITECH PROJECT, 2023
** init ressources
** File description:
** ressources
*/

#include "server.h"
#include <time.h>

int get_random_coordinate(int limit)
{
    return rand() % limit;
}

int get_current_resource(server_params_t *params, int x, int y, char resource)
{
    int current_resource = 0;

    if (resource == 'f')
        current_resource = params->world[x][y].food;
    if (resource == 'l')
        current_resource = params->world[x][y].linemate;
    if (resource == 'd')
        current_resource = params->world[x][y].deraumere;
    if (resource == 's')
        current_resource = params->world[x][y].sibur;
    if (resource == 'm')
        current_resource = params->world[x][y].mendiane;
    if (resource == 'p')
        current_resource = params->world[x][y].phiras;
    if (resource == 't')
        current_resource = params->world[x][y].thystame;

    return current_resource;
}

void update_resource(server_params_t *params,
    coordinate_t coordinate, char resource, int amount)
{
    int x = coordinate.x;
    int y = coordinate.y;

    if (resource == 'f')
        params->world[x][y].food += amount;
    if (resource == 'l')
        params->world[x][y].linemate += amount;
    if (resource == 'd')
        params->world[x][y].deraumere += amount;
    if (resource == 's')
        params->world[x][y].sibur += amount;
    if (resource == 'm')
        params->world[x][y].mendiane += amount;
    if (resource == 'p')
        params->world[x][y].phiras += amount;
    if (resource == 't')
        params->world[x][y].thystame += amount;
}

void distribute_resources(server_params_t *params, int total_resource,
    char resource)
{
    int resource_distributed = 0;

    while (resource_distributed < total_resource) {
        int random_x = get_random_coordinate(params->width);
        int random_y = get_random_coordinate(params->height);
        int current_resource = get_current_resource(params,
            random_x, random_y, resource);

        int remaining_resource = total_resource - resource_distributed;
        int resource_to_give = (remaining_resource > 2)
            ? rand() % 2 : remaining_resource;
        resource_distributed += resource_to_give;
        coordinate_t coordinate = { .x = random_x, .y = random_y };
        update_resource(params, coordinate, resource, resource_to_give);
    }
}

void define_params_world_default(server_params_t *params)
{
    params->world = malloc(params->height * sizeof(tile_t *));
    for (int y = 0; y < params->height; y++) {
        params->world[y] = malloc(params->width * sizeof(tile_t));
        for (int x = 0; x < params->width; x++) {
            params->world[y][x].x = x;
            params->world[y][x].y = y;
            params->world[y][x].food = 0;
            params->world[y][x].linemate = 0;
            params->world[y][x].deraumere = 0;
            params->world[y][x].sibur = 0;
            params->world[y][x].mendiane = 0;
            params->world[y][x].phiras = 0;
            params->world[y][x].thystame = 0;
        }
    }
}

void define_settings_world(server_params_t *params)
{
    srand(time(NULL));
    define_params_world_default(params);

    distribute_food(params);
    distribute_linemate(params);
    distribute_deraumere(params);
    distribute_sibur(params);
    distribute_mendiane(params);
    distribute_phiras(params);
    distribute_thystame(params);
}
