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
    this->title_tna.setFont(this->font);
    this->title_tna.setString("Teams name: ");
    this->title_tna.setCharacterSize(40);
    this->title_tna.setFillColor(sf::Color::Black);
    this->title_tna.setPosition(310, 10);
    this->title_chat.setFont(this->font);
    this->title_chat.setString("Chat :");
    this->title_chat.setCharacterSize(40);
    this->title_chat.setFillColor(sf::Color::Black);
    this->title_chat.setPosition(350, 1080 / 3 + 10);
    this->title_info.setFont(this->font);
    this->title_info.setString("Info :");
    this->title_info.setCharacterSize(40);
    this->title_info.setFillColor(sf::Color::Black);
    this->title_info.setPosition(350, 2 * 1080 / 3 + 10);
    this->text_bct.setFont(this->font);
    this->text_bct.setString("Tile content :\nFood : 0\nLinemate : 0\nDeraumere : 0\nSibur : 0\nMendiane : 0\nPhiras : 0\nThystame : 0");
    this->text_bct.setCharacterSize(30);
    this->text_bct.setFillColor(sf::Color::Black);
    this->text_bct.setPosition(10, 2 * 1080 / 3 + 60);
    this->text_pin.setFont(this->font);
    this->text_pin.setString("Inventory :\nFood : 0\nLinemate : 0\nDeraumere : 0\nSibur : 0\nMendiane : 0\nPhiras : 0\nThystame : 0");
    this->text_pin.setCharacterSize(30);
    this->text_pin.setFillColor(sf::Color::Black);
    this->text_pin.setPosition(600, 2 * 1080 / 3 + 60);
    this->text_plv.setFont(this->font);
    this->text_plv.setString("Level : N");
    this->text_plv.setCharacterSize(30);
    this->text_plv.setFillColor(sf::Color::Black);
    this->text_plv.setPosition(350, 2 * 1080 / 3 + 100);
    this->text_pid.setFont(this->font);
    this->text_pid.setString("Player : N");
    this->text_pid.setCharacterSize(30);
    this->text_pid.setFillColor(sf::Color::Black);
    this->text_pid.setPosition(350, 2 * 1080 / 3 + 60);
    this->tna_text.setFont(this->font);
    this->tna_text.setString("");
    this->tna_text.setCharacterSize(30);
    this->tna_text.setFillColor(sf::Color::Black);
    this->tna_text.setPosition(10, 100);
    new_text.setFont(this->font);
    new_text.setCharacterSize(30);
    new_text.setFillColor(sf::Color::Black);
    this->chat_messages_string = {};
    this->chat_texts = {};
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
    this->monster_texture.loadFromFile("assets/monster.png");
    this->monster_sprite.setTexture(monster_texture);
}

void Assets::create_player(int x, int y, int n)
{
    monster_sprite.setPosition(x * this->box_size + this->rectangle_width, y * this->box_size);
    monster_sprite.setScale(sf::Vector2f(0.5, 0.5));
    this->monster_sprites.insert(std::pair<int, sf::Sprite>(n, monster_sprite));
}

void Assets::delete_player(int n)
{
    this->monster_sprites.erase(n);
}

Assets::~Assets()
{
}