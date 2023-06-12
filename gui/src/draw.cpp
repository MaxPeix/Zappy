/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** draw.cpp
*/

#include "gui.hpp"

void GUI::draw_bct(std::string cmd)
{
    std::string parsed_cmd = "Tile content :\n";


    parsed_cmd += "food: ";
    parsed_cmd += cmd[4];
    parsed_cmd += "\n";
    parsed_cmd += "linemate: ";
    parsed_cmd += cmd[6];
    parsed_cmd += "\n";
    parsed_cmd += "deraumere: ";
    parsed_cmd += cmd[8];
    parsed_cmd += "\n";
    parsed_cmd += "sibur: ";
    parsed_cmd += cmd[10];
    parsed_cmd += "\n";
    parsed_cmd += "mendiane: ";
    parsed_cmd += cmd[12];
    parsed_cmd += "\n";
    parsed_cmd += "phiras: ";
    parsed_cmd += cmd[14];
    parsed_cmd += "\n";
    parsed_cmd += "thystame: ";
    parsed_cmd += cmd[16];
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
