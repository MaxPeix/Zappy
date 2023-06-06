/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** GUI.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Assets {
    public:
        Assets() = default;
        Assets(int height, int width);
        ~Assets();
        int box_size;
        int width_checkerboard;
        int rectangle_width;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Font font;
        sf::Text text_tna;
        sf::Text text_chat;
        sf::Text text_info;
        sf::Texture closeButtonTexture;
        sf::Sprite closeButtonSprite;
        sf::Texture optionsButtonTexture;
        sf::Sprite optionsButtonSprite;
        sf::RectangleShape rectangle;
        sf::RectangleShape leftrectangle1;
        sf::RectangleShape leftrectangle2;
        sf::RectangleShape leftrectangle3;
};