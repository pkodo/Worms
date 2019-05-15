//
// Created by stefan on 15.05.19.
//

#ifndef SEP19_GROUP21486_WHOAMI_H
#define SEP19_GROUP21486_WHOAMI_H

#include "Command.h"

namespace Sep
{
  class Whoami : public Command
  {
    public:
    Whoami(const std::string &name);

    virtual ~Whoami();

    int execute(Game &game, std::vector<std::string> &params) override;
  };
}

#endif //SEP19_GROUP21486_WHOAMI_H
