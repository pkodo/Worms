//
// Created by stefan on 17.04.19.
//

#include "Weapon.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  Weapon::Weapon(std::string name) : name_(std::move(name))
  {
  }

  //----------------------------------------------------------------------------
  Weapon::~Weapon()
  {
  }

  //----------------------------------------------------------------------------
  int Weapon::getAmmo() const
  {
    return ammo_;
  }

  //----------------------------------------------------------------------------
  void Weapon::setAmmo(int ammo)
  {
    Weapon::ammo_ = ammo;
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