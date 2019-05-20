//------------------------------------------------------------------------------
// Play.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#include "Game.h"
#include "Play.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  Play::Play(const std::string &name, int current_worm) : Command(name),
            current_worm_(current_worm)
  {
  }

  //----------------------------------------------------------------------------
  Play::~Play()
  {
  }

  //----------------------------------------------------------------------------
  int Play::execute(Game &game, std::vector<std::string> &params)
  {
    int team = 0;
    if(current_worm_ < 3)
    {
      team = 3; // Team 1
    }
    game.playCommand(current_worm_, team);
  }
}