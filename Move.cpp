//
// Created by stefan on 19.04.19.
//

#include <iostream>
#include "Move.h"
#include "Game.h"


namespace Sep
{
  int steps = -1;
  int Move::execute(Sep::Game &game, std::vector<std::string> &params)
  {
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
        game.move(1, 1, steps);
      }
      else
      {

      }

    }
    else
    {
      //Error
    }
    return 0;
  }

  Move::Move(const std::string &name) : Command(name)
  {
  }

  Move::~Move()
  {

  }
}