//
// Created by stefan on 17.04.19.
//

#include "Weapon.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  Weapon::Weapon(std::string name) : name(std::move(name))
  {
  }

  //----------------------------------------------------------------------------
  Weapon::~Weapon()
  {
  }

  //----------------------------------------------------------------------------
  int Weapon::getAmmo() const
  {
    return ammo;
  }

  //----------------------------------------------------------------------------
  void Weapon::setAmmo(int ammo)
  {
    Weapon::ammo = ammo;
  }

  //----------------------------------------------------------------------------
  const std::string &Weapon::getName() const
  {
    return name;
  }

  //----------------------------------------------------------------------------
  int Weapon::getDamage() const
  {
    return damage;
  }
}