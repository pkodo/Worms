//------------------------------------------------------------------------------
// Whoami.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#ifndef SEP19_GROUP21486_WHOAMI_H
#define SEP19_GROUP21486_WHOAMI_H

#include "Command.h"

namespace Sep
{
    //--------------------------------------------------------------------------
    // Whoami Class
    // class to show the team of the choosen worm
    //
  class Whoami : public Command
  {

    public:
      // Constructor
      Whoami(const std::string& name);

      //------------------------------------------------------------------------
      // Copy Constructor
      // Makes a copy of another Whoami Object. Is set to delete.
      // @param whoami object to copy.
      //
      Whoami(Whoami& whoami) = delete;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Whoami object to another. Is set to delete.
      // @param whoami Original with values to copy.
      //
      Whoami& operator = (Whoami& whoami) = delete;

      //Destructor
      virtual ~Whoami();

      //execute Method
      //prints the name of the team from the choosen worm
      //@param game   is the actual board
      //@param params  is the input stored in a vector
      //
      int execute(Game& game, std::vector<std::string>& params) override;
  };
}

#endif //SEP19_GROUP21486_WHOAMI_H
