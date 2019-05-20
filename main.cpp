//------------------------------------------------------------------------------
// main.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#include "Game.h"
#include <string>
#include <iostream>

namespace Sep
{
  const int RETURN_OK = 0;
  const int RETURN_ERROR_BAD_CONFIG = -1;
  const int RETURN_MEMORY_ERROR = -2;
  const int RETURN_ERROR_ARGUMENT = -3;
  const std::string ERROR_WRONG_ARGUMENTS = "Usage: ./sworms <config-file>";
  const std::string ERROR_NO_MEMORY = "[ERROR] memory error!";
}

// The main function creates an game object, loads the configuration-file on it
// and then it performs the game loop

int main(int argc, char* argv[])
{
  try
  {
    if(argc != 2)
    {
      std::cout << Sep::ERROR_WRONG_ARGUMENTS << std::endl;
      return Sep::RETURN_ERROR_ARGUMENT;
    }

    Sep::Game game;
    if(game.loadConfig(std::string(argv[1])))
    {
      return Sep::RETURN_ERROR_BAD_CONFIG;
    }
    if(game.gameLoop())
    {
      std::cout << Sep::ERROR_NO_MEMORY << std::endl;
      return Sep::RETURN_MEMORY_ERROR;
    }
    return Sep::RETURN_OK;
  }
  catch(std::bad_alloc&)
  {
    return Sep::RETURN_MEMORY_ERROR;
  }
  catch(std::exception&)
  {

  }
  catch(...)
  {

  }
}
