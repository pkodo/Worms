//
// Created by stefan on 23.04.19.
//

#ifndef SEP19_GROUP21486_MAP_H
#define SEP19_GROUP21486_MAP_H

#include "Command.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Map Class
  // class to execut map
  //
  class Map : public Command
  {
    public:
      //Constructor
      explicit Map(const std::string &name);

      //execute Method
      //prints the board
      //@param game   is the actual board
      //@param params  is the input stored in a vector
      //
      int execute(Game &game, std::vector<std::string>& params) override;

      //Destructor
      ~Map() override;

  };
}

#endif //SEP19_GROUP21486_MAP_H
