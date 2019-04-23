//
// Created by stefan on 23.04.19.
//

#ifndef SEP19_GROUP21486_CHOOSE_H
#define SEP19_GROUP21486_CHOOSE_H

#include "Command.h"

namespace Sep
{
  class Choose : public Command
  {
    public:
    Choose(const std::string &name);

    int execute(Game &game, std::vector<std::string> &params) override;

    virtual ~Choose();

  };
}

#endif //SEP19_GROUP21486_CHOOSE_H
