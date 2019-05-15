//
// Created by stefan on 15.05.19.
//

#ifndef SEP19_GROUP21486_PLAY_H
#define SEP19_GROUP21486_PLAY_H

#include "Command.h"

namespace Sep
{
  class Play : public Command
  {
    public:
    Play(const std::string &name);

    virtual ~Play();

    int execute(Game &game, std::vector<std::string> &params) override;
  };
}


#endif //SEP19_GROUP21486_PLAY_H
