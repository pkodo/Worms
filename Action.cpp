//
// Created by stefan on 23.04.19.
//

#include "Action.h"

namespace Sep
{
  int Action::execute(Game &game, std::vector<std::string> &params)
  {
    return 0;
  }

  Action::Action(const std::string &name) : Command(name)
  {
  }

  Action::~Action()
  {

  }
}