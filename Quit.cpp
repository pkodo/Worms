//------------------------------------------------------------------------------
// Quit.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger
//          Stefan Wietreich
//------------------------------------------------------------------------------
//

#include "Game.h"
#include "Quit.h"

namespace Sep
{

  //----------------------------------------------------------------------------
  Quit::Quit(const std::string& name) : Command(name)
  {
  }

  //----------------------------------------------------------------------------
  Quit::~Quit()
  = default;

  //----------------------------------------------------------------------------
  int Quit::execute(Game &game, std::vector<std::string>& params)
  {
    game.setQuit(true);
    return 0;
  }
}
