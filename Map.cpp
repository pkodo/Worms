//
// Created by stefan on 23.04.19.
//

#include "Map.h"
#include "Game.h"

namespace Sep
{
    Map::Map(const std::string &name) : Command(name)
    {
    }

    int Map::execute(Game &game, std::vector<std::string> &params)
    {
        game.printMap();
        return 0;
    }

    Map::~Map()
    = default;

}