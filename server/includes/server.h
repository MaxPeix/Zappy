/*
** EPITECH PROJECT, 2023
** Server
** File description:
** Server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_CLIENTS 30
#define BUFFER_SIZE 4096
#define CLIENT_NAME "Anonymous"
#define EPITECH_ERROR 84

enum direction { FIRST, NORTH, EAST, SOUTH, WEST };

typedef struct tile
{
    int x;
    int y;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} tile_t;

typedef struct client
{
    int id;
    int x_position;
    int y_position;
    int orientation;
    int incantation_level;
    int level;
    int socket;
    char *team_name;
    int start_loggin;
    int is_graphical;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} client_t;

typedef struct server_params
{
    int port;
    int width;
    int height;
    char **team_names;
    int clients_per_team;
    int frequency;
    tile_t **world;
} server_params_t;

typedef struct DistributionParams
{
    server_params_t *params;
    int total_resource;
    char resource;
} DistributionParams;

typedef struct
{
    int x;
    int y;
} coordinate_t;

// msprintf function
char *msprintf(const char *format, ...);

// Vérifie les erreurs de la ligne de commande
int check_errors(int argc, char **argv, server_params_t params);

// Initialise la liste des clients connectés
void init_clients_list(client_t *clients);

// Crée le socket et le lie à l'adresse du serveur
int create_and_bind_socket(server_params_t params, struct sockaddr_in *address);

// Attend les connexions entrantes et gère les clients connectés
void wait_for_connections(int server_socket,
                          client_t *clients,
                          struct sockaddr_in address,
                          server_params_t *server_params);

// Ajoute un nouveau client à la liste des clients connectés
void update_client_struct(int new_socket, client_t *clients, server_params_t *server_params);

// Traite les erreurs du select
void handle_select_errors(int activity);

// Configure les descripteurs de fichiers des clients connectés pour le select
int set_clients_sockets(client_t *clients, fd_set *readfds, int server_socket);

// Accepte une nouvelle connexion entrante
int accept_new_connection(int server_socket, struct sockaddr_in address);

// Vérifie les descripteurs de fichiers des clients connectés une activité
void check_client_activity(client_t *clients, int server_socket, fd_set *readfds, server_params_t *server_params);

// Envoie une réponse au client
void send_response(int socket, char *message);

// Lis le message du client
ssize_t read_method(int socket, char *buffer);

// Gère les commandes du client
void handle_command(client_t *client, server_params_t *server_params, char **args);

// Gère les commandes du client avec un numéro de joueur
void handle_command_with_player_nbr(client_t *clients, client_t *client, server_params_t *server_params, char **args);

// handle_graphic_command_two
void handle_broadcast_command(client_t *clients, client_t *client, char **args);

// handle_graphic_command_three
void handle_eject_command(client_t *clients, client_t *client, server_params_t *server_params, char **args);

// Initialise la structure client
void init_clients_list(client_t *clients);

// Gère la deconnexion du client
void handle_disconnect(client_t *client);

// Récupère les arguments du client
char **get_args_from_buffer(char *buffer);

// Libère un tableau de char **
void free_array(char **array);

// Parse les arguments passés en parametre au binaire
void parse_args(int argc, char **argv, server_params_t *params);

// handle_graphic_command
void handle_graphic_command(client_t *client, server_params_t *server_params);

// Print mct
void print_mct(server_params_t *server_params, client_t *client);

// Print tna
void print_tna(server_params_t *server_params, client_t *client);

// Print msz
void print_msz(server_params_t *server_params, client_t *client);

// Print sgt
void print_sgt(server_params_t *server_params, client_t *client);

// Print bct
void print_bct(server_params_t *server_params, client_t *client, char **args);

// Print ppo
void print_ppo(client_t *client, client_t *player);

// concat strings
char *concat_strings(char *output, char *temp);

// Initalise la structure par défaut
server_params_t init_default_server_params(void);

// check if the team name is valid
int check_team_name(char *team_name, char **valid_teams);

// send the team info to the client (from protocol of the start)
void send_info_loggin(int socket, client_t *client, server_params_t *server_params);

// define settings of the world
void define_settings_world(server_params_t *params);

// lib function to get random coordinate with a limit
int get_random_coordinate(int limit);

// concat strings
char *concat_strings(char *output, char *temp);

// send notification to the graphical client when a player loggin
void send_notification_player_loggin(client_t *clients, client_t *client_logged_in, server_params_t *server_params);

// distribute resources
void distribute_resources(server_params_t *params, int total_resource, char resource);
void distribute_food(server_params_t *params);
void distribute_linemate(server_params_t *params);
void distribute_deraumere(server_params_t *params);
void distribute_sibur(server_params_t *params);
void distribute_mendiane(server_params_t *params);
void distribute_phiras(server_params_t *params);
void distribute_thystame(server_params_t *params);

// client movement

void handle_forward_command(client_t *client, char **args);
void handle_right_command(client_t *client, char **args);
void handle_left_command(client_t *client, char **args);

// client food
void print_inventory(server_params_t *server_params, client_t *client);

#endif /* !SERVER_H_ */
