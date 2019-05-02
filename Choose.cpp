//------------------------------------------------------------------------------
// Choose.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger
//          Stefan Wietreich
//------------------------------------------------------------------------------
//

#include "Choose.h"
#include "Game.h"

namespace Sep
{

  //----------------------------------------------------------------------------
  int Choose::execute(Game &game, std::vector<std::string> &params)
  {
    return game.chooseWeapon(current_worm_, params);
  }

  //----------------------------------------------------------------------------
  Choose::~Choose()
  = default;

  //----------------------------------------------------------------------------
  Choose::Choose(const std::string &name, int current_worm) : Command(name),
                  current_worm_(current_worm)
  {
  }

}
