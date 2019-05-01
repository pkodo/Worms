//
// Created by stefan on 19.04.19.
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
      //Constructor
      Move(const std::string& name, int current_worm);

      //execute Method
      //moves the worm
      //@param game   is the actual board
      //@param params  is the input stored in a vector
      //
      int execute(Game& game, std::vector<std::string>& params) override;

      //Destructor
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
