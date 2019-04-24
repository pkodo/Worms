//
// Created by stefan on 19.04.19.
//

#ifndef SEP19_GROUP21486_MOVE_H
#define SEP19_GROUP21486_MOVE_H

#include "Command.h"

namespace Sep
{
  class Move : public Command
  {
    public:
      Move(const std::string &name, int current_worm);

      int execute(Game &game, std::vector<std::string> &params) override;

      virtual ~Move();

    private:

    enum ErrorType
    {
       EVERYTHING_OK,
       INVALID_PARAMETER
    };

    int current_worm_;
  };
}

#endif //SEP19_GROUP21486_MOVE_H
