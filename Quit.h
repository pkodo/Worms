//
// Created by stefan on 01.05.19.
//

#ifndef SEP19_GROUP21486_QUIT_H
#define SEP19_GROUP21486_QUIT_H

#include "Command.h"
namespace Sep
{
  //----------------------------------------------------------------------------
  // Quit Class
  // class end the game
  //
  class Quit : public Command
  {
    public:
      //Constructor
      Quit(const std::string& name);

      //Destructor
      virtual ~Quit();

      int execute(Game& game, std::vector<std::string>& params) override;
  };
}

#endif //SEP19_GROUP21486_QUIT_H
