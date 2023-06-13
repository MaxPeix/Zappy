/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** GUI.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include "assets.hpp"
#include <thread>
#include <future>

const int BUFFER_SIZE = 4096;

#define SUCCESS 0
#define ERROR 84

typedef struct info_player_s {
    int number;
    int x;
    int y;
    int orientation;
    int level;
    char team[6];
} info_player_t;

class GUI {
    public:
        GUI(int port, std::string machine);
        ~GUI();
        int connectToServer();
        void init_game();
        void draw_game();
        void game_loop();
        void check_event();
        void draw_cmd(std::string cmd);
        void listen_server();
        std::string ask_server(std::string cmd);
        void handle_stdin_input();
        void handle_read_server();
        void draw_bct(std::string cmd);
        void draw_tna(std::string cmd);
        void draw_pdi(std::string cmd);
        void draw_pnw(std::string cmd);
        void draw_ppo(std::string cmd);
        void draw_pin(std::string cmd);
        void draw_enw(std::string cmd);
        void draw_edi(std::string cmd);
        void draw_pbc(std::string cmd);
    private:
        Assets assets;
        int port;
        int sgt;
        std::string machine;
        int clientSocket;
        int height;
        int width;
        std::vector<std::vector<std::string>> tna;
        info_player_t player_info;
        sf::RenderWindow window;
        sf::Event event;
};
