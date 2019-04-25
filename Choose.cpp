//
// Created by stefan on 23.04.19.
//

#include "Choose.h"
#include "Game.h"
#include "Weapon.h"
#include <iostream>

namespace Sep
{

  int Choose::execute(Game &game, std::vector<std::string> &params)
  {
    if(params.at(1) == GUN)
    {
      game.getWormNumber().at(current_worm_).setCurrentWeapon(0);
      std::cout << "Chose weapon gun Ammunition: " <<
        game.getWormNumber().at(current_worm_).getCurrentWeapon().getAmmo() << std::endl;
    }
    else if(params.at(1) == BAZOOKA)
    {
      game.getWormNumber().at(current_worm_).setCurrentWeapon(1);
      std::cout << "Chose weapon bazooka Ammunition: " <<
                game.getWormNumber().at(current_worm_).getCurrentWeapon().getAmmo() << std::endl;
    }
    else if(params.at(1) == TELEPORT)
    {
      game.getWormNumber().at(current_worm_).setCurrentWeapon(2);
      std::cout << "Chose weapon teleport Ammunition: " <<
                game.getWormNumber().at(current_worm_).getCurrentWeapon().getAmmo() << std::endl;
    }
    else if(params.at(1) == BLOWTORCH)
    {
      game.getWormNumber().at(current_worm_).setCurrentWeapon(3);
      std::cout << "Chose weapon blowtorch Ammunition: " <<
                game.getWormNumber().at(current_worm_).getCurrentWeapon().getAmmo() << std::endl;
    }
    else if(params.at(1) == MELEE)
    {
      game.getWormNumber().at(current_worm_).setCurrentWeapon(4);
      std::cout << "Chose weapon melee Ammunition: " <<
                game.getWormNumber().at(current_worm_).getCurrentWeapon().getAmmo() << std::endl;
    }
    else if(params.at(1) == AIRSTRIKE)
    {
      game.getWormNumber().at(current_worm_).setCurrentWeapon(5);
      std::cout << "Chose weapon airstrike Ammunition: " <<
                game.getWormNumber().at(current_worm_).getCurrentWeapon().getAmmo() << std::endl;
    }
    else
    {
      return 1;
    }
    return 0;
  }

  Choose::~Choose()
  {

  }

  Choose::Choose(const std::string &name, int current_worm) : Command(name), current_worm_(current_worm)
  {

  }
}