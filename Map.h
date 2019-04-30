//
// Created by stefan on 23.04.19.
//

#ifndef SEP19_GROUP21486_MAP_H
#define SEP19_GROUP21486_MAP_H

#include "Command.h"

namespace Sep
{
  class Map : public Command
  {
  public:
      explicit Map(const std::string &name);

      int execute(Game &game, std::vector<std::string> &params) override;

      ~Map() override;

  };
}

#endif //SEP19_GROUP21486_MAP_H
