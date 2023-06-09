/*
** EPITECH PROJECT, 2023
** server
** File description:
** food_command.c
*/

#include "server.h"

void print_inventory(server_params_t *server_params, client_t *client)
{
    dprintf(client->socket,
            "[ food %d, linemate %d, deraumere %d, sibur %d, mendiane %d, "
            "phiras %d, thystame %d ]\n",
            client->food,
            client->linemate,
            client->deraumere,
            client->sibur,
            client->mendiane,
            client->phiras,
            client->thystame);
}
