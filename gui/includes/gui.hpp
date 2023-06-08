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
#include "infos.hpp"
#include <thread>
#include <future>

const int BUFFER_SIZE = 4096;

#define SUCCESS 0
#define ERROR 84

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
    private:
        Assets assets;
        Info info;
        int port;
        std::string machine;
        int clientSocket;
        int height;
        int width;
        std::vector<std::vector<std::string>> tna;
        sf::RenderWindow window;
        sf::Event event;
};
