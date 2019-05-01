//
// Created by stefan on 01.05.19.
//

#include "Game.h"
#include "Quit.h"

namespace Sep
{

  Quit::Quit(const std::string& name) : Command(name)
  {
  }

  Quit::~Quit()
  = default;

  int Quit::execute(Game &game, std::vector<std::string>& params)
  {
    game.setQuit(true);
    return 0;
  }
}
