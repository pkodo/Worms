//------------------------------------------------------------------------------
// Choose.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#ifndef SEP19_GROUP21486_CHOOSE_H
#define SEP19_GROUP21486_CHOOSE_H

#include "Command.h"
#include <string>

namespace Sep
{
  //----------------------------------------------------------------------------
  // Choose Class
  // class to perform Command-operations
  //
  class Choose : public Command
  {
    public:
      //------------------------------------------------------------------------
      // Constructor
      //@param name  describes the name of the worm you wanna chooseWeapon
      //@param current_worm  describes the number of the current worm
      //
      Choose(const std::string& name, int current_worm);

      //------------------------------------------------------------------------
      // Copy Constructor
      // Makes a copy of another Choose Object. Is set to delete.
      // @param choose object to copy.
      //
      Choose(Choose& choose) = delete;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Choose object to another. Is set to delete.
      // @param choose Original with values to copy.
      //
      Choose& operator = (Choose& choose) = delete;

      //------------------------------------------------------------------------
      // Method
      // method to execute the choose command
      // @param game  describes the current attributes of the board
      // @param params describes a worm within the vector
      //@return returns if the command was successfully executed
      //
      int execute(Game& game, std::vector<std::string>& params) override;

      //------------------------------------------------------------------------
      // Destructor
      //
      ~Choose() override;

    private:

      //The Variable describes the number of the current Worm
      int current_worm_;

  };
}

#endif //SEP19_GROUP21486_CHOOSE_H
