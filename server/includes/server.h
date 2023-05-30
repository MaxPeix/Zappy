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

    #define MAX_CLIENTS 10
    #define BUFFER_SIZE 4096
    #define CLIENT_NAME "Anonymous"
    #define EPITECH_ERROR 84

    typedef struct client {
        int socket;
    } client_t;

    typedef struct server_params {
        int port;
        int width;
        int height;
        char **team_names;
        int clients_per_team;
        int frequency;
    } server_params_t;

// Vérifie les erreurs de la ligne de commande
int check_errors(int argc, char **argv, server_params_t params);

// Initialise la liste des clients connectés
void init_clients_list(client_t *clients);

// Crée le socket et le lie à l'adresse du serveur
int create_and_bind_socket(server_params_t params,
    struct sockaddr_in *address);

// Attend les connexions entrantes et gère les clients connectés
void wait_for_connections(int server_socket,
    client_t *clients, struct sockaddr_in address);

// Ajoute un nouveau client à la liste des clients connectés
void update_client_struct(int new_socket, client_t *clients);

// Traite les erreurs du select
void handle_select_errors(int activity);

// Configure les descripteurs de fichiers des clients connectés pour le select
int set_clients_sockets(client_t *clients, fd_set *readfds, int server_socket);

// Accepte une nouvelle connexion entrante
int accept_new_connection(int server_socket, struct sockaddr_in address);

// Vérifie les descripteurs de fichiers des clients connectés une activité
void check_client_activity(client_t *clients,
    int server_socket, fd_set *readfds);

// Envoie une réponse au client
void send_response(int socket, char *message);

// Lis le message du client
void read_method(int socket, char *buffer);

// Gère les commandes du client
void handle_command(client_t *clients, int index, char *buffer);

// Initialise la structure client
void init_clients_list(client_t *clients);

// Gère la deconnexion du client
void handle_disconnect(client_t *clients, int socket, int index);

// Récupère les arguments du client
char **get_args_from_client(char *buffer);

// Libère un tableau de char **
void free_array(char **array);

// Parse les arguments passés en parametre au binaire
void parse_args(int argc, char **argv, server_params_t *params);

// Initalise la structure par défaut
server_params_t init_default_server_params(void);

#endif /* !SERVER_H_ */
