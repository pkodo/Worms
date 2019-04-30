//
// Created by stefan on 23.04.19.
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
    Help(const std::string& name);

    //--------------------------------------------------------------------------
    // Method
    // Method to execute the help command
    //
    int execute(Game& game, std::vector<std::string>& params) override;

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Help();

  };
}

#endif //SEP19_GROUP21486_HELP_H
