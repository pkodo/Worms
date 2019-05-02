//------------------------------------------------------------------------------
// Move.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger
//          Stefan Wietreich
//------------------------------------------------------------------------------
//

#ifndef SEP19_GROUP21486_MOVE_H
#define SEP19_GROUP21486_MOVE_H

#include "Command.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Move Class
  // class to move the worms
  //
  class Move : public Command
  {
    public:

      //------------------------------------------------------------------------
      //Constructor
      //
      Move(const std::string& name, int current_worm);

      //------------------------------------------------------------------------
      // Copy Constructor
      // Makes a copy of another Move Object. Is set to delete.
      // @param move object to copy.
      //
      Move(Move& move) = delete;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Move object to another. Is set to delete.
      // @param move Original with values to copy.
      //
      Move& operator = (Move& move) = delete;

      //------------------------------------------------------------------------
      //Executes method
      //moves the worm
      //@param game is the actual board
      //@param params is the input stored in a vector
      //
      int execute(Game& game, std::vector<std::string>& params) override;

      //------------------------------------------------------------------------
      //Destructor
      //
      ~Move() override;

    private:

      enum ErrorType
      {
        EVERYTHING_OK,
        INVALID_PARAMETER
      };

      //the variable shows the current worm
      int current_worm_;
  };
}

#endif //SEP19_GROUP21486_MOVE_H
