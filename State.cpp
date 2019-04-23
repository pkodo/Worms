//
// Created by stefan on 23.04.19.
//

#include "State.h"
#include "Game.h"
#include <iostream>

using std::cout;
using std::endl;

namespace Sep
{
    State::State(const std::string &name,int current_worm) : Command(name), current_worm_(current_worm)
    {

    }

    int State::execute(Game &game, std::vector<std::string> &params)
    {
        int index;
        if(game.getWormNumber().at(current_worm_).getId() <= 3)
        {
            cout << "current player: 1" << std::endl;
        }
        else
        {
            cout << "current player: 2" << std::endl;
        }
        cout << "current worm: " << game.getWormNumber().at(current_worm_).getName() << " ("
            << game.getWormNumber().at(current_worm_).getId() << ") \n" << endl;

        cout << "weapons of current worm:\n" << "gun (ammunition: inf)\n" <<
            "bazooka (ammunition: fehlt)\n" << "teleport (ammunition: fehlt)\n"
            << "blowtorch (ammunition: fehlt)\n" << "melee (ammunition: fehlt)\n"
            << "airstrike (ammunition: fehlt)\n" << endl;

        cout << "worms of player 1" << endl;
        for(index = 0; index < 3; index++)
        {
            if(game.getWormNumber().at(index).getHp() > 0)
            {
                cout << "  " << game.getWormNumber().at(index).getName() << " (" <<
                    game.getWormNumber().at(index).getId() << ") " <<
                    game.getWormNumber().at(index).getHp() << " HP (" <<
                    game.getWormNumber().at(index).getRow() << ", " <<
                    game.getWormNumber().at(index).getCol() << ") ~" << endl;
            }
        }
        cout << "worms of player 2" << endl;
        for(index = 3; index < 6; index++)
        {
            if(game.getWormNumber().at(index).getHp() > 0)
            {
                cout << "  " << game.getWormNumber().at(index).getName() << " (" <<
                     game.getWormNumber().at(index).getId() << ") " <<
                     game.getWormNumber().at(index).getHp() << " HP (" <<
                     game.getWormNumber().at(index).getRow() << ", " <<
                     game.getWormNumber().at(index).getCol() << ") *" << endl;
            }
        }
        return 0;
    }

    State::~State()
    {

    }


}