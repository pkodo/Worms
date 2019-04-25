//
// Created by stefan on 23.04.19.
//

#ifndef SEP19_GROUP21486_CHOOSE_H
#define SEP19_GROUP21486_CHOOSE_H

#include "Command.h"
#include <string>

using std::string;

namespace Sep
{
  class Choose : public Command
  {
    public:
      Choose(const std::string &name, int current_worm);

      int execute(Game &game, std::vector<std::string> &params) override;

      virtual ~Choose();

    private:
      enum ErrorType
      {
          EVERYTHING_OK,
          INVALID_CONFIGFILE,
      };
      int current_worm_;

      const string GUN = "gun";
      const string BAZOOKA = "bazooka";
      const string TELEPORT = "teleport";
      const string BLOWTORCH = "blowtorch";
      const string MELEE = "melee";
      const string AIRSTRIKE = "airstrike";

  };
}

#endif //SEP19_GROUP21486_CHOOSE_H
