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
    if(params.size() == 1)
    {
      checkOneParameterCommand(game, params);
    }
    else if(params.size() == 2)
    {
      checkTwoParameterCommand(game, params);
    }
    else if(params.size() == 3)
    {
      checkThreeParameterCommand(game, params);
    }
    else
    {
      return 1;
    }
  }

  //----------------------------------------------------------------------------
  int Action::checkOneParameterCommand(Game &game, std::vector<std::string> &params)
  {
    if(game.getWormNumber().at(current_worm_).getCurrentWeapon() == 4) // MELEE
    {
      game.getWormNumber().at(current_worm_).getWeapons().at(4).action();
      return 0;
    }
    return 1;
  }

  //----------------------------------------------------------------------------
  int Action::checkTwoParameterCommand(Game &game, std::vector<std::string> &params)
  {
    int col = 0;

    if((game.getWormNumber().at(current_worm_).getCurrentWeapon() == 0 //GUN
      || game.getWormNumber().at(current_worm_).getCurrentWeapon() == 1 // BAZOOKA
      || game.getWormNumber().at(current_worm_).getCurrentWeapon() == 3)) // BLOWTORCH
    {
      if(params.at(1) == "l") //0
      {
        //Aufruf
      }
      else if(params.at(1) == "r") //1
      {
        //Aufruf
      }
      else if(params.at(1) == "d") //2
      {
        //Aufruf
      }
      else if(params.at(1) == "u") //3
      {

      }
      else if(params.at(1) == "ld") //4
      {

      }
      else if(params.at(1) == "rd") //5
      {

      }
      else if(params.at(1) == "lu") //6
      {

      }
      else if(params.at(1) == "ru") //7
      {

      }
      else if( params.at(1) == "idle")
      {
        return 1;
      }
      else
      {
        return 1;
      }
    }
    else if(game.getWormNumber().at(current_worm_).getCurrentWeapon() == 5)// AIRSTRIKE
    {
      try
      {
        col = stoi(params.at(2));
      }
      catch(std::invalid_argument)
      {

      }
      if(col < 0 || col > game.getBoardWidth())
      {
        return 1;
      }
      //Aufruf ;
      return 0;
    }
  }

  //----------------------------------------------------------------------------
  int Action::checkThreeParameterCommand(Game &game, std::vector<std::string> &params)
  {
    int row = 0;
    int col = 0;
    if(game.getWormNumber().at(current_worm_).getCurrentWeapon() == 3)
    {
      try
      {
        row = stoi(params.at(2));
      }
      catch(std::invalid_argument)
      {
      }
      try
      {
        col = stoi(params.at(2));
      }
      catch(std::invalid_argument)
      {
      }
      if((col < 0 || col > game.getBoardWidth()) || (row < 0 || row > game.getBoardHeight()))
      {
        return 1;
      }
      //Aufruf ;
    }
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