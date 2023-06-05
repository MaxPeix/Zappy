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

const int BUFFER_SIZE = 4096;

#define SUCCESS 0
#define ERROR 84

class GUI {
    public:
        GUI(int port, std::string machine);
        ~GUI();
        int connectToServer();
        void draw_game();
        void draw_cmd(sf::RenderWindow window, std::string cmd);
        std::string ask_server(std::string cmd);
    private:
        int port;
        std::string machine;
        int height;
        int width;
        std::vector<std::vector<std::string>> tna;
};
