/*
** EPITECH PROJECT, 2023
** core_server
** File description:
** core
*/

#include "server.h"
#include <time.h>

void free_command_args(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}

char **duplicate_args(char **args)
{
    int arg_count = 0;
    while (args[arg_count] != NULL)
        arg_count++;

    char **new_args = malloc(sizeof(char*) * (arg_count + 1));

    for (int i = 0; i < arg_count; i++)
        new_args[i] = strdup(args[i]);

    new_args[arg_count] = NULL;

    return new_args;
}

command_t *create_new_command(char **args, server_params_t *server_params)
{
    command_t *new_command = malloc(sizeof(command_t));
    new_command->name = strdup(args[0]);
    new_command->args = duplicate_args(args);
    int found = 0;

    if (!new_command || !new_command->name || !new_command->args) {
        printf("Erreur lors de la duplication de la commande.\n");
        return NULL;
    }
    if (strcmp(args[0], "Broadcast") == 0) {
        new_command->execution_time = time(NULL) + 7 / server_params->frequency;
        found += 1;
    }
    if (strcmp(args[0], "Fork") == 0) {
        new_command->execution_time = time(NULL) + 42 / server_params->frequency;
        found += 1;
    }
    if (found == 0) {
        free_command_args(new_command->args);
        free(new_command->name);
        free(new_command);
        return NULL;
    }
    return new_command;
}

void add_command_to_client(client_t *client, command_t *new_command)
{
    client->commands = realloc(client->commands, sizeof(command_t)
        * (client->command_count + 1));
    client->commands[client->command_count] = *new_command;
    client->command_count++;
    printf("Commande %s ajoutée à la liste des commandes du client %d.\n",
        new_command->name, client->id);
    free(new_command);
}

void handle_client_request(client_t *clients, char *buffer, int i, server_params_t *server_params)
{
    char **args = NULL;
    if (buffer && strlen(buffer) > 0) {
        args = get_args_from_buffer(buffer);
        if (args == NULL) {
            printf("Erreur lors de la récupération des arguments.\n");
            return;
        }

        command_t *new_command = create_new_command(args, server_params);
        if (new_command == NULL) {
            send_response(clients[i].socket, "ko\n");
            return;
        }

        add_command_to_client(&clients[i], new_command);
    }
}

void remove_executed_command(client_t *client, int command_index)
{
    for (int k = command_index; k < client->command_count - 1; k++)
        client->commands[k] = client->commands[k + 1];
    free_command_args(client->commands[client->command_count - 1].args);
    client->command_count--;
    client->commands = realloc(client->commands,
        sizeof(command_t) * client->command_count);
}

void execute_commands_if_ready(client_t *clients,
    client_t *client, server_params_t *server_params)
{
    for (int j = 0; j < client->command_count; j++) {
        if (time(NULL) >= client->commands[j].execution_time) {
            handle_command(client, server_params,
                client->commands[j].args);
            handle_connect_nbr_command(clients, client, server_params,
                client->commands[j].args);
            handle_command_with_player_nbr(clients, client,
                server_params, client->commands[j].args);
            handle_broadcast_command(clients, client, client->commands[j].args);
            handle_eject_command(clients, client, server_params, client->commands[j].args);
            remove_executed_command(client, j);
        }
    }
}

void check_client_activity(client_t *clients, int server_socket, fd_set *readfds, server_params_t *server_params) {
    int client_socket = 0;
    int valread = 0;
    char buffer[BUFFER_SIZE];

    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_socket = clients[i].socket;

        execute_commands_if_ready(clients, &clients[i], server_params);

        if (!FD_ISSET(client_socket, readfds))
            continue;
        if ((valread = read(client_socket, buffer, BUFFER_SIZE)) == 0)
            handle_disconnect(&clients[i]);
            continue;
        if (!buffer)
            return;
        buffer[valread] = '\0';
        handle_client_request(clients, buffer, i, server_params);
    }
}
