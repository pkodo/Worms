//------------------------------------------------------------------------------
// Action.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
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
      // Copy Constructor
      // Makes a copy of another Action Object. Is set to delete.
      // @param action object to copy.
      //
      Action(Action& action) = delete;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Action object to another. Is set to delete.
      // @param action Original with values to copy.
      //
      Action& operator = (Action& action) = delete;

      //------------------------------------------------------------------------
      // Method
      // used to execute the command
      //@param game  describes the current board
      //@param params describes the vector where the input is stored
      //@return returns if the command was successfully executed
      //
      int execute(Game& game, std::vector<std::string>& params) override;

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
      // Enum describing the currently chosen weapon
      //
      enum Weapons
      {
        GUN,
        BAZOOKA,
        TELEPORT,
        BLOWTORCH,
        MELEE,
        AIRSTRIKE
      };

      //------------------------------------------------------------------------
      // Enum describing the various directions
      //
      enum Directions
      {
        LEFT,
        RIGHT,
        DOWN,
        UP,
        LEFT_DOWN,
        RIGHT_DOWN,
        LEFT_UP,
        RIGHT_UP
      };

      //------------------------------------------------------------------------
      //checkOneParameterCommand Method
      //the funtion checks the param for Melee, and makes damage calculations
      //@param game describes the current board
      //@param current_weapon is the number of the current weapon
      //@return returns if the specific command was successfully executed
      //
      bool checkOneParameterCommand(Game& game, int current_weapon);

      //------------------------------------------------------------------------
      //checkTwoParameterCommand Method
      //the funtion checks the param for gun, bazooka and blowtorch, furthermore
      //it makes damage calculations
      //@param game describes the current board
      //@param current_weapon is the number of the current weapon
      //@param params describes the vector where the input is stored
      //@return returns if the specific command was successfully executed
      //
      bool checkTwoParameterCommand(Game& game,
           std::vector<std::string>& params, int current_weapon);

      //------------------------------------------------------------------------
      //checkAirstrikeCommand
      //the funtion checks the current weapon for AIRSTRIKE, furthermore
      //it makes damage calculations
      //@param game describes the current board
      //@param current_weapon is the number of the current weapon
      //@param params describes the vector where the input is stored
      //@return returns if the specific command was successfully executed
      //
      bool checkAirstrikeCommand(Game& game,
           std::vector<std::string>& params, int current_weapon);

      //------------------------------------------------------------------------
      //checkThreeParameterCommand Method
      //the funtion checks the param for gun, bazooka and blowtorch, furthermore
      //it makes damage calculations
      //@param game describes the current board
      //@param current_weapon is the number of the current weapon
      //@param params describes the vector where the input is stored
      //@return returns if the specific command was successfully executed
      //
      bool checkThreeParameterCommand(Game& game,
           std::vector<std::string>& params, int current_weapon);
  };
}

#endif //SEP19_GROUP21486_ACTION_H
