/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** GUI.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>

class Assets {
    public:
        Assets();
        ~Assets();
        void init_assets(int height, int width);
        int box_size;
        int width_checkerboard;
        int rectangle_width;
        std::map<int, sf::Sprite> monster_sprites;
        void create_player(int x, int y, int n);
        void delete_player(int n);
        sf::Texture monster_texture;
        sf::Sprite monster_sprite;
        sf::Font font;
        sf::Text title_tna;
        sf::Text title_chat;
        sf::Text title_info;
        sf::Text text_bct;
        sf::Text tna_text;
        std::vector<sf::Text> chat_texts;
        sf::Text new_text;
        std::vector<std::string> chat_messages_string;
        sf::Texture closeButtonTexture;
        sf::Sprite closeButtonSprite;
        sf::Texture optionsButtonTexture;
        sf::Sprite optionsButtonSprite;
        sf::RectangleShape leftrectangle1;
        sf::RectangleShape leftrectangle2;
        sf::RectangleShape leftrectangle3;
        sf::Texture tileTexture;
        std::vector<std::vector<sf::Sprite>> tiles;
};
