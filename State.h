//
// Created by stefan on 23.04.19.
//

#ifndef SEP19_GROUP21486_STATE_H
#define SEP19_GROUP21486_STATE_H

#include "Command.h"

namespace Sep
{
  class State : public Command
  {
  public:
      State(const std::string &name, int current_worm);

      int execute(Game &game, std::vector<std::string> &params) override;

      virtual ~State();

  private:
      int current_worm_;


  };
}

#endif //SEP19_GROUP21486_STATE_H
