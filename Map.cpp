//------------------------------------------------------------------------------
// Map.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#include "Map.h"
#include "Game.h"

namespace Sep
{

  //----------------------------------------------------------------------------
  Map::Map(const std::string& name) : Command(name)
  {
  }

  //----------------------------------------------------------------------------
  int Map::execute(Game& game, std::vector<std::string>& params)
  {
    game.printMap();
    return 0;
  }

  //----------------------------------------------------------------------------
  Map::~Map()
  = default;

}
