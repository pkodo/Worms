//------------------------------------------------------------------------------
// Filename: Command.cpp
// Description: Class representing a general command
// Authors: Tutors
// Tutor: Tutors
// Group: 42
// Created: 32.13.2048
// Last change: 33.13.2048
//------------------------------------------------------------------------------

#include "Command.h"
namespace Sep
{
  //----------------------------------------------------------------------------
  Command::Command(std::string name) : command_name_(name)
  {
  }

  //----------------------------------------------------------------------------
  Command::~Command()
  {
  }

  //----------------------------------------------------------------------------
  const std::string &Command::getName() const
  {
    return command_name_;
  }
}
