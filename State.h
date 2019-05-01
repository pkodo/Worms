//
// Created by stefan on 23.04.19.
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
