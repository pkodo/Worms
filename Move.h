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
      Move(const std::string &name);

      int execute(Game &game, std::vector<std::string> &params) override;

      virtual ~Move();

    private:
      enum ErrorType {EVERYTHING_OK = 0, INVALID_STEPCOUNT = -1,
      INVALID_DIRECTION = -2};

    int printError(ErrorType type);
  };
}

#endif //SEP19_GROUP21486_MOVE_H
