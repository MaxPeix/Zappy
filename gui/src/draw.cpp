/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** draw.cpp
*/

#include "gui.hpp"

void GUI::draw_bct(std::string cmd)
{
    std::string parsed_cmd = "Tile content : ";
    int x = 0;
    int y = 0;
    int food = 0;
    int linemate = 0;
    int deraumere = 0;
    int sibur = 0;
    int mendiane = 0;
    int phiras = 0;
    int thystame = 0;

    sscanf(cmd.c_str(), "bct %d %d %d %d %d %d %d %d %d\n",
        &x,
        &y,
        &food,
        &linemate,
        &deraumere,
        &sibur,
        &mendiane,
        &phiras,
        &thystame);
    parsed_cmd += std::to_string(x);
    parsed_cmd += " ";
    parsed_cmd += std::to_string(y);
    parsed_cmd += "\n";
    parsed_cmd += "Food : ";
    parsed_cmd += std::to_string(food);
    parsed_cmd += "\n";
    parsed_cmd += "Linemate : ";
    parsed_cmd += std::to_string(linemate);
    parsed_cmd += "\n";
    parsed_cmd += "Deraumere : ";
    parsed_cmd += std::to_string(deraumere);
    parsed_cmd += "\n";
    parsed_cmd += "Sibur : ";
    parsed_cmd += std::to_string(sibur);
    parsed_cmd += "\n";
    parsed_cmd += "Mendiane : ";
    parsed_cmd += std::to_string(mendiane);
    parsed_cmd += "\n";
    parsed_cmd += "Phiras : ";
    parsed_cmd += std::to_string(phiras);
    parsed_cmd += "\n";
    parsed_cmd += "Thystame : ";
    parsed_cmd += std::to_string(thystame);
    parsed_cmd += "\n";
    this->assets.text_bct.setString(parsed_cmd);
}

void GUI::draw_tna(std::string cmd)
{
    std::string parsed_cmd = "";

    std::vector<std::string> teamNames;
    std::string currentTeamName = "";
    for (std::string::size_type i = 4; i < cmd.size(); i++) {
        if (cmd[i] == '\n' || cmd[i] == '\0') {
            if (!currentTeamName.empty()) {
                teamNames.push_back(currentTeamName);
                currentTeamName.clear();
                i += 4;
            }
        } else {
            currentTeamName += cmd[i];
        }
    }

    for (std::vector<std::string>::size_type i = 0; i < teamNames.size(); i++) {
        parsed_cmd += teamNames[i];

        if (i < teamNames.size() - 1) {
            parsed_cmd += "\n\n";
        }
    }

    this->assets.tna_text.setString(parsed_cmd);
}

void GUI::draw_pnw(std::string cmd)
{
    int num_values_parsed = sscanf(cmd.c_str(), "pnw %d %d %d %d %d %s\n",
        &player_info.number,
        &player_info.x,
        &player_info.y,
        &player_info.orientation, 
        &player_info.level,
        player_info.team);
    if (num_values_parsed != 6)
        return;
    assets.create_player(player_info.x, player_info.y, player_info.number);
}

void GUI::draw_pdi(std::string cmd)
{
    sscanf(cmd.c_str(), "pdi %d\n", &player_info.number);
    this->assets.delete_player(player_info.number);
}

void GUI::draw_enw(std::string cmd)
{
    int x, y, id;
    int tmp;
    int num_values_parsed = sscanf(cmd.c_str(), "enw %d %d %d %d\n",
        &id,
        &tmp,
        &x,
        &y);
    if (num_values_parsed != 4)
        return;
    assets.create_egg(x, y, id);
}


void GUI::draw_edi(std::string cmd)
{
    int id;
    int num_values_parsed = sscanf(cmd.c_str(), "edi %d\n", &id);
    if (num_values_parsed != 1)
        return;
    assets.delete_egg(id);
}

void GUI::draw_ppo(std::string cmd)
{
    int id = std::stoi(cmd.substr(4, 1));
    int x = std::stoi(cmd.substr(6, 1));
    int y = std::stoi(cmd.substr(8, 1));
    this->assets.monster_sprites[id].setPosition(x * this->assets.box_size + this->assets.rectangle_width, y * this->assets.box_size);
}

void GUI::draw_pin(std::string cmd)
{
    std::string parsed_cmd = "Inventory :\n";
    parsed_cmd += "Food: ";
    parsed_cmd += cmd[4];
    parsed_cmd += "\n";
    parsed_cmd += "Linemate: ";
    parsed_cmd += cmd[6];
    parsed_cmd += "\n";
    parsed_cmd += "Deraumere: ";
    parsed_cmd += cmd[8];
    parsed_cmd += "\n";
    parsed_cmd += "Sibur: ";
    parsed_cmd += cmd[10];
    parsed_cmd += "\n";
    parsed_cmd += "Mendiane: ";
    parsed_cmd += cmd[12];
    parsed_cmd += "\n";
    parsed_cmd += "Phiras: ";
    parsed_cmd += cmd[14];
    parsed_cmd += "\n";
    parsed_cmd += "Thystame: ";
    parsed_cmd += cmd[16];
    parsed_cmd += "\n";
    this->assets.text_pin.setString(parsed_cmd);
}

void GUI::draw_pbc(std::string cmd)
{
    cmd.replace(0, 3, "Player");
    this->assets.chat_messages_string.push_back(cmd);
    this->assets.new_text.setString(cmd);
    this->assets.new_text.setPosition(10, 1080 / 3 + 60 + (this->assets.chat_messages_string.size() - 1) * 30);
    this->assets.chat_texts.push_back(this->assets.new_text);

    if (this->assets.chat_texts.size() > 5) {
        this->assets.chat_texts.erase(this->assets.chat_texts.begin());
        this->assets.chat_messages_string.erase(this->assets.chat_messages_string.begin());
        for (unsigned int i = 0; i < this->assets.chat_texts.size(); i++) {
            this->assets.chat_texts[i].setPosition(10, 1080 / 3 + 60 + i * 30);
        }
    }
}
