//------------------------------------------------------------------------------
// Whoami.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//


#include <iostream>
#include "Whoami.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  Sep::Whoami::Whoami(const std::string &name) : Command(name)
  {
  }

  //----------------------------------------------------------------------------
  Whoami::~Whoami()
  {
  }

  //----------------------------------------------------------------------------
  int Whoami::execute(Game &game, std::vector<std::string> &params)
  {
    std::cout << "Team: I use Arch, btw" << std::endl;
    return 0;
  }
}
