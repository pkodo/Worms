//
// Created by stefan on 23.04.19.
//

#ifndef SEP19_GROUP21486_ACTION_H
#define SEP19_GROUP21486_ACTION_H

#include "Command.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Action Class
  // class to execute the Command
  //
  class Action : public Command
  {
    public:
      //------------------------------------------------------------------------
      // Constructor
      //
      Action(const std::string& name, int current_worm);

      //------------------------------------------------------------------------
      // Method
      // used to execute the command
      int execute(Game& game, std::vector<std::string>& params) override;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Action object to another. Is set to delete.
      // @param action Original with values to copy.
      //
      Action& operator = (Action& action) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      ~Action() override;

    private:
      //------------------------------------------------------------------------
      // Variable for saving the command for current worm
      //
      int current_worm_;

      bool checkOneParameterCommand(Game& game, int current_weapon);

      bool checkTwoParameterCommand(Game& game,
           std::vector<std::string>& params, int current_weapon);

      bool checkAirstrikeCommand(Game& game,
           std::vector<std::string>& params, int current_weapon);

      bool checkThreeParameterCommand(Game& game,
           std::vector<std::string>& params, int current_weapon);
  };
}

#endif //SEP19_GROUP21486_ACTION_H
