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
