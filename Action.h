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

      Action(const std::string &name, int current_worm);

      int execute(Game &game, std::vector<std::string> &params) override;

      virtual ~Action();

    private:
      int current_worm_;

      bool checkOneParameterCommand(Game &game, int current_weapon);

      bool checkTwoParameterCommand(Game &game, std::vector<std::string> &params, int current_weapon);

      bool checkAirstrikeCommand(Game &game, std::vector<std::string> &params, int current_weapon);

      bool checkThreeParameterCommand(Game &game, std::vector<std::string> &params, int current_weapon);
  };
}

#endif //SEP19_GROUP21486_ACTION_H
