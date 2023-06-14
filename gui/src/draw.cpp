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
    assets.create_player(player_info.x, player_info.y, player_info.number, player_info.orientation, player_info.team, this->tna);
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
    int id, x, y, o;
    int num_values_parsed = sscanf(cmd.c_str(), "ppo %d %d %d %d\n",
        &id,
        &x,
        &y,
        &o);
    if (num_values_parsed != 4)
        return;
    this->assets.monster_sprites[id].first.setPosition(x * this->assets.box_size + this->assets.rectangle_width + this->assets.box_size / 2, y * this->assets.box_size + this->assets.box_size / 2);
    if (o == 1)
        this->assets.monster_sprites[id].first.setRotation(180);
    else if (o == 2)
        this->assets.monster_sprites[id].first.setRotation(90);
    else if (o == 3)
        this->assets.monster_sprites[id].first.setRotation(0);
    else if (o == 4)
        this->assets.monster_sprites[id].first.setRotation(270);
}

void GUI::draw_pin(std::string cmd)
{
    std::string parsed_cmd = "Inventory :\n";
    int n = 0;
    int x = 0;
    int y = 0;
    int food = 0;
    int linemate = 0;
    int deraumere = 0;
    int sibur = 0;
    int mendiane = 0;
    int phiras = 0;
    int thystame = 0;

    sscanf(cmd.c_str(), "pin %d %d %d %d %d %d %d %d %d %d\n",
        &n,
        &x,
        &y,
        &food,
        &linemate,
        &deraumere,
        &sibur,
        &mendiane,
        &phiras,
        &thystame);
    parsed_cmd += "Food: ";
    parsed_cmd += std::to_string(food);
    parsed_cmd += "\n";
    parsed_cmd += "Linemate: ";
    parsed_cmd += std::to_string(linemate);
    parsed_cmd += "\n";
    parsed_cmd += "Deraumere: ";
    parsed_cmd += std::to_string(deraumere);
    parsed_cmd += "\n";
    parsed_cmd += "Sibur: ";
    parsed_cmd += std::to_string(sibur);
    parsed_cmd += "\n";
    parsed_cmd += "Mendiane: ";
    parsed_cmd += std::to_string(mendiane);
    parsed_cmd += "\n";
    parsed_cmd += "Phiras: ";
    parsed_cmd += std::to_string(phiras);
    parsed_cmd += "\n";
    parsed_cmd += "Thystame: ";
    parsed_cmd += std::to_string(thystame);
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

void GUI::draw_pic(std::string cmd)
{
    std::istringstream iss(cmd);
    std::string prefix;
    int X, Y, L;
    std::vector<int> ns;

    if (iss >> prefix >> X >> Y >> L) {
        int n;
        while (iss >> n) {
        ns.push_back(n);
        }
    }

    for (int n : ns) {
        if (this->assets.monster_sprites[n].second == this->tna[0]) {
            this->assets.monster_sprites[n].first.setTexture(this->assets.monster_red_evolving_texture);
        } else if (this->assets.monster_sprites[n].second == this->tna[1]) {
            this->assets.monster_sprites[n].first.setTexture(this->assets.monster_blue_evolving_texture);
        } else if (this->assets.monster_sprites[n].second == this->tna[2]) {
            this->assets.monster_sprites[n].first.setTexture(this->assets.monster_green_evolving_texture);
        } else if (this->assets.monster_sprites[n].second == this->tna[3]) {
            this->assets.monster_sprites[n].first.setTexture(this->assets.monster_orange_evolving_texture);
        } else if (this->assets.monster_sprites[n].second == this->tna[4]) {
            this->assets.monster_sprites[n].first.setTexture(this->assets.monster_pink_evolving_texture);
        } else
            this->assets.monster_sprites[n].first.setTexture(this->assets.monster_red_evolving_texture);
        this->evolving.push_back(n);
    }
}

void GUI::draw_pie(std::string cmd)
{
    std::istringstream iss(cmd);
    std::string prefix;
    int X, Y, R;

    if (iss >> prefix >> X >> Y >> R) {
        for (int n : this->evolving) {
            if (this->assets.monster_sprites[n].second == this->tna[0]) {
                this->assets.monster_sprites[n].first.setTexture(this->assets.monster_red_texture);
            } else if (this->assets.monster_sprites[n].second == this->tna[1]) {
                this->assets.monster_sprites[n].first.setTexture(this->assets.monster_blue_texture);
            } else if (this->assets.monster_sprites[n].second == this->tna[2]) {
                this->assets.monster_sprites[n].first.setTexture(this->assets.monster_green_texture);
            } else if (this->assets.monster_sprites[n].second == this->tna[3]) {
                this->assets.monster_sprites[n].first.setTexture(this->assets.monster_orange_texture);
            } else if (this->assets.monster_sprites[n].second == this->tna[4]) {
                this->assets.monster_sprites[n].first.setTexture(this->assets.monster_pink_texture);
            } else
                this->assets.monster_sprites[n].first.setTexture(this->assets.monster_red_texture);
        }
        this->evolving.clear();
    }
}
