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
