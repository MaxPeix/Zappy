/*
** EPITECH PROJECT, 2023
** init_server
** File description:
** init_server
*/

#include "server.h"

server_params_t init_default_server_params(void)
{
    server_params_t params;

    params.port = 4242;
    params.width = 10;
    params.height = 10;
    params.team_names = NULL;
    params.clients_per_team = 2;
    params.frequency = 5000;

    return params;
}

void parse_teams_names(int argc, char **argv, int i, server_params_t *params)
{
    int team_count = 0;
    for (int j = i + 1; j < argc; j++) {
        if (argv[j][0] == '-')
            break;
        team_count++;
    }
    params->team_names = malloc(sizeof(char *) * (team_count + 1));
    for (int k = 0; k < team_count; k++)
        params->team_names[k] = strdup(argv[i + k + 1]);
    params->team_names[team_count + 1] = NULL;
}

void count_resources(server_params_t *params, char resource) {
    int total_resource = 0;
    for (int x = 0; x < params->width; x++) {
        for (int y = 0; y < params->height; y++) {
            switch (resource) {
                case 'f': total_resource += params->world[x][y].food; break;
                case 'l': total_resource += params->world[x][y].linemate; break;
                case 'd': total_resource += params->world[x][y].deraumere; break;
                case 's': total_resource += params->world[x][y].sibur; break;
                case 'm': total_resource += params->world[x][y].mendiane; break;
                case 'p': total_resource += params->world[x][y].phiras; break;
                case 't': total_resource += params->world[x][y].thystame; break;
            }
        }
    }
    printf("Total %c: %d\n", resource, total_resource);
}

void distribute_resources(server_params_t *params, int total_resource, int *resource_distributed, int max_resource_per_tile, char resource) {
    while (*resource_distributed < total_resource) {
        int random_x = rand() % params->width;
        int random_y = rand() % params->height;
        int current_resource = 0;
        
        switch (resource) {
            case 'f': current_resource = params->world[random_x][random_y].food; break;
            case 'l': current_resource = params->world[random_x][random_y].linemate; break;
            case 'd': current_resource = params->world[random_x][random_y].deraumere; break;
            case 's': current_resource = params->world[random_x][random_y].sibur; break;
            case 'm': current_resource = params->world[random_x][random_y].mendiane; break;
            case 'p': current_resource = params->world[random_x][random_y].phiras; break;
            case 't': current_resource = params->world[random_x][random_y].thystame; break;
        }
        
        if (current_resource >= max_resource_per_tile)
            continue;
            
        int remaining_resource = total_resource - *resource_distributed;
        int resource_to_give = (remaining_resource > 2) ? rand() % 2 : remaining_resource;
        *resource_distributed += resource_to_give;
        
        switch (resource) {
            case 'f': params->world[random_x][random_y].food += resource_to_give; break;
            case 'l': params->world[random_x][random_y].linemate += resource_to_give; break;
            case 'd': params->world[random_x][random_y].deraumere += resource_to_give; break;
            case 's': params->world[random_x][random_y].sibur += resource_to_give; break;
            case 'm': params->world[random_x][random_y].mendiane += resource_to_give; break;
            case 'p': params->world[random_x][random_y].phiras += resource_to_give; break;
            case 't': params->world[random_x][random_y].thystame += resource_to_give; break;
        }
    }
}

void parse_args(int argc, char **argv, server_params_t *params) {
    srand(time(NULL));
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0)
            params->port = atoi(argv[++i]);
        if (strcmp(argv[i], "-x") == 0)
            params->width = atoi(argv[++i]);
        if (strcmp(argv[i], "-y") == 0)
            params->height = atoi(argv[++i]);
        if (strcmp(argv[i], "-n") == 0)
            parse_teams_names(argc, argv, i, params);
        if (strcmp(argv[i], "-c") == 0)
            params->clients_per_team = atoi(argv[++i]);
        if (strcmp(argv[i], "-f") == 0)
            params->frequency = atoi(argv[++i]);
    }
    
    params->world = malloc(params->width * sizeof(mob_t *));
    for (int x = 0; x < params->width; x++) {
        params->world[x] = malloc(params->height * sizeof(mob_t));
        for (int y = 0; y < params->height; y++) {
            params->world[x][y].x = x;
            params->world[x][y].y = y;
            params->world[x][y].food = 0;
            params->world[x][y].linemate = 0;
            params->world[x][y].deraumere = 0;
            params->world[x][y].sibur = 0;
            params->world[x][y].mendiane = 0;
            params->world[x][y].phiras = 0;
            params->world[x][y].thystame = 0;
        }
    }
    
    int total_food = params->width * params->height * 0.5;
    int food_distributed = 0;
    distribute_resources(params, total_food, &food_distributed, 2, 'f');

    int total_linemate = params->width * params->height * 0.3;
    int linemate_distributed = 0;
    distribute_resources(params, total_linemate, &linemate_distributed, 2, 'l');

    int total_deraumere = params->width * params->height * 0.15;
    int deraumere_distributed = 0;
    distribute_resources(params, total_deraumere, &deraumere_distributed, 2, 'd');

    int total_sibur = params->width * params->height * 0.1;
    int sibur_distributed = 0;
    distribute_resources(params, total_sibur, &sibur_distributed, 2, 's');

    int total_mendiane = params->width * params->height * 0.1;
    int mendiane_distributed = 0;
    distribute_resources(params, total_mendiane, &mendiane_distributed, 2, 'm');

    int total_phiras = params->width * params->height * 0.08;
    int phiras_distributed = 0;
    distribute_resources(params, total_phiras, &phiras_distributed, 2, 'p');

    int total_thystame = params->width * params->height * 0.05;
    int thystame_distributed = 0;
    distribute_resources(params, total_thystame, &thystame_distributed, 2, 't');
}

int create_and_bind_socket(server_params_t params,
    struct sockaddr_in *address)
{
    if (params.port == 0 || !address)
        return -1;
    int server_socket;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        return -1;
    }
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(params.port);
    if (bind(server_socket,
        (struct sockaddr *)address, sizeof(*address)) < 0) {
        perror("bind failed");
        return -1;
    }
    printf("Port : %d\n", params.port);
    return server_socket;
}
