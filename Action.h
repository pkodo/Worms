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
      //@param game  describes the current board
      //@param params describes the vector where the input is stored
      //
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

      //------------------------------------------------------------------------
      //checkOneParameterCommand Method
      //the funtion checks the param for Melee, and makes damage calculations
      //@param game   describes the current board
      //@param current_weapon   is the number of the current weapon
      //
      bool checkOneParameterCommand(Game& game, int current_weapon);

      //------------------------------------------------------------------------
      //checkTwoParameterCommand Method
      //the funtion checks the param for gun, bazooka and blowtorch, furthermore
      //it makes damage calculations
      //@param game   describes the current board
      //@param current_weapon   is the number of the current weapon
      //@param params describes the vector where the input is stored
      //
      bool checkTwoParameterCommand(Game& game,
           std::vector<std::string>& params, int current_weapon);

      //------------------------------------------------------------------------
      //checkAirstrikeCommand
      //the funtion checks the current weapon for AIRSTRIKE, furthermore
      //it makes damage calculations
      //@param game   describes the current board
      //@param current_weapon   is the number of the current weapon
      //@param params describes the vector where the input is stored
      //

      bool checkAirstrikeCommand(Game& game,
           std::vector<std::string>& params, int current_weapon);

      //------------------------------------------------------------------------
      //checkTwoParameterCommand Method
      //the funtion checks the param for gun, bazooka and blowtorch, furthermore
      //it makes damage calculations
      //@param game   describes the current board
      //@param current_weapon   is the number of the current weapon
      //@param params describes the vector where the input is stored
      //

      bool checkThreeParameterCommand(Game& game,
           std::vector<std::string>& params, int current_weapon);
  };
}

#endif //SEP19_GROUP21486_ACTION_H
