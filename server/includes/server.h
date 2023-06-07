/*
** EPITECH PROJECT, 2023
** Server
** File description:
** Server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/select.h>
    #include <errno.h>

    #define MAX_CLIENTS 30
    #define BUFFER_SIZE 4096
    #define CLIENT_NAME "Anonymous"
    #define EPITECH_ERROR 84

    typedef struct tile {
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

    typedef struct client {
        int socket;
        char *team_name;
        int start_loggin;
        tile_t *tiles;
        int is_graphical;
        int level;
    } client_t;

    typedef struct server_params {
        int port;
        int width;
        int height;
        char **team_names;
        int clients_per_team;
        int frequency;
        tile_t **world;
    } server_params_t;

    typedef struct DistributionParams {
        server_params_t *params;
        int total_resource;
        char resource;
    } DistributionParams;

    typedef struct {
        int x;
        int y;
    } coordinate_t;

// Vérifie les erreurs de la ligne de commande
int check_errors(int argc, char **argv, server_params_t params);

// Initialise la liste des clients connectés
void init_clients_list(client_t *clients);

// Crée le socket et le lie à l'adresse du serveur
int create_and_bind_socket(server_params_t params,
    struct sockaddr_in *address);

// Attend les connexions entrantes et gère les clients connectés
void wait_for_connections(int server_socket, client_t *clients,
    struct sockaddr_in address, server_params_t *server_params);

// Ajoute un nouveau client à la liste des clients connectés
void update_client_struct(int new_socket, client_t *clients, server_params_t
    *server_params);

// Traite les erreurs du select
void handle_select_errors(int activity);

// Configure les descripteurs de fichiers des clients connectés pour le select
int set_clients_sockets(client_t *clients, fd_set *readfds, int server_socket);

// Accepte une nouvelle connexion entrante
int accept_new_connection(int server_socket, struct sockaddr_in address);

// Vérifie les descripteurs de fichiers des clients connectés une activité
void check_client_activity(client_t *clients,
    int server_socket, fd_set *readfds, server_params_t *server_params);

// Envoie une réponse au client
void send_response(int socket, char *message);

// Lis le message du client
ssize_t read_method(int socket, char *buffer);

// Gère les commandes du client
void handle_command(client_t *client, server_params_t *server_params,
    char *buffer);

// Initialise la structure client
void init_clients_list(client_t *clients);

// Gère la deconnexion du client
void handle_disconnect(client_t *client);

// Récupère les arguments du client
char **get_args_from_client(char *buffer);

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

// Initalise la structure par défaut
server_params_t init_default_server_params(void);

// check if the team name is valid
int check_team_name(char *team_name, char **valid_teams);

// send the team info to the client (from protocol of the start)
void send_info_loggin(int socket, client_t *client, server_params_t
    *server_params);

// define settings of the world
void define_settings_world(server_params_t *params);

// lib function to get random coordinate with a limit
int get_random_coordinate(int limit);

// distribute resources
void distribute_resources(server_params_t *params,
    int total_resource, char resource);
void distribute_food(server_params_t *params);
void distribute_linemate(server_params_t *params);
void distribute_deraumere(server_params_t *params);
void distribute_sibur(server_params_t *params);
void distribute_mendiane(server_params_t *params);
void distribute_phiras(server_params_t *params);
void distribute_thystame(server_params_t *params);

#endif /* !SERVER_H_ */
