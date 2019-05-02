//------------------------------------------------------------------------------
// Weapon.cpp
//
// Group: Group 11, study assistant Philip Loibl
//
// Authors: Paul Kodolitsch 01436808
//          Christian Luginger 01556194
//          Stefan Wietreich 11811040
//------------------------------------------------------------------------------
//

#include <iostream>
#include "Weapon.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  Weapon::Weapon() : ammo_(0), damage_(0)
  {
  }

  //----------------------------------------------------------------------------
  Weapon::Weapon(const std::string &name, int ammo, int damage) : name_(name),
                                                                  ammo_(ammo),
                                                                  damage_(
                                                                    damage)
  {
  }

  //----------------------------------------------------------------------------
  Weapon::~Weapon()
  = default;

  //----------------------------------------------------------------------------
  int Weapon::getAmmo() const
  {
    return ammo_;
  }

  //----------------------------------------------------------------------------
  void Weapon::decreaseAmmo()
  {
    ammo_--;
  }

  //----------------------------------------------------------------------------
  void Weapon::increaseAmmo()
  {
    ammo_++;
  }

  //----------------------------------------------------------------------------
  const std::string &Weapon::getName() const
  {
    return name_;
  }

  //----------------------------------------------------------------------------
  int Weapon::getDamage() const
  {
    return damage_;
  }

}
