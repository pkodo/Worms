//------------------------------------------------------------------------------
// Action.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//
#include "Action.h"
#include "Game.h"

namespace Sep
{

  //----------------------------------------------------------------------------
  int Action::execute(Game& game, std::vector<std::string>& params)
  {
    int current_weapon = game.getWormNumber().at(current_worm_).
                              getCurrentWeapon();
    if(params.size() == 1)
    {
      if(checkOneParameterCommand(game, current_weapon))
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
  bool Action::checkOneParameterCommand(Game& game, int current_weapon)
  {
    if(current_weapon == MELEE)
    {
      game.actionCommand(current_worm_, current_weapon,
              game.getWormNumber().at(current_worm_).getWeapons()
              .at(current_weapon).getDamage());
      return true;
    }
    return false;
  }

  //----------------------------------------------------------------------------
  bool Action::checkTwoParameterCommand(Game& game,
                   std::vector<std::string>& params, int current_weapon)
  {
    if(current_weapon == GUN
      || current_weapon == BAZOOKA
      || current_weapon == BLOWTORCH)
    {
      if(params.at(1) == "l") // 0
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().
                at(current_weapon).getDamage(), LEFT);
        return true;
      }
      else if(params.at(1) == "r") //1
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().
                at(current_weapon).getDamage(), RIGHT);
        return true;
      }
      else if(params.at(1) == "d") //2
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().
                at(current_weapon).getDamage(), DOWN);
        return true;
      }
      else if(params.at(1) == "u") //3
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().
                at(current_weapon).getDamage(), UP);
        return true;
      }
      else if(params.at(1) == "ld") //4
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().
                at(current_weapon).getDamage(), LEFT_DOWN);
        return true;
      }
      else if(params.at(1) == "rd") //5
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().
                at(current_weapon).getDamage(), RIGHT_DOWN);
        return true;
      }
      else if(params.at(1) == "lu") //6
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().
                at(current_weapon).getDamage(), LEFT_UP);
        return true;
      }
      else if(params.at(1) == "ru") //7
      {
        game.actionDirectionCommand(current_worm_, current_weapon,
                game.getWormNumber().at(current_worm_).getWeapons().
                at(current_weapon).getDamage(), RIGHT_UP);
        return true;
      }
    }
    return params.at(1) == "idle";
  }

  //----------------------------------------------------------------------------
  bool Action::checkAirstrikeCommand(Game& game,
               std::vector<std::string>& params, int current_weapon)
  {
    int col = 0;
    if(current_weapon == AIRSTRIKE)
    {
      try
      {
        col = stoi(params.at(1));
      }
      catch(std::invalid_argument& invalidArgument)
      {

      }
      if(col < 0 || col > game.getBoardWidth())
      {
        return false;
      }
      game.actionColCommand(current_worm_, current_weapon,
         game.getWormNumber().at(current_worm_).getWeapons().at(current_weapon).
         getDamage(), col);
      return true;
    }
    else
    {
      return false;
    }
  }

  //----------------------------------------------------------------------------
  bool Action::checkThreeParameterCommand(Game& game,
                   std::vector<std::string>& params, int current_weapon)
  {
    int row = 0;
    int col = 0;
    if(game.getWormNumber().at(current_worm_).getCurrentWeapon()
         == TELEPORT)
    {
      try
      {
        row = stoi(params.at(1));
      }
      catch(std::invalid_argument& invalidArgument)
      {
      }
      try
      {
        col = stoi(params.at(2));
      }
      catch(std::invalid_argument& invalidArgument1)
      {
      }
      if(((col < 0 || col > game.getBoardWidth()) || (row < 0 || row > game.
          getBoardHeight())) || game.getWormNumber().at(current_worm_).
          getWeapons().at(current_weapon).getAmmo() <= 0)
      {
        return false;
      }
      if(game.actionRowColCommand(current_worm_, current_weapon, row, col))
      {
         return true;
      }
    }
    return false;
  }

  //----------------------------------------------------------------------------
  Action::Action(const std::string& name, int current_worm) : Command(name),
                                                current_worm_(current_worm)
  {
  }

  //----------------------------------------------------------------------------
  Action::~Action()
  = default;
}
