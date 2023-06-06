/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** assets.cpp
*/

#include "assets.hpp"

Assets::Assets()
{
}

void Assets::init_assets(int height, int width)
{
    this->box_size = 1080 / height;
    this->width_checkerboard = box_size * width;
    this->rectangle_width = 1920 - width_checkerboard;
    this->font.loadFromFile("assets/Bronten.ttf");
    this->text_tna.setFont(this->font);
    this->text_tna.setString("Team name: ");
    this->text_tna.setCharacterSize(40);
    this->text_tna.setFillColor(sf::Color::Black);
    this->text_tna.setPosition(250, 10);
    this->text_chat.setFont(this->font);
    this->text_chat.setString("Chat :");
    this->text_chat.setCharacterSize(40);
    this->text_chat.setFillColor(sf::Color::Black);
    this->text_chat.setPosition(350, 1080 / 3 + 10);
    this->text_info.setFont(this->font);
    this->text_info.setString("Info :");
    this->text_info.setCharacterSize(40);
    this->text_info.setFillColor(sf::Color::Black);
    this->text_info.setPosition(350, 2 * 1080 / 3 + 10);
    this->closeButtonTexture.loadFromFile("assets/quit-icon.png");
    this->closeButtonSprite.setTexture(this->closeButtonTexture);
    this->closeButtonSprite.setPosition(10, 10);
    this->optionsButtonTexture.loadFromFile("assets/options.png");
    this->optionsButtonSprite.setTexture(this->optionsButtonTexture);
    this->optionsButtonSprite.setPosition(80, 10);
    this->leftrectangle1 = sf::RectangleShape(sf::Vector2f(this->rectangle_width, 1080 / 3));
    this->leftrectangle1.setPosition(0, 0);
    this->leftrectangle1.setFillColor(sf::Color::Blue);
    this->leftrectangle2 = sf::RectangleShape(sf::Vector2f(this->rectangle_width, 1080 / 3));
    this->leftrectangle2.setPosition(0, 1080 / 3);
    this->leftrectangle2.setFillColor(sf::Color::Red);
    this->leftrectangle3 = sf::RectangleShape(sf::Vector2f(this->rectangle_width, 1080 / 3));
    this->leftrectangle3.setPosition(0, 2 * 1080 / 3);
    this->leftrectangle3.setFillColor(sf::Color::Green);
    this->tileTexture.loadFromFile("assets/tile.png");
    for (int i = 0; i < width; i++) {
        std::vector<sf::Sprite> tmp;
        for(int j = 0; j < height; j++) {
            tmp.push_back(sf::Sprite());
        }
        this->tiles.push_back(tmp);
    }
    for (int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            this->tiles[i][j].setTexture(this->tileTexture);
            float scalingFactor = std::min(static_cast<float>(this->box_size) / this->tileTexture.getSize().x,
                                           static_cast<float>(this->box_size) / this->tileTexture.getSize().y);
            this->tiles[i][j].setScale(sf::Vector2f(scalingFactor, scalingFactor));
            this->tiles[i][j].setPosition(i * this->box_size + this->rectangle_width, j * this->box_size);
        }
    }
}

Assets::~Assets()
{
}