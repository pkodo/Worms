//------------------------------------------------------------------------------
// Quit.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger
//          Stefan Wietreich
//------------------------------------------------------------------------------
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

      //------------------------------------------------------------------------
      //Constructor
      //
      Quit(const std::string& name);

      //------------------------------------------------------------------------
      // Copy Constructor
      // Makes a copy of another Move Quit. Is set to delete.
      // @param quit object to copy.
      //
      Quit(Quit& quit) = delete;

      //------------------------------------------------------------------------
      // Assignment Operator
      // Used to assign one Quit object to another. Is set to delete.
      // @param quit Original with values to copy.
      //
      Quit& operator = (Quit& quit) = delete;

      //------------------------------------------------------------------------
      //Destructor
      //
      virtual ~Quit();

      //------------------------------------------------------------------------
      //Executes method
      //moves the worm
      //@param game is the actual board
      //@param params is the input stored in a vector
      //
      int execute(Game& game, std::vector<std::string>& params) override;
  };
}

#endif //SEP19_GROUP21486_QUIT_H
