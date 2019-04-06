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

int main()//int argc, char* argv[])
{
  //if(argc != 2)
  //{
  //  std::cout << Sep::ERROR_WRONG_ARGUMENTS << '\n';
  //  return Sep::RETURN_ERROR_ARGUMENT;
  //}

  Sep::Game game;
  if(game.loadConfig(std::string("config.txt")))
    return Sep::RETURN_ERROR_BAD_CONFIG;

  game.printMap();
  if(game.addWorm(2, 23))
    return Sep::RETURN_ERROR_INVALID_TARGET;

  game.printMap();
  game.move(7, 23, 2);
  if(game.addWorm(1, 24))
    return Sep::RETURN_ERROR_INVALID_TARGET;

  if(game.addWorm(4, 13))
    return Sep::RETURN_ERROR_INVALID_TARGET;

  game.printMap();
  game.move(9, 25, -1); // Warning, can't climb 2 higher Elements
  game.move(9, 25, 1); // will fall in water
  game.move(4, 13, -1); //climb
  game.printMap();
  if(game.addWorm(10, 16)) //error
    return Sep::RETURN_ERROR_INVALID_TARGET;

  if(game.addWorm(0, 1))
    return Sep::RETURN_ERROR_INVALID_TARGET;

  game.move(8, 1, 3);

  return Sep::RETURN_OK;
}