//
// Created by stefan on 17.04.19.
//

#include "Weapon.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  Weapon::Weapon(std::string name) : name_(name), ammo_(0), damage_(0)
  {
  }

  Weapon::Weapon(const std::string &name, int ammo, int damage) : name_(name),
                                                                  ammo_(ammo),
                                                                  damage_(
                                                                    damage)
  {
  }

  Weapon::Weapon()
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

  void Weapon::action()
  {

  }


}