//
// Created by stefan on 19.04.19.
//

#include <iostream>
#include "Move.h"
#include "Game.h"

using std::cout;
using std::endl;

namespace Sep
{

  int Move::execute(Game &game, std::vector<std::string> &params)
  {
    int steps = -1;
    if(params.at(1) == "left" || params.at(1) == "right")
    {
      try
      {
        steps = stoi(params.at(2));
      }
      catch(std::invalid_argument)
      {

      }

      if(steps >= 0 && steps <= 3)
      {
        if(params.at(1) == "left")
        {
          steps *= -1;
        }

        game.move(game.getWormNumber().at(current_worm_).getRow(),
                game.getWormNumber().at(current_worm_).getCol(), steps, current_worm_);
       // game.setNextMove(steps);
      }
      else
      {
        return printError(INVALID_STEPCOUNT);
      }

    }
    else
    {
      return printError(INVALID_DIRECTION);
    }
    return EVERYTHING_OK;
  }

  int Move::printError(ErrorType type)
  {
    switch (type)
    {
      case INVALID_STEPCOUNT:
        cout << "[ERROR] invalid step count" << endl;
        break;
      case INVALID_DIRECTION:
        cout << "[ERROR] invalid direction" << endl;
        break;
      case EVERYTHING_OK:
        break;
    }
    return type;
  }

  Move::Move(const std::string &name, int current_worm) : Command(name), current_worm_(current_worm)
  {
  }

  Move::~Move()
  {

  }
}