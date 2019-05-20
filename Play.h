//------------------------------------------------------------------------------
// Play.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#ifndef SEP19_GROUP21486_PLAY_H
#define SEP19_GROUP21486_PLAY_H

#include "Command.h"

namespace Sep
{
    //--------------------------------------------------------------------------
    // Play Class
    // class to implement simple KI
    //
  class Play : public Command
  {
    public:
      // Constructor
      Play(const std::string &name, int current_worm);

      //------------------------------------------------------------------------
      // Copy Constructor
      // Makes a copy of another Play Object. Is set to delete.
      // @param play object to copy.
      //
      Play(Play& play) = delete;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Play object to another. Is set to delete.
      // @param play Original with values to copy.
      //
      Play& operator = (Play& play) = delete;

      //Destructor
      virtual ~Play();

      //execute Method
      //executes the best possible turn for a worm
      //@param game   is the actual board
      //@param params  is the input stored in a vector
      //
      int execute(Game &game, std::vector<std::string> &params) override;

  private:

      int current_worm_;
  };
}


#endif //SEP19_GROUP21486_PLAY_H
