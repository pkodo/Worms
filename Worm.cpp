//------------------------------------------------------------------------------
// Worm.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Author: Paul Kodolitsch 01436808
//------------------------------------------------------------------------------
//

#include "Worm.h"
namespace Sep
{
  //----------------------------------------------------------------------------
  Worm::~Worm()
  {

  }

  //----------------------------------------------------------------------------
  Worm::Worm(int id, std::string name) : Field(WORM), id(id),
    name(std::move(name))
  {
  }

  //----------------------------------------------------------------------------
  const std::string &Worm::getName() const
  {
    return name;
  }

  //----------------------------------------------------------------------------
  void Worm::setName(const std::string &name)
  {
    Worm::name = name;
  }

  //----------------------------------------------------------------------------
  int Worm::getId() const
  {
    return id;
  }

  //----------------------------------------------------------------------------
  int Worm::getHp() const
  {
    return hp;
  }

  //----------------------------------------------------------------------------
  const std::vector<Weapon> &Worm::getWeapons() const
  {
    return weapons;
  }

  //----------------------------------------------------------------------------
  void Worm::damage(int points)
  {
    hp -= points;
  }

  //----------------------------------------------------------------------------
  char Worm::getCharacter() const
  {
    if(id >= 1 && id <= 3)
    {
      return '~';
    }
    else if(id >= 4 && id <= 6)
    {
      return '*';
    }
  }
}