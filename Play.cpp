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


#include "Play.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  Play::Play(const std::string &name) : Command(name)
  {
  }

  //----------------------------------------------------------------------------
  Play::~Play()
  {
  }

  //----------------------------------------------------------------------------
  int Play::execute(Game &game, std::vector<std::string> &params)
  {
    // TODO
    return 0;
  }
}