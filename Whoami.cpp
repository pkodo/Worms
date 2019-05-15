//
// Created by stefan on 15.05.19.
//

#include <iostream>
#include "Whoami.h"

using std::cout;
using std::endl;

namespace Sep
{
  Sep::Whoami::Whoami(const std::string &name) : Command(name)
  {
  }

  Whoami::~Whoami()
  {

  }

  int Whoami::execute(Game &game, std::vector<std::string> &params)
  {
    cout << "Team: SwormTrooper" << endl;
    return 0;
  }
}
