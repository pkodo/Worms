//------------------------------------------------------------------------------
// Move.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#include <iostream>
#include "Move.h"
#include "Game.h"

namespace Sep
{

  //----------------------------------------------------------------------------
  int Move::execute(Game& game, std::vector<std::string>& params)
  {
    int steps = -1;
    if(params.at(1) == "l" || params.at(1) == "r")
    {
      try
      {
        steps = stoi(params.at(2));
      }
      catch(std::invalid_argument &invalidArgument)
      {

      }

      if(steps >= 0 && steps <= 3)
      {
        if(params.at(1) == "l")
        {
          steps *= -1;
        }
        game.move(game.getWormNumber().at(current_worm_).getRow(),
                  game.getWormNumber().at(current_worm_).getCol(),
                  steps, current_worm_);
      }
      else
      {
        return INVALID_PARAMETER;
      }
    }
    else
    {
      return INVALID_PARAMETER;
    }
    game.printMap();
    return EVERYTHING_OK;
  }

  //----------------------------------------------------------------------------
  Move::Move(const std::string& name, int current_worm) : Command(name),
                                            current_worm_(current_worm)
  {
  }

  //----------------------------------------------------------------------------
  Move::~Move()
  = default;

}
