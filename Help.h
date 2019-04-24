//
// Created by stefan on 23.04.19.
//

#ifndef SEP19_GROUP21486_HELP_H
#define SEP19_GROUP21486_HELP_H

#include "Command.h"

namespace Sep
{
  class Help : public Command
  {
  public:
      Help(const std::string &name);

      int execute(Game &game, std::vector<std::string> &params) override;

      virtual ~Help();

  };
}

#endif //SEP19_GROUP21486_HELP_H