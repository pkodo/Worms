//
// Created by stefan on 23.04.19.
//

#include "Choose.h"
#include "Game.h"

namespace Sep
{


  int Choose::execute(Game &game, std::vector<std::string> &params)
  {
    if(params.at(1) == GUN)
    {
      //game.getWormNumber().at(current_worm_).setCurrentWeapon();
    }
    else if(params.at(1) == BAZOOKA)
    {
      //game.getWormNumber().at(current_worm_).setCurrentWeapon();
    }
    else if(params.at(1) == TELEPORT)
    {
      //game.getWormNumber().at(current_worm_).setCurrentWeapon();
    }
    else if(params.at(1) == BLOWTORCH)
    {
      //game.getWormNumber().at(current_worm_).setCurrentWeapon();
    }
    else if(params.at(1) == MELEE)
    {
      //game.getWormNumber().at(current_worm_).setCurrentWeapon();
    }
    else if(params.at(1) == AIRSTRIKE)
    {
      //game.getWormNumber().at(current_worm_).setCurrentWeapon();
    }

    return 0;
  }

  Choose::~Choose()
  {

  }

  Choose::Choose(const std::string &name, int current_worm) : Command(name)
  {

  }
}