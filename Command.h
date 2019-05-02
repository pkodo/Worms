//------------------------------------------------------------------------------
// Command.h
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <vector>
namespace Sep
{
  class Game;

  class Command
  {

    private:
    //------------------------------------------------------------------------
    /// Name of this command
    std::string command_name_;

    public:
    //------------------------------------------------------------------------
    // Constructor
    explicit Command(std::string name);

    //------------------------------------------------------------------------
    // Destructor
    virtual ~Command();

    //------------------------------------------------------------------------
    // Deleted copy constructor
    Command(const Command& original) = delete;

    //------------------------------------------------------------------------
    // Deleted assignment operator
    Command &operator=(const Command& original) = delete;

    //------------------------------------------------------------------------
    // Executes the command.
    // @param game The game where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action
    virtual int execute(Game& game, std::vector<std::string>& params) = 0;

    //------------------------------------------------------------------------
    // Getter Methods
    const std::string& getName() const;
  };
}
#endif //COMMAND_H_INCLUDED
