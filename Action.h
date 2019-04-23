//
// Created by stefan on 23.04.19.
//

#ifndef SEP19_GROUP21486_ACTION_H
#define SEP19_GROUP21486_ACTION_H

#include "Command.h"

namespace Sep
{
  class Action : public Command
  {
    public:
    Action(const std::string &name);

    int execute(Game &game, std::vector<std::string> &params) override;

    virtual ~Action();

  };
}

#endif //SEP19_GROUP21486_ACTION_H
