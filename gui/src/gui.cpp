/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** gui.cpp
*/

#include "gui.hpp"

GUI::GUI(int port, std::string machine)
{
    this->port = port;
    this->machine = machine;
}

GUI::~GUI()
{
}

void GUI::init_game()
{
    this->window.create(sf::VideoMode(1920, 1080), "Trantor", sf::Style::Fullscreen);
    this->window.setFramerateLimit(60);
    this->assets = Assets();
    this->assets.init_assets(this->height, this->width);
    this->assets.text_sgt.setString(std::to_string(this->sgt));
}

void GUI::draw_game()
{
    window.draw(this->assets.leftrectangle1);
    window.draw(this->assets.leftrectangle2);
    window.draw(this->assets.leftrectangle3);
    window.draw(this->assets.closeButtonSprite);
    window.draw(this->assets.optionsButtonSprite);
    window.draw(this->assets.optionsPlusButtonSprite);
    window.draw(this->assets.optionsMinusButtonSprite);
    window.draw(this->assets.title_tna);
    window.draw(this->assets.title_chat);
    window.draw(this->assets.title_info);
    window.draw(this->assets.text_bct);
    window.draw(this->assets.text_pin);
    window.draw(this->assets.text_plv);
    window.draw(this->assets.text_pid);
    window.draw(this->assets.text_sgt);
    window.draw(this->assets.tna_text);
    for (auto& text : this->assets.chat_texts) {
        window.draw(text);
    }
    for (int i = 0; i < this->width; i++) {
        for(int j = 0; j < this->height; j++) {
            window.draw(this->assets.tiles[i][j]);
        }
    }
    for (auto &monster_sprite : assets.monster_sprites) {
        window.draw(monster_sprite.second.first);
    }
    for (auto &egg_sprite : assets.egg_sprites) {
        window.draw(egg_sprite.second);
    }
}

void GUI::check_event()
{
    std::string cmd;
    std::string server_response;
    std::string player_position;
    std::string player_level;
    std::string player_inventory;

    server_response = ask_server("tna\n");
    draw_cmd(server_response);
    for (auto &monster_sprite : assets.monster_sprites) {
        player_position = ask_server("ppo " + std::to_string(monster_sprite.first) + "\n");
        draw_cmd(player_position);
    }
    if (this->event.type == sf::Event::Closed)
        window.close();
    if (this->event.type == sf::Event::MouseButtonReleased) {
        if (this->event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (this->assets.closeButtonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                window.close();
            }
            if (this->assets.optionsPlusButtonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (this->sgt == 2)
                    this->sgt = 10;
                else
                    this->sgt += 10;
                server_response = ask_server("sst " + std::to_string(this->sgt) + "\n");
                draw_cmd(server_response);
            }
            if (this->assets.optionsMinusButtonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                this->sgt -= 10;
                if (this->sgt <= 1)
                    this->sgt = 2;
                server_response = ask_server("sst " + std::to_string(this->sgt) + "\n");
                draw_cmd(server_response);
            }
            for (auto &monster_sprite : assets.monster_sprites) {
                if (monster_sprite.second.first.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    this->assets.text_pid.setString("Player : " + std::to_string(monster_sprite.first));
                    player_level = ask_server("plv " + std::to_string(monster_sprite.first) + "\n");
                    draw_cmd(player_level);
                    player_inventory = ask_server("pin " + std::to_string(monster_sprite.first) + "\n");
                    draw_cmd(player_inventory);
                }
            }
            for (int i = 0; i < this->width; i++) {
                for(int j = 0; j < this->height; j++) {
                    if (this->assets.tiles[i][j].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        cmd = "bct " + std::to_string(i) + " " + std::to_string(j) + "\n";
                        server_response = ask_server(cmd);
                        draw_cmd(server_response);
                    }
                }
            }
        }
    }
}

void GUI::game_loop()
{
    fd_set read_fds;
    struct timeval tv = {
        .tv_sec = 0,
        .tv_usec = 100000
    };

    while (window.isOpen()) {
        while (window.pollEvent(this->event)) {
            check_event();
        }
        window.clear();
        draw_game();
        this->setup_fd_set(&read_fds, this->clientSocket);
        if (select(this->clientSocket + 1, &read_fds, NULL, NULL, &tv) == -1) {
            std::cout << "Error: select" << std::endl;
            exit(84);
        }
        if (FD_ISSET(this->clientSocket, &read_fds))
            handle_read_server();
        window.display();
    }
}

void GUI::draw_cmd(std::string cmd)
{
    std::string cmd_tag = cmd.substr(0, 3);
    std::string parsed_string = cmd;

    if (cmd_tag.compare("bct") == 0) {
        this->draw_bct(cmd);
        return;
    }
    if (cmd_tag.compare("tna") == 0) {
        this->draw_tna(cmd);
        return;
    }
    if (cmd_tag.compare("pnw") == 0) {
        this->draw_pnw(cmd);
        return;
    }
    if (cmd_tag.compare("ppo") == 0) {
        this->draw_ppo(cmd);
        return;
    }
    if (cmd_tag.compare("plv") == 0) {
        this->assets.text_plv.setString("level: " + cmd.substr(6, 1));
        return;
    }
    if (cmd_tag.compare("pin") == 0) {
        this->draw_pin(cmd);
        return;
    }
    if (cmd_tag.compare("pex") == 0) {
        return;
    }
    if (cmd_tag.compare("pbc") == 0) {
        this->draw_pbc(cmd);
        return;
    }
    if (cmd_tag.compare("pic") == 0) {
        this->draw_pic(cmd);
        return;
    }
    if (cmd_tag.compare("pie") == 0) {
        this->draw_pie(cmd);
        return;
    }
    if (cmd_tag.compare("pfk") == 0) {
        return;
    }
    if (cmd_tag.compare("pdr") == 0) {
        return;
    }
    if (cmd_tag.compare("pgt") == 0) {
        return;
    }
    if (cmd_tag.compare("pdi") == 0) {
        this->draw_pdi(cmd);
        return;
    }
    if (cmd_tag.compare("enw") == 0) {
        this->draw_enw(cmd);
        return;
    }
    if (cmd_tag.compare("ebo") == 0) {
        return;
    }
    if (cmd_tag.compare("edi") == 0) {
        this->draw_edi(cmd);
        return;
    }
    if (cmd_tag.compare("sgt") == 0) {
        this->assets.text_sgt.setString(cmd.substr(4, cmd.size() - 4));
        return;
    }
    if (cmd_tag.compare("seg") == 0) {
        this->window.close();
        return;
    }
    if (cmd_tag.compare("smg") == 0) {
        std::cout << cmd;
        return;
    }
    if (cmd_tag.compare("suc") == 0) {
        std::cout << cmd;
        return;
    }
    if (cmd_tag.compare("sbp") == 0) {
        std::cout << cmd;
        return;
    }
    return;
}
