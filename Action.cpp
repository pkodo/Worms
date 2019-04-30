//
// Created by stefan on 23.04.19.
//

#include "Action.h"
#include "Game.h"

namespace Sep
{

  //----------------------------------------------------------------------------
  int Action::execute(Game &game, std::vector<std::string> &params)
  {
    int current_weapon = game.getWormNumber().at(current_worm_).getCurrentWeapon();
    if(params.size() == 1)
    {
      if(checkOneParameterCommand(game, params, current_weapon))
      {
        return 0;
      }
    }
    if(params.size() == 2)
    {
      if(checkTwoParameterCommand(game, params, current_weapon)
         || checkAirstrikeCommand(game, params, current_weapon))
      {
        return 0;
      }
    }
    if(params.size() == 3)
    {
      if(checkThreeParameterCommand(game, params, current_weapon))
      {
        return 0;
      }
    }
    return 1;
  }

  //----------------------------------------------------------------------------
  bool Action::checkOneParameterCommand(Game &game, std::vector<std::string> &params, int current_weapon)
  {
    if(current_weapon == 4) // MELEE
    {
      game.actionCommand(current_worm_, current_weapon,
              game.getWormNumber().at(current_worm_).getWeapons().at(current_weapon).getDamage());
      return true;
    }
    return false;
  }

  //----------------------------------------------------------------------------
  bool Action::checkTwoParameterCommand(Game &game, std::vector<std::string> &params, int current_weapon)
  {
    if((current_weapon == 0 //GUN
      || current_weapon == 1 // BAZOOKA
      || current_weapon == 3)) // BLOWTORCH
    {
      if(params.at(1) == "l") // 0
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().at(current_weapon).getDamage(), 0);
        return true;
      }
      else if(params.at(1) == "r") //1
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().at(current_weapon).getDamage(), 1);
        return true;
      }
      else if(params.at(1) == "d") //2
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().at(current_weapon).getDamage(), 2);
        return true;
      }
      else if(params.at(1) == "u") //3
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().at(current_weapon).getDamage(), 3);
        return true;
      }
      else if(params.at(1) == "ld") //4
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().at(current_weapon).getDamage(), 4);
        return true;
      }
      else if(params.at(1) == "rd") //5
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().at(current_weapon).getDamage(), 5);
        return true;
      }
      else if(params.at(1) == "lu") //6
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().at(current_weapon).getDamage(), 6);
        return true;
      }
      else if(params.at(1) == "ru") //7
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().at(current_weapon).getDamage(), 7);
        return true;
      }
    }
    if(params.at(1) == "idle")
    {
      return true;
    }
    return false;
}

  bool Action::checkAirstrikeCommand(Game &game, std::vector<std::string> &params, int current_weapon)
  {
    int col = 0;
    if(current_weapon == 5)// AIRSTRIKE
    {
      try
      {
        col = stoi(params.at(1));
      }
      catch(std::invalid_argument &invalidArgument)
      {

      }
      if(col < 0 || col > game.getBoardWidth())
      {
        return false;
      }
      game.actionColCommand(current_worm_, current_weapon,
              game.getWormNumber().at(current_worm_).getWeapons().at(current_weapon).getDamage(), col);
      return true;
    }
    else
    {
      return false;
    }
  }

  //----------------------------------------------------------------------------
  bool Action::checkThreeParameterCommand(Game &game, std::vector<std::string> &params, int current_weapon)
  {
    int row = 0;
    int col = 0;
    if(game.getWormNumber().at(current_worm_).getCurrentWeapon() == 2) // teleport
    {
      try
      {
        row = stoi(params.at(1));
      }
      catch(std::invalid_argument &invalidArgument)
      {
      }
      try
      {
        col = stoi(params.at(2));
      }
      catch(std::invalid_argument &invalidArgument1)
      {
      }
      if(((col < 0 || col > game.getBoardWidth()) || (row < 0 || row > game.getBoardHeight())) ||
          game.getWormNumber().at(current_worm_).getWeapons().at(current_weapon).getAmmo() <= 0)
      {
        return false;
      }
      game.actionRowColCommand(current_worm_, current_weapon, row, col);
    }
    return true;
  }

  //----------------------------------------------------------------------------
  Action::Action(const std::string &name, int current_worm) : Command(name),
                                                current_worm_(current_worm)
  {
  }

  //----------------------------------------------------------------------------
  Action::~Action()
  {

  }
}