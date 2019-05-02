//------------------------------------------------------------------------------
// Help.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger
//          Stefan Wietreich
//------------------------------------------------------------------------------
//

#ifndef SEP19_GROUP21486_HELP_H
#define SEP19_GROUP21486_HELP_H

#include "Command.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Help Class
  // class to execute the help command
  //
  class Help : public Command
  {

    public:
      //--------------------------------------------------------------------------
      // Constructor
      //
      explicit Help(const std::string& name);

      //--------------------------------------------------------------------------
      // Method
      // Method to execute the help command
      //@param game  is the actual board
      //@param params    is the input stored in a vector
      //
      int execute(Game& game, std::vector<std::string>& params) override;

      //--------------------------------------------------------------------------
      // Destructor
      //
      ~Help() override;

  };
}

#endif //SEP19_GROUP21486_HELP_H
