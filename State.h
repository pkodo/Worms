//------------------------------------------------------------------------------
// State.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#ifndef SEP19_GROUP21486_STATE_H
#define SEP19_GROUP21486_STATE_H

#include "Command.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // State Class
  // class to show the current state of the game
  //
  class State : public Command
  {

    public:
      // Constructor
      State(const std::string& name, int current_worm);

      //------------------------------------------------------------------------
      // Copy Constructor
      // Makes a copy of another State Object. Is set to delete.
      // @param state object to copy.
      //
      State(State& state) = delete;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one State object to another. Is set to delete.
      // @param state Original with values to copy.
      //
      State& operator = (State& state) = delete;

      //execute Method
      //prints state
      //@param game   is the actual board
      //@param params  is the input stored in a vector
      //
      int execute(Game& game, std::vector<std::string>& params) override;

      //Destructor
      ~State() override;

    private:
      //the variable is the number of the current worm
      int current_worm_;


  };
}

#endif //SEP19_GROUP21486_STATE_H
