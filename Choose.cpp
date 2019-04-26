//
// Created by stefan on 23.04.19.
//

#include "Choose.h"
#include "Game.h"

namespace Sep
{

  int Choose::execute(Game &game, std::vector<std::string> &params)
  {
      return game.chooseWeapon(current_worm_, params);
  }

  Choose::~Choose()
  {

  }

  Choose::Choose(const std::string &name, int current_worm) : Command(name), current_worm_(current_worm)
  {

  }
}