//
// Created by stefan on 23.04.19.
//

#include "Action.h"
#include "Game.h"

namespace Sep
{
  int Action::execute(Game &game, std::vector<std::string> &params)
  {
    game.getWormNumber().at(current_worm_).getWeapons().at(0); // TODO
    return 0;
  }

  Action::Action(const std::string &name, int current_worm) : Command(name),
                                                              current_worm_(
                                                                current_worm)
  {
  }

  Action::~Action()
  {

  }
}