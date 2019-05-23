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
  Play::Play(const std::string& name, int current_worm) : Command(name),
            current_worm_(current_worm)
  {
  }

  //----------------------------------------------------------------------------
  Play::~Play()
  {
  }

  //----------------------------------------------------------------------------
  int Play::execute(Game& game, std::vector<std::string>& params)
  {
    bool team = false;
    if(current_worm_ < 3)
    {
      team = true; // Team 1
    }
    game.setGhostMode(true);
    game.playCommand(current_worm_, team);
    return EVERYTHING_OK;
  }
}