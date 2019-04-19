//------------------------------------------------------------------------------
// Filename: main.cpp
// Description: simple main
// Authors: Michael Hancianu
// Group: xxxxx
// Created: 14.03.2019
// Last change: 15.03.2019 : some CS
//------------------------------------------------------------------------------

#include "Game.h"
#include <string>
#include <iostream>

namespace Sep
{
  const int RETURN_OK = 0;
  const int RETURN_ERROR_BAD_CONFIG = -1;
  const int RETURN_ERROR_INVALID_TARGET = -2;
  const int RETURN_ERROR_ARGUMENT = -3;
  const std::string ERROR_WRONG_ARGUMENTS = "Usage: ./sworms <config-file>";
}

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cout << Sep::ERROR_WRONG_ARGUMENTS << '\n';
    return Sep::RETURN_ERROR_ARGUMENT;
  }

  Sep::Game game;
  if(game.loadConfig(std::string(argv[1])))
    return Sep::RETURN_ERROR_BAD_CONFIG;
  game.gameLoop();

  return Sep::RETURN_OK;
}