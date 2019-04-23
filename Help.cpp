//
// Created by stefan on 23.04.19.
//

#include "Help.h"
#include <iostream>

namespace Sep
{
    Help::Help(const std::string &name) : Command(name)
    {
    }

    int Help::execute(Game &game, std::vector<std::string> &params)
    {
        std::cout << "Available commands:\n" << "  move [left/right] [0..3]\n" <<
            "    Move your worm.\n" << "  choose [weapon]\n" << "    Select your weapon.\n"
            << "  action [l/r/d/u/ld/rd/lu/ru]\n" << "    Shoots current weapon.\n"
            << "    Activates blowtorch.\n" << "  action\n" << "    Activates melee attack.\n"
            << "  action [row] [col]\n" << "    Teleports to coordinate.\n" << "  action [col]\n"
            << "    Airstrike.\n" << "  action idle\n" << "    Do nothing.\n" << "  quit\n"
            << "    End the game.\n" << "  help\n" << "    Display this help.\n" <<
            "  state\n" << "    Print the current game state." << std::endl;

        return 0;
    }

    Help::~Help()
    {
    }

}