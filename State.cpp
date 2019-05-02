//------------------------------------------------------------------------------
// State.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger
//          Stefan Wietreich
//------------------------------------------------------------------------------
//

#include "State.h"
#include "Game.h"
#include <iostream>

using std::cout;
using std::endl;

namespace Sep
{
  //----------------------------------------------------------------------------
  State::State(const std::string& name, int current_worm) : Command(name),
               current_worm_(current_worm)
  {
  }

  //----------------------------------------------------------------------------
  int State::execute(Game& game, std::vector<std::string>& params)
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
    cout << "current worm: " << game.getWormNumber().at(current_worm_).
         getName() << " (" << game.getWormNumber().at(current_worm_).
         getId() << ") \n" << endl;

    for(index = 0; index < 6 ; index++)
    {
      if(index == 0)
      {
        cout << "weapons of current worm:\n" <<  "  gun (ammunition: inf)";
        if(game.getWormNumber().at(current_worm_).getCurrentWeapon()
               == index)
        {
          cout << " *" << endl;
        }
        else
        {
          cout << endl;
        }
      }
      else if(game.getWormNumber().at(current_worm_).getWeapons().at(index).
              getAmmo() > 0)
      {
        cout << "  " << game.getWormNumber().at(current_worm_).
           getWeapons().at(index).getName()
           << " (ammunition: " << game.getWormNumber().
           at(current_worm_).getWeapons().at(index).getAmmo()  << ")";
        if(game.getWormNumber().at(current_worm_).getCurrentWeapon()
               == index)
        {
          cout << " *" << endl;
        }
        else
        {
          cout << endl;
        }
      }
    }
    cout << endl;
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
        cout << "  " << game.getWormNumber().at(index).getName()
             << " (" <<
             game.getWormNumber().at(index).getId() << ") " <<
             game.getWormNumber().at(index).getHp() << " HP (" <<
             game.getWormNumber().at(index).getRow() << ", " <<
             game.getWormNumber().at(index).getCol() << ") *" << endl;
      }
    }
    return 0;
  }

  //----------------------------------------------------------------------------
  State::~State()
  = default;


}
