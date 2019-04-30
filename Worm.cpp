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
#include "Airstrike.h"
#include "Melee.h"
#include "Blowtorch.h"
#include "Teleport.h"
#include "Bazooka.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  Worm::~Worm()
  = default;

  //----------------------------------------------------------------------------
  Worm::Worm(int id_, std::string name) : Field(WORM), id_(id_), hp_(), row_
    (), col_(), name_(std::move(name)), current_weapon_()
  {
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
  std::vector<Weapon> &Worm::getWeapons()
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

  void Worm::setWeapons()
  {
    weapons_.emplace_back(Gun());
    weapons_.emplace_back(Bazooka());
    weapons_.emplace_back(Teleport());
    weapons_.emplace_back(Blowtorch());
    weapons_.emplace_back(Melee());
    weapons_.emplace_back(Airstrike());
  }

  //----------------------------------------------------------------------------
  int Worm::getCurrentWeapon() const
  {
    return current_weapon_;
  }

  //----------------------------------------------------------------------------
  void Worm::setCurrentWeapon(int currentWeapon)
  {
    current_weapon_ = currentWeapon;
  }
}