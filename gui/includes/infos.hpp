/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** infos.hpp
*/

#pragma once

#include <iostream>
#include <vector>

class Info {
    public:
        Info();
        ~Info();
        std::string info_text;
        std::string chat_text;
        std::vector<std::string> tna;
        std::vector<std::string> players;
};