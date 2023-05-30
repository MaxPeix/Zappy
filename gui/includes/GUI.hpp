/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** GUI.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>

#define SUCCESS 0
#define ERROR 84


struct TileData {
    int x;
    int y;
    int q0;
    int q1;
    int q2;
    int q3;
    int q4;
    int q5;
    int q6;
};

class GUI {
    public:
        GUI();
        ~GUI();
        int run();
    private:
        sf::RenderWindow window;
        int port;
        std::string machine;
};

class Map {
    public:
        Map();
        ~Map();
    private:
        int x;
        int y;
        std::vector<TileData> tiles;
        std::vector<std::vector<std::string>> tna;
};
