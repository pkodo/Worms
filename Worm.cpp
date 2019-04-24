//------------------------------------------------------------------------------
// Worm.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Author: Paul Kodolitsch 01436808
//------------------------------------------------------------------------------
//

#include "Worm.h"
#include "Gun.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  Worm::~Worm()
  {

  }

  //----------------------------------------------------------------------------
  Worm::Worm(int id_, std::string name) : Field(WORM), id_(id_),
    name_(std::move(name))
  {
    Gun gun;
    weapons_.push_back(gun);
  }

  //----------------------------------------------------------------------------
  const std::string &Worm::getName() const
  {
    return name_;
  }

  //----------------------------------------------------------------------------
  void Worm::setName(const std::string &name)
  {
    Worm::name_ = name;
  }

  //----------------------------------------------------------------------------
  int Worm::getId() const
  {
    return id_;
  }

  //----------------------------------------------------------------------------
  int Worm::getHp() const
  {
    return hp_;
  }

  //----------------------------------------------------------------------------
  int Worm::getRow() const
  {
      return row_;
  }

  //----------------------------------------------------------------------------
  int Worm::getCol() const
  {
      return col_;
  }

  //----------------------------------------------------------------------------
  void Worm::setPosition(int row, int col)
  {
      row_ = row;
      col_ = col;
  }

  void Worm::setHp(int hp)
  {
      hp_ = hp;
  }

  //----------------------------------------------------------------------------
  const std::vector<Weapon> &Worm::getWeapons() const
  {
    return weapons_;
  }

  //----------------------------------------------------------------------------
  void Worm::damage(int points)
  {
    hp_ -= points;
  }

  //----------------------------------------------------------------------------
  char Worm::getCharacter() const
  {
    if(id_ >= 1 && id_ <= 3)
    {
      return '~';
    }
    else if(id_ >= 4 && id_ <= 6)
    {
      return '*';
    }
    else
    {
      return ' ';
    }
  }

  void Worm::setWeapons(const std::vector<Weapon> &weapons)
  {
    weapons_ = weapons;
  }
}