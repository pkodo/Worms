//
// Created by stefan on 15.05.19.
//

#include "Play.h"

namespace Sep
{

  Play::Play(const std::string &name) : Command(name)
  {
  }

  Play::~Play()
  {

  }

  int Play::execute(Game &game, std::vector<std::string> &params)
  {
    // TODO
    return 0;
  }
}