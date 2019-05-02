//------------------------------------------------------------------------------
// Command.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#include "Command.h"
namespace Sep
{
  //----------------------------------------------------------------------------
  Command::Command(std::string name) : command_name_(name)
  {
  }

  //----------------------------------------------------------------------------
  Command::~Command()
  = default;

  //----------------------------------------------------------------------------
  const std::string &Command::getName() const
  {
    return command_name_;
  }
}
